/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
long test_bitMatch(long x, long y)
{
    int i;
    long result = 0;
    for (i = 0; i < 64; i++) {
 long mask = 1L << i;
 long bit = (x & mask) == (y & mask);
 result |= bit << i;
    }
    return result;
}
//2
long test_copyLSB(long x)
{
  return (x & 0x1L) ? -1 : 0;
}
long test_distinctNegation(long x) {
    return (long) (x != -x);
}
long test_leastBitPos(long x) {
  long mask = 1L;
  if (x == 0)
    return 0;
  while (!(mask & x)) {
    mask = mask << 1;
  }
  return mask;
}
long test_dividePower2(long x, long n)
{
    long p2n = 1L<<n;
    return x/p2n;
}
//3
long test_conditional(long x, long y, long z)
{
  return x?y:z;
}
long test_isLessOrEqual(long x, long y)
{
    return (long) (x <= y);
}
//4
long test_trueThreeFourths(long x)
{
  return (long) (((__int128) x * 3L)/4L);
}
long test_bitCount(long x) {
  long result = 0;
  long i;
  for (i = 0; i < 64; i++)
    result += (x >> i) & 0x1;
  return result;
}
long test_isPalindrome(long x) {
    long result = 1L;
    int i;
    long mask = 0xFFFFFFFFL;
    long xlo = x & mask;
    long xhi = (x >> 32) & mask;
    for (i = 0; i < 32; i++) {
 int flipi = 31-i;
 long bhigh = (xhi >> i) & 0x1L;
 long blow = (xlo >> flipi) & 0x1L;
 result = result && (long) (bhigh == blow);
    }
    return result;
}
long test_integerLog2(long x) {
  long result;
  /* find the leftmost bit */
  for (result = 63; result >= 0; result--) {
      long val = 1L << result;
      if (x & val)
   break;
  }
  return result;
}
//float
int test_floatIsEqual(unsigned uf, unsigned ug) {
    float f = u2f(uf);
    float g = u2f(ug);
    return f == g;
}
unsigned test_floatScale4(unsigned uf) {
  float f = u2f(uf);
  float tf = 4*f;
  if (isnan(f))
    return uf;
  else
    return f2u(tf);
}
unsigned test_floatUnsigned2Float(unsigned u) {
    float f = (float) u;
    return f2u(f);
}
