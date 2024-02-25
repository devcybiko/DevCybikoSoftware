/**
  * The B2C project is a set of programs and libraries
  * that comprise a languate translator.  B2C compiles
  * a BASIC program into C which is compiled by the Cybiko
  * SDK 2.10 into an application.
  *
  *  Copyright 2004 by Gregory Smith
  *  (greg@alcorgrp.com)
  *
  *  This program is free software; you can redistribute it and/or
  *  modify it under the terms of the GNU General Public License
  *  as published by the Free Software Foundation; either version 2
  *  of the License, or (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License
  *  along with this program; if not, write to the Free Software
  *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
  *
  * @author Gregory Smith (http://www.greg-smith.com, Greg@AlcorGrp.com)
  * @version 1.0
  */
#include "inc\fixed.h"

short fixed_error = 0;
fixed fixed_sine_tbl[65]={
0x0000,0x0648,0x0c8f,0x12d5,0x1917,0x1f56,0x2590,0x2bc4,
0x31f1,0x3817,0x3e33,0x4447,0x4a50,0x504d,0x563e,0x5c22,
0x61f7,0x67bd,0x6d74,0x7319,0x78ad,0x7e2e,0x839c,0x88f5,
0x8e39,0x9368,0x987f,0x9d7f,0xa267,0xa736,0xabeb,0xb085,
0xb504,0xb968,0xbdae,0xc1d8,0xc5e4,0xc9d1,0xcd9f,0xd14d,
0xd4db,0xd848,0xdb94,0xdebe,0xe1c5,0xe4aa,0xe76b,0xea09,
0xec83,0xeed8,0xf109,0xf314,0xf4fa,0xf6ba,0xf853,0xf9c7,
0xfb14,0xfc3b,0xfd3a,0xfe13,0xfec4,0xff4e,0xffb1,0xffec,
0x00010000};

fixed fixed_from_int(int i)
{
	fixed result;
	result = ((long)i)<<16;
	return result;
}

fixed fixed_from_char(char c)
{
	fixed result;
	result = ((long)c)<<16;
	return result;
}

fixed fixed_from_long(long l)
{
	fixed result;
	result = l<<16;
	return result;
}

int fixed_to_int(fixed f)
{
	int result;
	result = (int)(f>>16);
	return result;
}

fixed fixed_neg(fixed a)
{
  return -a;
}

fixed fixed_add(fixed a, fixed b)
{
  return a+b;
}

fixed fixed_subtract(fixed a, fixed b)
{
  return a-b;
}

char *fixed_print(fixed a, int digits)
{
  long intpart;
  long fracpart;
  int dec;
  short sign;
  static char s[32];
  short i,j,d;

  memset(s, 0, sizeof(s));
  if (a < 0) 
    {
      sign=-1;
      a=-a;
    }
  else sign=1;

  intpart = a>>16L;
//TRACE("a=%08lx", a);
//TRACE("intpart=%ld", intpart);
  fracpart= a & 0x0000ffffL;
//TRACE("fracpart=%ld", fracpart);

  i=7;

  dec = (int)(intpart % 10L);
  intpart = intpart / 10L;
  s[--i]='0'+(char)dec;

  while(intpart)
    {
      dec = (int)(intpart % 10L);
      intpart = intpart / 10L;
//TRACE("%ld %ld", intpart, dec);
      s[--i]='0'+(char)dec;
    }
  if (sign<1) s[--i]='-';
	
  j=7;
  s[j++]='.';
  d=0;
//  while(fracpart)
    while (d != digits)
    {
      //if (d==digits) break;
      d++;
      fracpart *= 10;
      dec = (int)(fracpart >> 16);
//TRACE("%d %d", intpart, dec);
      s[j++]='0'+(char)dec;
      fracpart &= 0xffff;
    }
  s[j]=0;
  return &s[i];
}	

#define isdigit(a) (a>='0' && a<='9')

fixed fixed_from_string(char *s)
{
  char *t=s;
  fixed result=0;
  fixed intpart=0;
  fixed fracpart=0;
  short sign=1;
  
  if (*t == '-') {sign=-1; t++;}
  if (*t == '+') {t++;}

  while(*t)
    {
      if (*t == '.') {break;}
      if (!isdigit(*t)) break;
      intpart=intpart*10L+(*t-'0');
      t++;
    }
  if (*t == '.')
    {
      while(*t) t++;
      t--;
      while(*t != '.')
	{
	  if (!isdigit(*t)) break;
	  fracpart = fracpart + (( ((long)(*t)-'0')) << 16);
	  fracpart = fracpart/10L;
//TRACE("*t=%c fracpart=%08lx", *t, fracpart);
	  t--;
	}
    }
  result = (intpart<<16) + fracpart;
  if (sign == -1) result = fixed_neg(result);
  return result;
}

