#include <stdio.h>
#include <stdlib.h>

// remove, attach
float *Remove(float **, int);
float *attach(float **, float **);

int main(void)
{

    float poly1[10] = {8, 1, 0, 0, 3, 2, 0, 0, 0, 1}; // x^8 + 3*x^5 + 2*x^4 + 1, 맨 앞은 최고차항의 계수
    float poly2[10] = {7, 0, 1, 0, 5, 3, 0, 0, 0, 1}; // x^7 + 5*x^5 + 3*x^4 + 1

    return 1;
}

float *Remove(float **pol, int leadexp)
{
    *pol[0] = leadexp;
    int lenofpol = sizeof(*pol) / sizeof(int *);
    *pol[lenofpol - leadexp] = 0;
}

// coef, expon 을 그냥 배열로 다 보내버림
float *attach(float **pol1, float **pol2)
{
    float leadexp1 = *pol1[0];
    float leadexp2 = *pol2[0];

    int sizeofnewpol = sizeof(leadexp1) / sizeof(float *);

    float *resultpol;                 // empty array for new polynomial
    resultpol = malloc(sizeofnewpol); // resultpol의 선언까지 함. 이제 여기다 채워넣으면 된다

    int maxleadexp;

    maxleadexp = leadexp1;

    if (leadexp2 >= leadexp1)
    {
        maxleadexp = leadexp2;
    }

    for (int i = 0; i < maxleadexp + 1; i++)
    {
        resultpol[i] = *pol1[i] - *pol2[i];
    }
    return resultpol;
}
