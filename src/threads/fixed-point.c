#include "threads/fixed-point.h"
#include <debug.h>
#include <stddef.h>
#include <random.h>
#include <stdio.h>
#include <string.h>
#include "devices/timer.h"
// ana hna ana hna
#define SHIFT 14 // 2^14 = 16384

//convert integer n to fixed point
struct real int_to_real(int n)
{
     n= n<< SHIFT;
    struct real result;
    result.val = n;
    return result;
}

//convert fixed point x to integer (rounding towards zero)
int real_truncate(struct real x)
{
    int result = x.val >> SHIFT;
    return result;
}

//convert fixed point x to integer (rounding to nearest)
int real_round(struct real x)
{
    int num = x.val;
    num = num + 8192;
    int result = num >> SHIFT;
    return result;
}

// returns real x +  real y
struct real add_real_real(struct real x, struct real y)
{
    struct real result;
    result.val = x.val + y.val;
    return result;
}

// returns real x - real y
struct real sub_real_real(struct real x, struct real y)
{
    struct real result;
    result.val = x.val - y.val;
    return result;
}

// returns real x +  int n
struct real add_real_int(struct real x, int n)
{
    struct real y = int_to_real(n);
    struct real result;
    result.val = x.val + y.val;
    return result;
}

// returns real x - int n
struct real sub_real_int(struct real x, int n)
{
    struct real y = int_to_real(n);
    struct real result;
    result.val = x.val - y.val;
    return result;
}

// returns real x * real y
struct real mul_real_real(struct real x, struct real y)
{
   /* struct real result;
    int num = x.val * y.val;
    struct real num1;
    num1.val = num;
    num = real_truncate(num1);
    result.val = num;
    return result;*/
    struct real result;
    int64_t R=((int64_t)x.val) * y.val;
    R=R>>SHIFT;
    result.val=(int)R;
    return result;
}

// returns real x * int n
struct real mul_real_int(struct real x, int n)
{
    struct real result;
    result.val = x.val * n;
    return result;
}

// returns real x /real y
struct real div_real_real(struct real x, struct real y)
{
      /* struct real result ;
       result.val =(x.val<<SHIFT )/ y.val;
    // struct real result;
    // struct real num1 = int_to_real(x.val);
    // result.val = num1.val / y.val;
    return result;*/
    struct real result;
    int64_t R=((int64_t)x.val)<<SHIFT;
    R=R/y.val;
    result.val=(int)R;

    
    return result;
}

// returns real x / int n
struct real div_real_int(struct real x, int n)
{
    struct real result;
    result.val = x.val / n;
    return result;
}