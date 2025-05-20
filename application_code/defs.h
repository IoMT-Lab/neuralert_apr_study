#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long __time64_t;
typedef __time64_t	da16x_time_t;

typedef signed char			CHAR;
typedef unsigned char		UCHAR;
typedef signed short		SHORT;
typedef unsigned short		USHORT;
typedef signed int			INT;
typedef unsigned int		UINT;
typedef signed long			LONG;
typedef unsigned long		ULONG;

#define __TIME64__

#define MAX_TIMESYNC_LENGTH				80

typedef long             BaseType_t;

#define pdFALSE                                  ( ( BaseType_t ) 0 )
#define pdTRUE                                   ( ( BaseType_t ) 1 )

#define SAMPLES_PER_FIFO				32
#define FIFO_BLOCKS_PER_PACKET 5 
#define MAX_SAMPLES_PER_PACKET	(FIFO_BLOCKS_PER_PACKET * SAMPLES_PER_FIFO)

typedef struct
{
	int16_t Xvalue;					//!< X-Value * 1000
	int16_t Yvalue;					//!< Y-Value * 1000
	int16_t Zvalue;					//!< Z-Value * 1000
#ifdef SAVEMAGNITUDE
	int16_t Magvalue;				//!< magnitude (sqrt(x^2 + y^2 + z^2) * 1000
#endif
#ifdef __TIME64__
	__time64_t accelTime;               //!< time when accelerometer data taken
#else
	time_t accelTime;
#endif /* __TIME64__ */
} accelDataStruct;

#define PRINTF printf