#ifndef STD_TYPE_H
#define STD_TYPE_H


/*Only Positive Data*/

typedef char       					S8 ;
typedef unsigned char       		u8 ;
typedef unsigned short int       	u16;
typedef unsigned long int       	u32;
typedef unsigned long long int      u64;

/*Positive Data & negative data*/

typedef signed char       			s8 ;
typedef signed short int       		s16;
typedef signed long  int       		s32;
typedef signed long long int    	s64;


/*Only Floating Data*/

typedef float       				f32;
typedef double       				f64;


/*boolean*/
typedef enum BOOL
{
	false,
	true
}BOOL;

#endif //STD_TYPE_h