#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

bool SetGain(float f);
int16_t Amplify(int16_t s);

static bool init_all_tones();


//浮点数乘以2，有0判断    //float== 1符号位+8阶码+23尾数
__inline float xmul2f(float d) {
  union {
    float floatval;
    int intval;
  } uflint;
  uflint.floatval = d;
  if (uflint.intval & 0x7FFFFFFF) { // if f==0 do nothing
    uflint.intval += 1 << 23; // add 1 to the exponent  //先移位再相加，阶码的最小位为第23位，阶码+1相当于乘2
  }
  return uflint.floatval;
}
//浮点数除以2，有0判断
__inline float xdiv2f(float d) {
  union {
    float floatval;
    int intval;
  } uflint;
  uflint.floatval = d;
  if (uflint.intval & 0x7FFFFFFF) { // if f==0 do nothing
    uflint.intval -= 1 << 23; // sub 1 from the exponent  //先移位再相减，阶码-1相当于除以2
  }
  return uflint.floatval;
}
//浮点数除以任意整数n，有0判断
__inline float xdivf(float d, int n) {
  union {
    float floatval;
    int intval;
  } uflint;
  uflint.floatval = d;
  if (uflint.intval & 0x7FFFFFFF) { // if f==0 do nothing
    uflint.intval -= n << 23; // add n to the exponent
  }
  return uflint.floatval;
}

//双精度浮点数除以2，有0判断
__inline double xdiv2d(double d) {
  union {
    double doubleval;
    int64_t intval;
  } uflint;
  uflint.doubleval = d;
  if (uflint.intval & 0x7FFFFFFFFFFFFFFF) { // if f==0 do nothing
    uflint.intval -= 1 << 52; // sub 1 from the exponent  //先移位再相减，阶码-1相当于除以2
  }
  return uflint.doubleval;
}


#endif
