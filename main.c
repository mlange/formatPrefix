/*    
    
    CC    Last digit of century number [0,2] (the year divided by 100
          and truncated to an integer as a decimal number).  Only
          supported up to the year 2299.

    YY    Year within century [00,99].  Single digits are preceeded
          by 0.

    WW    Week number of year [00,53], with Monday as the first day
          of week 1.  Single digits are preceeded by 0.

    JJJ   Day number of year [001,366].  Single digits are preceded
          by 0.

    123   Fixed number(s) can also be used.  These are usually used to
          specify a plant or facility code, but could be used for any
          other reason as well.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

static char *holders[] = {"cc", "yy", "ww", "jjj", NULL};
static char *formats[] = {"%C", "%y", "%w", "%j",  NULL};

char *zeropad(char *out, char *in, int outlength)
{
    int inlength,
        numzeros;

    /* Just make a copy if the input is already as long as the output. */
    inlength = strlen(in);
    if (inlength >= outlength)
        return strcpy(out, in);

    /* Determine how much padding we'll need to do. */
    numzeros = outlength - inlength;

    /* Build the output string. */
    memset(out, '0', numzeros);
    strcpy(out + numzeros, in);

    return out;
}

char *format(char *string)
{
    long ii = 0;

    char *ptr;

    time_t now;
    struct tm *times;

    /* Get the current time. */
    time(&now);
    times = localtime(&now);

    /* Cycle through every placeholder we support. */
    while (holders[ii])
    {
	/* Have we found this placeholder in the string? */
	if ((ptr = strstr(string, holders[ii])) != NULL)
	{
	    char value[10],
	         valuePadded[10];
   
	    /* Get the value associated with this format. */
	    strftime(value, sizeof value, formats[ii], times);

	    /* Zero-pad the value. */
            zeropad(valuePadded, value, strlen(holders[ii]));

	    /* Copy the value over the top of the placeholder. */
	    memcpy(ptr, valuePadded, strlen(valuePadded));
	}

	ii++;
    }

    return string;
}

int main(int argc, char *argv[])
{
    int ii = 0;

    char buffer[20];

    if (argv[1])
        strcpy(buffer, argv[1]);
    else
        strcpy(buffer, "1yyjjj");

    printf("FORMAT: %s\n", buffer);

    format(buffer);

    printf("RESULT: %s\n", buffer);

    exit(0);
}

