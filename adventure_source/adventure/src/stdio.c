// stdio.c
// (C) Jan 2001, The Alcor Group, Inc.
// Authored by and placed into the Public Domain
// By Gregory Smith
//
// Standard I/O replacement for Cybiko
//
#define MALLOC(n,type) (type *)malloc(n * sizeof(type))
#define CALLOC(n,type) (type *)calloc(n, sizeof(type))
#define SAME(a,b) (strcmp(a,b) == 0)

#define MAX_LINES 100
#define LINE_LENGTH 40
#define MAX_PIXELS_WIDTH 160
#define MAX_PIXELS_HEIGHT 100

//
// the putc structure.
// Cybiko has a limit of 256 bytes on the stack
// per function.  So all the local variables
// are gathered here.
//
static struct putc {
    int x, y;     // last x,y coords of putc drawing
    int nlines;   // number of lines in the cybiko display
    int ht;       // height of font
    int topline;  // the currently displayed line while scrolling
    struct Font *font;  // default font
    char *lines[MAX_LINES];  // array lines of scrolling text
} *pc;

//
// currently displayed line
//
static int disp_line=MAX_LINES;

//
// a shared buffer for all functions
//
static char stdio_buffer[256];

static void redisp();
static void prev_disp(int dir);
static void scroll();
static void putc_update(int c);
static void getchar_del();

//
// init the putc structure
//
void init_putc()
{
    int i;

    //
    // allocate the pc structure
    //
    pc = CALLOC(1, struct putc);

    //
    // allocate space for each line of text in the
    // scrolling console
    //
    for(i=0; i<MAX_LINES; i++)
    {
        pc->lines[i] = CALLOC(LINE_LENGTH, char);
    }

    //
    //default font for putc
    //
    pc->font = mini_normal_font;

    //
    // default font
    //
    pc->nlines = MAX_PIXELS_HEIGHT/Font_get_char_height(pc->font);

    //
    // height of font
    //
    pc->ht = Font_get_char_height(pc->font);

    //
    // top line of scrolling display
    //
    pc->topline = MAX_LINES-1;

    //
    // erase display
    //
    TGraph_fill_screen(main_module.m_gfx, CLR_WHITE);
}

//
// redisplay the display
//
static void redisp()
{
    int i;

    //
    // reset the top line of the display
    //
    disp_line = MAX_LINES;

    //
    // clear the display
    //
    TGraph_fill_screen (main_module.m_gfx, CLR_WHITE);

    //
    // set the font and the color
    //
    Graphics_set_font(main_module.m_gfx, pc->font);
    Graphics_set_color(main_module.m_gfx, CLR_BLACK);

    //
    // reset the x,y coords
    //
    pc->x = 0;
    pc->y = 0;

    //
    // for each of the bottom lines of text
    //
    for(i=MAX_LINES-pc->nlines; i<MAX_LINES; i++)
    {
        //
        // display the line of text
        //
        Graphics_draw_text(main_module.m_gfx, pc->lines[i], pc->x, pc->y);

        //
        // point to the next line of display
        //
        pc->y += pc->ht;
    }
    //
    // update the display
    //
    DisplayGraphics_show(main_module.m_gfx);
}

//
// scroll back one screenful of text
//
static void prev_disp(int dir)
{
    int i;

    //
    // scroll forward one screenful
    //
    if (dir == 1)
    {
        disp_line += (pc->nlines-1);
        if (disp_line >= (MAX_LINES-pc->nlines))
            disp_line = MAX_LINES;
    }
    //
    // scroll back one screenful
    //
    else
    {
        if (disp_line == MAX_LINES) disp_line = MAX_LINES - pc->nlines;
        disp_line -= (pc->nlines-1);
        if (disp_line < pc->topline)
            disp_line = pc->topline;
    }
    //
    // if we've scrolled to the bottom, just redisplay the normal text
    //
    if (disp_line == MAX_LINES)
    {
        redisp();
        return;
    }

    //
    // we're in the old text, make a black background and white text
    //
    TGraph_fill_screen (main_module.m_gfx, CLR_BLACK);
    Graphics_set_font(main_module.m_gfx, pc->font);
    Graphics_set_color(main_module.m_gfx, CLR_WHITE);
    pc->x = 0;
    pc->y = 0;

    //
    // redisplay the text
    //
    for(i=disp_line; i<disp_line+pc->nlines; i++)
    {
        Graphics_draw_text(main_module.m_gfx, pc->lines[i], pc->x, pc->y);
        pc->y += pc->ht;
    }

    //
    // update the display
    //
    DisplayGraphics_show(main_module.m_gfx);
}

