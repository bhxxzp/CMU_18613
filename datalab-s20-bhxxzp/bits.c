/* 
 * CS:APP Data Lab 
 * 
 * <Name: Peng Zeng  userID:pengzeng>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  long Funct(long arg1, long arg2, ...) {
      /* brief description of how your implementation works */
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  3. Function arguments and local variables (no global variables).
  4. Local variables of type int and long
  5. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  6. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  7. Casting from int to long and from long to int
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.
 
  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
   */
  long pow2plus1(long x) {
     /* exploit ability of shifts to compute powers of 2 */
     /* Note that the 'L' indicates a long constant */
     return (1L << x) + 1L;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
   */
  long pow2plus4(long x) {
     /* exploit ability of shifts to compute powers of 2 */
     long result = (1L << x);
     result += 4L;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
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
/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7L, 0xEL) = 0xFFFFFFFFFFFFFFF6L
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
long bitMatch(long x, long y) {
  return ~(x & ~y) & ~(~x & y);
}
//2
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL,
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) {
  // logical shift
  return ((x << 63) >> 63);
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
long distinctNegation(long x) {
  // -x = ~x + 1
  long result = x ^ (~x + 1);
  return !!result;
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96L) = 0x20L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
long leastBitPos(long x) {
  return (x & (~x + 1));
}
/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) {
  long sign = x >> 63; // if x positive return 1, if negative or zero return 0
  long result1 = x >> n; // x positive's result
  long result2 = (x + ((1L << n) + (~1L + 1L))) >> n; // x negative's result
  return (result1 & ~sign) | (sign & result2);
}
//3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4L,5L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long conditional(long x, long y, long z) {
  long point = !!x;
  long mask = ((point << 63) >> 63);
  return (mask & y) | (~mask & z);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4L,5L) = 1L.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
