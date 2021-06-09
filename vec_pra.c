#include "mms/mlx.h"
#include "vector_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592

int main()
{
    vector_t vec1 = {3.0f, 4.0f, 5.0f};
    vector_t vec2 = {6.0f, 7.0f, 8.0f};
    vector_t vec3;
    vector_t vec4;
    vector_t vec5;

    float hoge, piyo, foo, bar, fuga, buzz;

    hoge = SQR(3.14f);
    piyo = 2.0f;
    
    printf("smaller %f\n",MIN(hoge, piyo));
    printf("bigger %f\n",MAX(hoge, piyo));

    hoge = SQR(3.14);
    piyo = 2;
    
    printf("smaller %f\n",MIN(hoge, piyo));
    printf("bigger %f\n",MAX(hoge, piyo));

    // printf("vec1 = %s\n", vector_str(&vec1));
    // printf("vec2 = %s\n", vector_str(&vec2));
    // vec3 = add(&vec1, &vec2);
    // //vec1 = mult(&vec1, 3);
    // //vec2 = mult(&vec2, 4);
    // vec4 = sub(&vec1, &vec2);
    // printf("vec1 + vec2 = %s\n", vector_str(&(vec3)));
    // printf("3vec1 - 4vec2 = %s\n", vector_str(&(vec4)));
    // normalize(&vec4);
    // printf("normalize(3vec1 - 4vec2) = %s\n", vector_str(&(vec4)));
    
    // printf("dot(vec1, vec2) = %f\n", dot(&vec1, &vec2));
    // cross(&vec5, &vec1, &vec2);
    // printf("cross(vec1, vec2) = %s\n", vector_str(&vec5));


    //system("leaks a.out");
}