//
// scroll all the text off the top of the saved list of lines
// move the top line to the bottom
//
static void scroll()
{
    char *tmp = pc->lines[0];  // save off the top line of archived text
    int i;

    //
    // move the current top line up the archived text
    //
    pc->topline--;

    //
    // if it scrolls off the top then set the topline
    // to the top of the archived text
    //
    if (pc->topline < 0) pc->topline = 0;

    //
    // move the text up the archived text
    //
    for(i=0; i<MAX_LINES-1; i++)
        pc->lines[i] = pc->lines[i+1];

    //
    // roll the top line to the bottom, and clear the string
    //
    pc->lines[i] = tmp;
    tmp[0] = 0;
}

//
// putc puts a single character into the stdio_buff
// and display a single character on the display
//
void putc(int c)
{
    char buf[2];
    int i = MAX_LINES-1;  // point to the last line in the display
    int len;
    char *curline;

    //
    // if its the null character, just exit
    //
    if (c == 0) return;

    //
    // if its the newline, scroll up one line and redisplay
    //
    if (c == '\n')
    {
        scroll();
        redisp();
        return;
    }

    //
    // the curline is the bottom (last) line of the display
    //
    curline = pc->lines[i];

    //
    // append the character to the end of the last line of the display
    //
    len = strlen(pc->lines[i]);
    curline[len] = (char) c;
    len++;
    curline[len] = 0; // null terminator

    //
    // determine if adding this character will go off the end screen
    //
    if (Font_string_width(pc->font, curline) > MAX_PIXELS_WIDTH)
    {
        //
        // take the character off the end of the string
        //
        len--;
        curline[len] = 0;

        //
        // scroll the display and redisplay (to make room on the next
        // line for the character)
        //
        scroll();
        redisp();

        //
        // append the character to the end of the last line of the display
        //
        curline = pc->lines[i];
        len = strlen(pc->lines[i]);
        curline[len] = (char) c;
        len++;
        curline[len] = 0; //null terminator
    }

    //
    // if adding the character turns a line then scroll and redisplay
    //
    if (len >= LINE_LENGTH-1)
    {
        scroll();
        redisp();
        return;
    }
}

//
// Called during gets() to display a single character at
// a time.  putc() doesn't do a DisplayGraphics_show().
//
static void putc_update(int c)
{
    //
    // put the character on the display
    //
    putc(c);

    //
    // draw just the bottom line of text and display the screen
    //
    Graphics_draw_text(main_module.m_gfx, pc->lines[MAX_LINES-1], 0, (pc->nlines-1)*pc->ht);
    DisplayGraphics_show(main_module.m_gfx);
}

//
// emulate the fopen() call from posix.
//
FILE *fopen(char *name, char *mode)
{
	struct FileInput *fi;  // cybiko input file
	struct FileOutput *fo; // cybiko output file
	struct _file *file;    // the returned file object
    int openned;           // whether the file was previously openned

    //
    // Allocate the file object
    //
    file = CALLOC(1, FILE);

    //
    // if the file mode is READ
    //
	if (*mode == 'r')
	{
        //
        // set the file type to INPUT
        //
        file->type = 0;

        //
        // open the file.  Opens the file from the archive
        // XXX NEED TO OPEN FILES FROM THE FLASH DEVICE NOT THE ARCHIVE
        //
        file->cybio = Archive_open_Ex(main_module.m_process->module->archive, name);

        //
        // if the file openned - return the FILE pointer
        //
        if (file->cybio)
        {
            return file;
        }

        //
        // if the file failed to open, close the file (free memory)
        // and return NULL
        //
        fclose(file);
        return NULL;
	}

    //
    // Open the file for WRITE access
    //
	else
	{
        //
        // set the type to WRITE access
        //
		file->type = 1;

        //
        // allocate the FileOutput structure and call the constructor
        //
		file->cybio = CALLOC(1, struct FileOutput);
		FileOutput_ctor(file->cybio);

        //
        // open the file (not in the archive, but on the device
        //
        openned = FileOutput_open(file->cybio, name, TRUE);

        //
        // if the file openned, return the FILE pointer
        // otherwise close (free) the file and return NULL
        //
		if (openned) return file;
		fclose(file);
		return NULL;
    }

    //XXX NEED TO IMPLEMENT APPEND ACCESS //
}

