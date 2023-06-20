#include <stdio.h>

/*Produces Farenheit to Celcius Table in which
 F = 0, 20, 40, ..., 300*/

/* C = (5/9)(F - 32) */
main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("  F to  C\n");

    while(fahr <= upper)
    {
        celsius = (5.0/9.0) * (fahr - 32.0); // See formula on line 6.
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr += step;
    }

    printf("\n  F to  C\n");

    while(fahr >= lower)
    {
        celsius = (5.0/9.0) * (fahr - 32.0); // See formula on line 6.
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr -= step;
    }
}