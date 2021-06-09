#include <math.h>
#include <stdio.h>

int main()
{
    double f;
    scanf("%lf",&f);
    printf("%f\n", round(f));  //math.h を include したので、log が使用できる。

    return 0;
}
