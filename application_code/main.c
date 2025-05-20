#include "defs.h"

#define MAX_JSON_STRING_SIZE 10000 // double our usual packet size
char mqttMessage[MAX_JSON_STRING_SIZE];


static accelDataStruct accelXmitData[MAX_SAMPLES_PER_PACKET];

/**
 *******************************************************************************
 * @brief Process similar to strncpy but makes sure there is a
 * terminating null
 * copies up to (max_len - 1) characters and adds a null terminator
 * *******************************************************************************
 */
void user_text_copy(UCHAR *to_string, const UCHAR *from_string, const int max_len)
{
	int i;
	for (i=0; (i < (max_len-1)); i++)
	{
		if(from_string[i] == 0x00)
			break;
		else
			to_string[i] = from_string[i];
	}
	to_string[i] = 0x00;
}

/**
 *******************************************************************************
 * @brief Helper function to create a printable string from a long long
 *        because printf doesn't handle long longs
 *        Format is just digits.  No commas or anything.
 *******************************************************************************
 */
void time64_string (char *timestamp_str, const __time64_t *timestamp)
{
	__time64_t timestamp_copy;
	char nowStr[20];
	char str2[20];

	// split into high order and lower order pieces
	timestamp_copy = *timestamp;
	uint64_t num1 = ((timestamp_copy/1000000) * 1000000);	// millions
	uint64_t num2 = timestamp_copy - num1;
	uint32_t num3 = num2;

	sprintf(nowStr,"%03ld",(uint32_t)(timestamp_copy/1000000));
	sprintf(str2,"%06ld",num3);
	strcat(nowStr,str2);
	strcpy(timestamp_str,nowStr);

}

/**
 *******************************************************************************
 * @brief Helper function to create a printable string from a long long
 *        time in msec, because printf doesn't handle long longs
 *******************************************************************************
 */
void time64_msec_string (char *time_str, const __time64_t *time_msec)
{

	ULONG time_milliseconds;
	ULONG time_seconds;
	ULONG time_minutes;
	ULONG time_hours;
	ULONG time_days;

	time_seconds = (ULONG)(*time_msec / (__time64_t)1000);
	time_milliseconds = (ULONG)(*time_msec
				  - ((__time64_t)time_seconds * (__time64_t)1000));
	time_minutes = (ULONG)(time_seconds / (ULONG)60);
	time_hours = (ULONG)(time_minutes / (ULONG)60);
	time_days = (ULONG)(time_hours / (ULONG)24);

	time_seconds = time_seconds % (ULONG)60;
	time_minutes = time_minutes % (ULONG)60;
	time_hours = time_hours % (ULONG)24;

	sprintf(time_str,
			"%u Days plus %02u:%02u:%02u.%03u",
		time_days,
		time_hours,
		time_minutes,
		time_seconds,
		time_milliseconds);
}

/**
 *******************************************************************************
 * @brief Helper function to create a printable string from a long long
 *        time in seconds, because printf doesn't handle long longs
 *******************************************************************************
 */
void time64_seconds_string(char *time_str, const __time64_t *time_msec)
{

	ULONG time_milliseconds;
	ULONG time_tenths;
	ULONG time_seconds;

	time_seconds = (ULONG)(*time_msec / (__time64_t)1000);
	time_milliseconds = (ULONG)(*time_msec
				  - ((__time64_t)time_seconds * (__time64_t)1000));
	// At this point, time_milliseconds is between 0 and 999
	// We want x.x format, round to nearest tenth
	// so - for instance, 849 becomes 899 becomes .8
	//                and 850 becomes 900 becomes .9

	PRINTF(" [time64_seconds_string] intermediate msec: %lu", time_milliseconds);

	time_tenths = time_milliseconds + (ULONG)50;
	PRINTF(" [time64_seconds_string] intermediate tenths before division: %lu", time_tenths);
	time_tenths = time_tenths / (ULONG)100;

	sprintf(time_str,
			"%u.%u seconds  %u milliseconds",
		time_seconds,
		time_tenths,
		time_milliseconds);
}




/**
 *******************************************************************************
 * @brief calculate the timestamp for all a sample read from the accelerometer FIFO
 *      by using it's relative position in the buffer.
 *
 *   FIFO_ts 			- is the timestamp assigned to the FIFO buffer when it was read
 *   FIFO_ts_prev		- is the timestamp assigned to the previous FIFO buffer when it was read
 *   offset         	- is the position in the FIFO
 *   FIFO_samples		- is the total number of samples in the FIFO
 *   adjusted_timestamp - is the calculated timestamp to be assigned to the sample
 *                    		with this offset
 *
 *******************************************************************************
 */
void calculate_timestamp_for_sample(const __time64_t *FIFO_ts, const __time64_t *FIFO_ts_prev, int offset,
	int FIFO_samples, __time64_t *adjusted_timestamp)
{
	//__time64_t scaled_timestamp;	// times 1000 for more precise math
	__time64_t scaled_timestamp_prev; // times 1000 for more precise math
	__time64_t scaled_offsettime;	// the time offset of this sample * 1000
	__time64_t adjusted_scaled_timestamp;
	__time64_t rounded_offsettime;

	__time64_t scaled_timestamp = *FIFO_ts;
	scaled_timestamp = scaled_timestamp * (__time64_t)1000;

	scaled_timestamp_prev = *FIFO_ts_prev;
	scaled_timestamp_prev = scaled_timestamp_prev * (__time64_t)1000;

	scaled_offsettime = ((scaled_timestamp - scaled_timestamp_prev) * (__time64_t)(offset + 1)) / (__time64_t)FIFO_samples;

	// offset time * 1000
	adjusted_scaled_timestamp = scaled_timestamp_prev + scaled_offsettime;
	// back to msec.  We round by adding 500 usec before dividing
	rounded_offsettime = (adjusted_scaled_timestamp + (__time64_t)500)
			                  / (__time64_t)1000;

	*adjusted_timestamp = rounded_offsettime;
}

void test_one() {
    UCHAR* from_string;
    UCHAR* to_string;

    from_string = "HELLO";
    to_string = malloc(20);

    PRINTF("BEFORE: {%s}, {%s}\n", from_string, to_string);
    user_text_copy(to_string, from_string, 20);
    PRINTF("AFTER: {%s}, {%s}\n", from_string, to_string);

    free(to_string);
}

int main(int argc, char** argv) {
    test_one();


    return 0;
}