//
// fclose - close the cybiko file and deallocate memory
//
void fclose(FILE *_file)
{
	struct _file *file = _file;

    //
    // if its READ access
    //
	if (file->type == 0)
	{
        //
        // destroy the file input structure
        //
	    if (file->cybio) Input_dtor(file->cybio, FREE_MEMORY);
    }
	else
	{
        //
        // destroy the file output structure
        //
        if (file->cybio) Output_dtor(file->cybio, FREE_MEMORY);
    }

    //
    // free the file descriptor
    //
	free(file);
	return;
}

//
// a poor man's implementation of ltoa (long to ascii)
// n = number to convert
// buf = buffer to put the converted number into
// buflen = the max size of the buffer (ignored)
//
char *ltoa(long n, char *buf, int buflen)
{
	sprintf(buf, "%ld", n);
	return buf;
}

//
// printf is just a call to vsprintf() and then to
// putc() to print each character to the display
// XXX NO CHECKS FOR STDIO_BUFVER OVERFLOW
//
int printf(char *fmt, ...)
{
    int i;
    va_list parameters;    // variable parameter list

    va_start(parameters, fmt);
    vsprintf(stdio_buffer, fmt, parameters);    // varargs sprintf

    //
    // send each character to the display, slowly!
    //
    for(i=0; stdio_buffer[i]; i++)
        putc(stdio_buffer[i]);
}

//
// return the current position of the input file
// XXX NEEDS TO WORK FOR OUTPUT FILES AS WELL
//
long ftell(FILE *file)
{
	return FileInput_tell(file->cybio);
}

// whence - 0=set, 1=cur 2=end
// XXX WORKS FOR INPUT FILE ONLY, NEEDS TO WORK FOR OUTPUT AS WELL
long fseek(FILE *file, long n, int whence)
{
	return Input_seekg(file->cybio, n, whence);
}

//
// if the file is stdout or stderr, it goes to the display
// else it goes to the file via fprintf
//
int fputc(int c, FILE *file)
{
    if (file == stdout || file == stderr) putc(c);
    else fprintf(file, "%c", c);
}

//
// get a singled character from the file.
// if the file is stdin, get it from the keyboard via getchar()
// otherwise read a byte from an Input stream
//
int fgetc(FILE *file)
{
    int c;

	if (file == stdin)
    {
		c = getchar();
    }
	else
    {
		c = Input_read_byte(file->cybio);
    }
    return c;
}

//
// get a string from the keyboard (stdin) or a file
//
int fgets(char *buf, int buflen, FILE *file)
{
	int i;
	int c;

    //
    // for each character in the buffer or until a newline
    //
	for(i=0; i<buflen-1; i++)
	{
        //
        // get a single character from the file
        //
		c = fgetc(file);

        //
        // if its a newline, we need to exit early
        //
		if (c == '\n')
		{
			buf[i] = (char) c; // add the newline to the string
			i++;
            buf[i] = 0;  //terminate the string
			break;
		}
        //
        // if its the end of file exit early
        //
		else if (c == EOF)
		{
            buf[i] = 0;
            if (file == stdin) return 0;   // XXX THIS MAY BE PREMATURE
			break;
		}
        //
        // if its the backspace key remove the last character
        //
        else if (c == KEY_BACKSPACE)
        {
            if (i)
            {
                i--;
                buf[i] = 0;
                i--;
            }
        }
        //
        // add the character to the end of the string
        //
        else
        {
            buf[i] = (char) c;
            buf[i+1] = 0;
        }
	}
	buf[i] = 0;  // null terminate the string
	return i; // return the length of the string
}

//
// fprintf implementation
//
int fprintf(FILE *file, char *fmt, ...)
{
    int i;
    va_list parameters;    // variable parameter list

    va_start(parameters, fmt);
    vsprintf(stdio_buffer, fmt, parameters);    // varargs sprintf
    va_end(parameters);

    for(i=0; stdio_buffer[i]; i++)
        fputc(stdio_buffer[i], file);
}

