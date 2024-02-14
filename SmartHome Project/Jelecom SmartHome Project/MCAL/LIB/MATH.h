

#ifndef BIT_MATH_H
#define BIT_MATH_H


#include "STD_TYPE.h" 


#define SET_BIT(REG, BIT)    (REG |= (1<<BIT))

#define CLR_BIT(REG, BIT)    (REG &=~ (1<<BIT))

#define GET_BIT(REG, BIT)    ((REG>>BIT)&0x01)

#define TOGGLE_BIT(REG, BIT) (REG ^= (1<<BIT))

#define null 0

#endif // END_MATH