long isLessOrEqual(long x, long y) {
  long yMinusx = y + (~x + 1);
  long index = 1L << 63;
  long same = !((index & x) ^ (index & y)); // to check if x and x have the same sign, same return 1, different return 0
  long resultsame = !(yMinusx & index); // if x and y are positive, y - x > 0, return 1
  long xLeft = x & index; // take the signed bit of x
  long yLeft = y & index; // take the signed bit of y
  /*
  * if xLeft negative(100000), y positive(000000), reverse xLeft(which is 011111....) then and yLeft,then(00000) !, return 1
  * if xLeft positive(000000), y negative(100000), reverse xLeft(which is 111111....) then and yLeft,then(10000) !, return 0
  */
  long resultdiff = !(~xLeft & yLeft);
  return (same & resultsame) | (~same & resultdiff);
}
//4
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples:
 *    trueThreeFourths(11L) = 8
 *    trueThreeFourths(-9L) = -6
 *    trueThreeFourths(4611686018427387904L) = 3458764513820540928L (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
long trueThreeFourths(long x)
{
	long mask = 0x3; // last two digit
	long sign = x >> 63; // signal to justy positive or negative
	long result = (x >> 2) + (x >> 1); // original result
	long remainder = x & mask; // the remainder of x/4
  long remainder1 = !!((remainder & sign) ^ 0L);
  long remainder2 = !(remainder ^ mask);
	return result + remainder1 + remainder2;
  // long temp = x >> 1;
  // long absT = (((temp) & ~sign)|((~temp + 1 ) & sign));
  // long absTT = ((absT) >> 1);
  // long result1 = absTT + absTT + absTT;
  // long result = ((result1) & ~sign) | ((~result1 + 1) & sign);

  // long absX = (((x) & ~sign)|((~x + 1 ) & sign)); // positive select self, negative select reverse, return absolute
  // long result1 = (absX + (1L << 2) + (~1L + 1L)) >> 2; // (absX + 2 ^ 2 -1) / (2 ^ 2)
  // long result2 = result1 + result1 + result1; // multiply 3 times
  // long result = (result2 & sign) | ((~result2 + 1) & ~sign); // restore
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5L) = 2, bitCount(7L) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
/* idea came from https://www.viseator.com/2017/06/18/CS_APP_DataLab/
 * the "count" will iterate
*/
long bitCount(long x) {
  long count; 
  long mask6 = (((((long)0xFF << 8) + (long)0xFF) << 16) + (((long)0xFF << 8) + (long)0xFF)); 
  long mask5 = mask6 ^ (mask6 << 16); 
  long mask4 = mask5 ^ (mask5 << 8); // create mask 0000000011111111;
  long mask3 = mask4 ^ (mask4 << 4); // create mask 0000111100001111;
  long mask2 = mask3 ^ (mask3 << 2); // create mask 0011001100110011;
  long mask1 = mask2 ^ (mask2 << 1); // create mask 0101010101010101
  count = (x & mask1) + ((x >> 1) & mask1);
  count = (count & mask2) + ((count >> 2) & mask2);
  count = (count & mask3) + ((count >> 4) & mask3);
  count = (count & mask4) + ((count >> 8) & mask4);
  count = (count & mask5) + ((count >> 16) & mask5);
  count = (count & mask6) + ((count >> 32) & mask6);
  return count;
}
/*
 * isPalindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPalindrome(0x6F0F0123c480F0F6L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
// idea came from https://stackoverflow.com/questions/12357876/reverse-unsigned-short-vector-using-bitwise-operator
long isPalindrome(long x) {
  long mask6 = (((((long)0xFF << 8) + (long)0xFF) << 16) + (((long)0xFF << 8) + (long)0xFF)); 
  long mask5 = mask6 ^ (mask6 << 16); 
  long mask4 = mask5 ^ (mask5 << 8); // create mask 0000000011111111;
  long mask3 = mask4 ^ (mask4 << 4); // create mask 0000111100001111;
  long mask2 = mask3 ^ (mask3 << 2); // create mask 0011001100110011;
  long mask1 = mask2 ^ (mask2 << 1); // create mask 0101010101010101
  long x1 = x;
  long x2 = x;
  x1 = x1 << 32 | ((x1 >> 32) & mask6);
  x1 = ((x1 & mask5) << 16) | ((x1 >> 16) & mask5);
  x1 = ((x1 & mask4) << 8) | ((x1 >> 8) & mask4);
  x1 = ((x1 & mask3) << 4) | ((x1 >> 4) & mask3);
  x1 = ((x1 & mask2) << 2) | ((x1 >> 2) & mask2);
  x1 = ((x1 & mask1) << 1) | ((x1 >> 1) & mask1);
  return !(x1 ^ x2);

}
/*
 * integerLog2 - return floor(log base 2 of x), where x > 0
 *   Example: integerLog2(16L) = 4L, integerLog2(31L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 60
 *   Rating: 4
 */
long integerLog2(long x) {
/*
 * I used Binarysearch to figure out this problem.
 * Firstly, the result is 0. And then first search
 * is on 32th. If 32th and front has one, then b5 return 1,
 * which means there is "1" in 32th or in the front of 32th, else means no one.
 * If 32th or front has one, then I binarysearch the next part, which is 
 * (64 - 32) / 2 = 16. (32 + 16) = 48. Then, I found 48th. Keep going until 63th
*/
  long result = 0;
  long b5 = !!(x >> 32);
  long b4 = 0;
  long b3 = 0;
  long b2 = 0;
  long b1 = 0;
  long b0 = 0;
  result = b5 << 5;
  b4 = !!(x >> (16 + result));
  result = result + (b4 << 4);
  b3 = !!(x >> (8 + result));
  result = result + (b3 << 3);
  b2 = !!(x >> (4 + result));
  result = result + (b2 << 2);
  b1 = !!(x >> (2 + result));
  result = result + (b1 << 1);
  b0 = !!(x >> (1 + result));
  result = result + b0;
  return result;
}
//float
/* 
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
  unsigned mask = ~(0x80000000);
  unsigned fmask = (uf >> 23) & ((1 << 8) - 1); // get uf exp field
  unsigned gmask = (ug >> 23) & ((1 << 8) - 1); // get ug exp field
  unsigned frac_mask = 0x007FFFFF; // get the fraction field
  unsigned uff = uf & frac_mask;
  unsigned ugf = ug & frac_mask;
  if (((fmask == 0xFF) && ((uff) != 0)) || ((gmask == 0xFF) && ((ugf) != 0))) {
    return 0;
    } 
  if (((uf & mask) == 0) && ((ug & mask) == 0)){
    return 1; // denormalized
  }
  return uf == ug; // true
}
/* 
 * floatScale4 - Return bit-level equivalent of expression 4*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale4(unsigned uf) {
  int time = 2;
  unsigned sf = (1 << 31) & uf; // signal field
  unsigned exp = (uf >> 23) & ((1 << 8) - 1); // exp field
  unsigned frac_mask = 0x007FFFFF;
  unsigned frac = uf & frac_mask; // get fraction field
  unsigned denormalize = ((exp + 1) >> 8) & 1; // if denormalize return 1, else 0
  if (!(frac | exp) || denormalize) {
    return uf; // When argument is NaN, return argument
    }
  while(time--){ // time 2, time 2
    if (exp != 0){ // denormalized
      if (exp != 0xFF){ // normalized
        exp = exp + 1; // time 2 = exp + 1
      } 
      if (exp == 0xFF){ // special exp = 11111111
        frac = 0; // NaN
      }
    }else { // exp == 0, denormalized
    // fraction shift
      if (!!(frac & (1 << 22))){
        frac = frac << 1;
        exp = 1;
    }else {
      frac = frac << 1;
      exp = 0;
      }
    }
  }

frac = frac & frac_mask;
exp = exp & 0xFF;
return sf + (exp << 23) + frac;
}
/* 
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
/*
 * Idea came from https://stackoverflow.com/questions/40836522/c-bit-level-int-to-float-conversion-unexpected-output
*/
unsigned floatUnsigned2Float(unsigned u) {
  int temp, a, b, c, exp, biasing, len_frac, greatest_bit;
  if (!!u){
    len_frac = 23;
    greatest_bit = 31;
    while(!((1 << greatest_bit) & u)){ // to calculate how many 0 in u, and return the real number of bit.
      greatest_bit--;
    }
    biasing = 127;
    temp = len_frac - greatest_bit;
    exp = biasing + greatest_bit; // because the exp field = 2^(exp + 127)
    if (temp >= 0){
      u = u << temp;
    } else {
      temp = -temp;
      // https://stackoverflow.com/questions/8981913/how-to-perform-round-to-even-with-floating-point-numbers
      a = u & (1 << temp);
      b = u & (1 << (temp - 1));
      c = u << (33 - temp);
      u = u >> temp;
      // (round to even or is even)
      u += b && (a || c);
    }
    u = (exp << len_frac) + (u & 0x007FFFFF); // add all to get unsigned float
  }
  return u;
}
