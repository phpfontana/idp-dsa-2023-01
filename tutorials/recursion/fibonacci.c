# include <stdio.h>

int recursive_factorial (int fac)
{
    if (fac == 0)
        return 1;

    return fac * recursive_factorial(fac - 1);
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

