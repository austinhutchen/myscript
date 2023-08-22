

// 4 bit words
int bitAnd(int x, int y) {
  // demorgan's law
  return ~(~x | ~y);
}
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  // CONSTRUCTS AN INITIAL 1 BYTE word OF ALL EVEN BITS E.G. 1001
  int word = 0x55;
  // shifts the word left to copy until the maximum of 32 bits == 4 bytes is
  // reached! same as copying over the even word to each set of bytes and doing
  // +=
  word = word | word << 8;
  word = word | word << 16;
  return word;
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  // if x is INTMIN, then (x+x) will underflow to 0 because x is negative. so
  // !(x+x)=1 !INTMIN must be 0, so we add !(x) as a condition using the bitwise
  // AND bind
  // !(0)^!(INTMIN) == 1^0
  // 1^0 == 1, so this will return 1 if these conditions are fulfilled, meaning
  // x = TMIN
  return !(x + x) ^ !(x);
}
/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  //
  x = x & (x >> 16); // 1 shift
  x = x & (x >> 8);  // 2 shifts
  x = x & (x >> 4);  // 3 shifts
  x = x & (x >> 2);  // 4 shifts
  // now compare x in the final bit position with  1 , if it made it through
  // every comparison, then return 1. Else, it will return 0 because of the
  // above shift conditions needing to pass a whole floor division by 2.
  return x & 0x1;
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  // (8 bits = 1 byte)
  // multiplies x by a factor of 1/8n ,dividing bitwise x by n sets of 8 bits ==
  // n bytes then user masking to grab the resultant full word
  // x/(n*8)
  int ans = x >> (n << 3);
  // pulls out lower 8 bits using 0xff, a mask of 8 ones
  return (ans & 0xFF);
}
/*
 * isNegative - return 1 if x < 0, return 0 otherwise
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  // shift x to check the last bit, which determines sign
  // a sign of 1 indicates negative, do an AND operation to compare with 1
  int sign = x >> 31;
  return sign & 1;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // double negation of x to get a boolean truth result if x is nonzero (meaning
  // it is true) ANY VALUE OF X OTHER THAN 0 IS TRUE
  int ans;
  // if double negation X is true, we get the twos complement of 0, which is all
  // 11111..==-1 this allows for x to be assigned to y using & operator
  // otherwise, we use ones complement to invert 0 into new mask (result of -1+1
  // in case that ~!!x is ~0+1==-1+1==0)
  x = ~(!!x) + 1;
  // twos complement of logical double negation of x gives -1 or 0, mask values
  // for y or z
  ans = (x & y) | (~x & z);
  // returned answer will be either y or z depending on the initial negation of
  // x
  return ans;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  int sign;
  int ans;
  int check;
  // grab sign
  x = ((x << 1) + x); // do x * 3
  sign = x >> 31;  // extract sign bit
  check = sign & 3;  // use for below
  // x+1 / 4 if neg
  // x / 4 if pos
  ans = ((x + check) >> 2);
  return ans;
}
/*
 ~0 == ~0000 == 1111 == 0xff == -1 = one's complement of 0
 ~0 + 1 == ~0000 +1 == 0xff+1 == -1+1 == 0 == two's complement of 0
 INTMAX= 0111..1
 -1= 1111...1 (because of overflow)
 INTMIN= ?

 * isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
  // x compared to its sign mask will yield a 1 if x is negative, because of
  // signed integers using 1 final ! operation will return 0 if x is negative
  // because of 1 sign mask and 1 if sign mask is 0
  return !(x >> 31);
}
/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x) {
  // meaning that x or -x shifted by 31 places needs to be nonzero
  // x or -x is checked for its sign by shifting by 31
  // x or -x must have a 1 in the sign bit (shifted by 31), so any nonzero value
  // will give 1
  return ((x | (~x + 1)) >> 31) & 1;
}
/*
 * leftBitCount - returns count of number of consective 1's in
 *     left-hand (most significant) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Rating: 4
 */
int leftBitCount(int x) {
  // Think of tempx as a "window" being shifted while the !~ pair tests that the
  // given byte string has consecutive ones. the given window MUST be equal to
  // -1 (ALL ONES) to be added to the total consecutive bits
  // !~(-1)=1 = TRUE (ONES IN GIVEN WINDOW ARE CONSECUTIVE)
  int tempx = x;  
  int ans;
  int shift;
  // check if x==-1
  int check = !(~x);
  // add first 16 bits to our result (if they exist)
  // shifting by 4 adds 16 bits to our total because 1<<4 = 16
  ans = !(~(tempx >> 16)) << 4;
  // shift by a factor of 0 if tempx is small, because the most significant
  // checked bits have zero 1s so far shift tempx to continue checking by a
  // factor of 1 or 0
  tempx = tempx << ans;
  // shift out 8 bits,
  shift = !(~(tempx >> 24)) << 3;
  tempx = tempx << shift;
  // ans | shift is the same as ans+=consecutive bits to keep total the same
  ans = ans | shift;
  // shift out 4 bits
  shift = !(~(tempx >> 28)) << 2;
  tempx = tempx << shift;
  ans = ans | shift;
  // shift out 2 bits
  shift = !(~(tempx >> 30)) << 1;
  tempx = tempx << shift;
  ans = ans | shift;
  // check the last bit
  ans = ans ^ (1 & ((tempx >> 31)));
  // final round towards zero if we initially had x=-1
  return ans + check;
}

/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x) {
  // To get the rightmost two bits in number N, we perform bitwise AND (&) with
  // 3 because 3 in binary is 0011
  int rmdr = x & 3;
  int sign = x >> 31;
  x = x >> 2; // x/4
  x = x + (x << 1);   // x* 3
  // let the overflow happen first with x.
  // THEN
  //---->rmdr=(rmdr *3 + 3(if negative))/4
  // x+ rmdr fixes overflow
  rmdr = ((rmdr + (rmdr << 1)) + (sign & 3));
  // divide rmdr by 4
  rmdr >>= 2;
  x = x + rmdr;
  return x;
}
/*
 * Extra credit
 */
/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) { return 0xff; }
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) { return 2; }