#include <stdio.h>

int main(void)
{
    typedef struct
    {
        float x;
        float y;
    } point; // 꼭 선언한 애를 뭐로 부를지 정해야함

    struct
    {
        point p1, p2, p3, p4;
    } rectangle;

    struct
    {
        point p1, p2, p3;
    } triangle;

    struct circle
    {
        point center;
        float radius;
    };
}
