#include <stdio.h>
#include <time.h>

int main(void)
{
    clock_t start = clock();
    long long sum = 0;

    for (int repeat = 0; repeat < 1000; repeat++)
    {
        for (int i = 0; i < 999; i++)
        {
            for (int j = 0; j < 999; j++)
            {
                sum += i + j;
            }
        }
    }

    clock_t end = clock();

    printf("sum = %lld\n", sum);
    printf("time = %.6f seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}