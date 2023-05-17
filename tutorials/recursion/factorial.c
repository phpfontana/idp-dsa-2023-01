# include <stdio.h>

int factorial (int n)
{
    if (n == 0)
        return 1;
    
    return n *  factorial(n - 1);
}

int main(int argc, char const *argv[])
{
    int fac, res;
    printf("Enter the factorial value: ");
    fac = 4;
    res = factorial(fac);
    printf("%d! = %d\n", fac, res);
    return 0;
}