//
// get a string from the keyboard
//
char *gets(char *inrec)
{
	char *s;

    //
    // get the string from the stdin
    //
	fgets(inrec, 256, stdin);

    //
    // remove the newline, if it exists
    //
	s = strchr(inrec, '\n');
	if (s) *s = 0;
	return inrec;
}

//
// getchar_del - respond to the BKSP key by removing the character from
// the display. wont wrap to the previous line.
//
static void getchar_del()
{
    int i = MAX_LINES-1;
    int len;
    char *curline;

    //
    // get the current line
    //
    curline = pc->lines[i];

    //
    // find the last character in the current line
    // replace it with a null - erasing it
    // and redisplay the screen
    //
    len = strlen(curline);
    if (len)
    {
        len--;
        curline[len] = 0;
        redisp();
    }
}

//
// enter into a message loop waiting for keystroke.
// XXX DOESNT HANDLE UPPERCASE, SHIFT, FN keys
//
int getchar()
{
  struct Message* message;   // the message
  bool got_char = FALSE;     // whether a char is found
  int return_value = 0;      // the return key value
  int key;  // the key

  //
  // display the last output (printf prompt, eg)
  //
  putc_update(0);

  //
  // while no character has been found,
  // process messages by passing them to the default message handler
  //
  while(!got_char)
  {
    //
    // wait for a message
    //
    message = cWinApp_get_message(main_module.m_process, 0, 1, MSG_USER);

    //
    // on each message check the message id
    //
    switch(message->msgid)
    {
      // if the process is told to shutup, EOF is returned
      // Just like UNIX
      case MSG_SHUTUP:
      case MSG_QUIT:
        got_char = TRUE;
        return_value = EOF;
        break;
 
      // If the new focus is us then redisplay the screen
      case MSG_GOTFOCUS:
        redisp();
        break;

      // at last a key
      case MSG_KEYDOWN:
      {
          // save off a single key
          key = Message_get_key_param(message)->scancode;

          // switch on the key
          switch(key) {
 
          // XXX EXITS IMMEDIATELY WITHOUT FREEING MEMORY
          case KEY_ESC:
          {
            got_char = TRUE;
            return_value = EOF;
            exit(0); //hack
            break;
          }

          // Returnds a newline and updates the display
          case KEY_ENTER:
          {
            key = '\n';
            return_value = key;
            got_char = TRUE;
            putc_update(key);
            break;
          }

          // delete the last character from the display and redisplay
          case KEY_BACKSPACE:
          case KEY_DEL:
          {
            return_value = KEY_BACKSPACE;
            got_char = TRUE;
            getchar_del();
            if (disp_line != MAX_LINES) redisp();
            break;
          }

          // if the help key is pressed, call the default proc
          case KEY_HELP:
          {
              cWinApp_defproc(main_module.m_process, message);
              redisp();
              break;
          }

          // if key_up scroll up to the previous window
          case KEY_UP:
          {
              prev_disp(-1);
              break;
          }

          // if key_down scroll down to the next window
          case KEY_DOWN:
          {
              prev_disp(+1);
              break;
          }

          // any ordinary key - add it to the display and return it
	      default:
	      {
             got_char= TRUE;
		     return_value = key;
             putc_update(key);
             if (disp_line != MAX_LINES) redisp();
             break;
	      }
          }
          break;
      }
      default:             //  Processes all unprocessed messages.
        // pass the message to the user's message proc
        process_message(message);

        // pass the message to the default proc
        cWinApp_defproc(main_module.m_process, message);
    }

    // delete the processed message
    Message_delete(message);
  }  //  while(!exit_application)
    return return_value;

}

//
// call finput_read to get some data from the file
//
long fread(void *ptr, size_t size, size_t nitems, FILE *file)
{
    return FileInput_read(file->cybio, ptr, (long)size*nitems );
}

//
// call foutput_write to put some data to the file
//
long fwrite(void *ptr, size_t size, size_t nitems, FILE *file)
{
    return FileOutput_write(file->cybio, ptr, (long)size*nitems);
}

//
// convert string to integer
//
long atoi(char *s)
{
	return (long)atoul(s);
}

//
// convert upper case character to lower case character
//
int tolower(int c)
{
    if (c>='A' && c<='Z') return c+32;
	else return c;
}

//
// random number generator
//
long rand(void)
{
	return random(-1);
}
