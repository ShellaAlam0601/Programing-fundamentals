#include <stdio.h>

/* Returns the sum of proper divisors of x (all divisors except x itself) */
int sumProperDivisors(int x)
{
    int i, sum;

    if (x <= 1)
        return 0;

    sum = 1;                       /* 1 divides every number */
    for (i = 2; i * i <= x; i++)   /* test only up to square root */
    {
        if (x % i == 0)
        {
            sum += i;              /* add the small divisor */
            if (i != x / i)        /* do not add a square root twice */
                sum += x / i;      /* add the big divisor */
        }
    }
    return sum;
}

int main()
{
    int n, a, b, pairs = 0;

    do
    {
        printf("Enter n: ");
        scanf("%d", &n);
    } while (n < 1);

    printf("Amicable pairs up to %d:\n", n);

    for (a = 2; a <= n; a++)
    {
        b = sumProperDivisors(a);

        /* b > a  -> smaller number first, each pair once, and a != b */
        if (b > a && b <= n && sumProperDivisors(b) == a)
        {
            printf("(%d, %d)\n", a, b);
            pairs++;
        }
    }

    if (pairs == 0)
        printf("No amicable pairs found up to %d.\n", n);
    else
        printf("Total pairs: %d\n", pairs);

    return 0;
}
