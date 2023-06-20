#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

main()
{
		for(float celsius = LOWER; celsius <= UPPER; celsius += STEP)
		{
				printf("%3.0f %6.1f\n", celsius, ((9.0/5.0) * celsius) + 32);
		}
}