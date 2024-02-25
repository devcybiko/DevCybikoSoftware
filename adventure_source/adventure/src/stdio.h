// stdio.h
// (C) The Alcor Group, Inc
// Copyright Jan 2001

#ifndef _STDIO_H_
#define _STDIO_H_

#define rindex(s,c) strrchr(s,c)

struct _file {
	long type;
	void *cybio;
    struct Archive *archive;
};

#ifndef EOF
#define EOF (-1)
#endif

#define FILE struct _file
#define stdout ((FILE *)-1)
#define stdin ((FILE *)-2)
#define stderr ((FILE *)-3)

void init_putc();
void putc(int c);
FILE *fopen(char *name, char *mode);
void fclose(FILE *);
char *ltoa(long a, char *buf, int buflen);
int printf(char *fmt, ...);
long ftell(FILE *file);
long fseek(FILE *file, long n, int whence);
int fputc(int c, FILE *file);
int fgetc(FILE *file);
int fgets(char *buf, int buflen, FILE *file);
int fprintf(FILE *file, char *fmt, ...);
char *gets(char *inrec);
int getchar();
long fread(void *ptr, size_t size, size_t nitems, FILE *file);
long fwrite(void *ptr, size_t size, size_t nitems, FILE *file);
long atoi(char *s);
int tolower(int c);
long rand(void);

int process_message(struct Message *message);

#endif //_STDIO_H_