fixed fixed_multiply(fixed a, fixed b)
{
  short s0=1;
  short s1=1;
  fixed a0;
  fixed b0;
  fixed a1;
  fixed b1;
  fixed a0b0;
  fixed a0b1;
  fixed a1b0;
  fixed a1b1;
  fixed c00;
  fixed c10;
  fixed c01;
  fixed c11;
  fixed result;

  fixed_error=0;

  if (a<0) {s0=-1; a=fixed_neg(a);}
  if (b<0) {s1=-1; b=fixed_neg(b);}
  a0=a & 0x0000ffffL;
  b0=b & 0x0000ffffL;
  a1=a >> 16;
  b1=b >> 16;

  a0b0 = a0*b0;
  a0b1 = a0*b1;
  a1b0 = a1*b0;
  a1b1 = a1*b1;

  c00 = (a0b0>>16)&0x0000ffffL;
  c01 = a0b1 & 0xffff0000L;
  a0b1 &= 0x0000ffffL;
  c10 = a1b0 & 0xffff0000L;
  a1b0 &= 0x0000ffffL;

  if (a1b1 > 0x00007fffL)
    fixed_error=1;

  a1b1 =(a1b1 & 0x0000ffffL)<<16;

  result = s0*s1*(c00+a0b1+a1b0+(c01+c10+a1b1));
  return result;
}

fixed fixed_reciprocal(fixed a)
{
  fixed hi;
  fixed lo;
  fixed prod;
  fixed guess;
  fixed last_guess;

  long sign=1;
  short i;

TRACE("a=%08lx", a);
  if (a < 0)
    {
      a=-a;
      sign=-1;
    }
  if (a==65536L) return sign*65536L;

  if (a < 32768L)
    {
TRACE("Its a fraction");
      hi = 1073741824L;
      lo = 65536L;
    }
  else
    {
TRACE("Its a whole number");
      hi = 65536L;
      lo = 0;
    }
  i=0;
  last_guess = 0;
  guess = 1;
  while(i<32 && (last_guess != guess))
    {
      TRACE("%d: hi=%ld lo=%ld lg=%ld gu=%ld", i, hi, lo, last_guess, guess);
      last_guess = guess;
      guess = (hi+lo)/2L;
      prod = fixed_multiply(a,guess);
      if (prod > 65536L)
	{
	  hi = guess; 
	}
      else
	{
	  lo = guess;
	}
      i++;
    }
  return hi*sign;
}

fixed fixed_sqrt(fixed a)
{
  fixed hi;
  fixed lo;
  fixed prod;
  fixed guess;
  fixed last_guess;

  short sign=1;
  short i;

  if (a < 0)
    {
      return 0;
    }
  if (a==65536) return 65536;
  if (a == 0)  return 0;

  if (a < 0x00010000)
    {
      hi = 0x00010000;
      lo = a;
    }
  else
    {
      hi = a;
      lo = 0;
    }

  i=0;
  last_guess = 0;
  guess = 1;
  while(i<32 && (last_guess != guess))
    {
      /*printf("%d: hi=%08x lo=%08x lg=%08x gu=%08x\n", i, hi, lo, last_guess, guess);*/
      last_guess = guess;
      guess = (hi+lo)/2;
      prod = fixed_multiply(guess,guess);
      if (prod > a)
	{
	  hi = guess; 
	}
      else
	{
	  lo = guess;
	}
      i++;
    }
  return lo;
}

fixed fixed_divide(fixed a, fixed b)
{
  return fixed_multiply(a, fixed_reciprocal(b));
}

#define FIXED_HALF_PI 0x0001921f
#define FIXED_PI 0x0003243f
#define FIXED_HALF_3PI 0x0004b65f
#define FIXED_2PI  0x0006487E
#define FIXED_RECIPROCAL_2PI 0x000028bf
#define FIXED_RECIPROCAL_HALF_PI 0x0000a2fb

fixed fixed_sin(fixed a)
{
  short sign=1;
  fixed tmp;
  short index;
  fixed result;

  if (a<0) {a=-a; sign=-1;}
  while(a>FIXED_2PI) a=a-FIXED_2PI;
  if (0 <= a && a < FIXED_HALF_PI) 
    {
      tmp = fixed_multiply(a, FIXED_RECIPROCAL_HALF_PI); /* divide by pi/2 */
      index = (short)(tmp >> 10); /* multiply by 64, shift right 16 */
      result = fixed_sine_tbl[index];
    }
  else if (FIXED_HALF_PI <= a && a < FIXED_PI)
    {
      tmp = fixed_multiply(a-FIXED_HALF_PI, FIXED_RECIPROCAL_HALF_PI); /* divide by pi/2 */
      index = (short)(tmp >> 10); /* multiply by 64, shift right 16 */
      result = fixed_sine_tbl[64-index];
    }
  else if (FIXED_PI <= a && a < FIXED_HALF_3PI)
    {
      tmp = fixed_multiply(a-FIXED_PI, FIXED_RECIPROCAL_HALF_PI); /* divide by pi/2 */
      index = (short)(tmp >> 10); /* multiply by 64, shift right 16 */
      result = -fixed_sine_tbl[index];
    }
  else
    {
      tmp = fixed_multiply(a-FIXED_HALF_3PI, FIXED_RECIPROCAL_HALF_PI); /* divide by pi/2 */
      index = (short)(tmp >> 10); /* multiply by 64, shift right 16 */
      result = -fixed_sine_tbl[64-index];
    }
  return sign*result;
  
}

fixed fixed_cos(fixed a)
{
  return fixed_sin(a+FIXED_HALF_PI);
}

fixed fixed_tan(fixed a)
{
  return fixed_divide(fixed_sin(a), fixed_cos(a));
}