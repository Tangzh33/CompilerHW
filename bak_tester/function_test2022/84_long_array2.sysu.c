#include <sysy/sylib.h>
int a[4096];

int f1(int b[])
{
    a[5] = 4000;
    a[4000] = 3;
    a[4095] = 7;
    b[a[4095]] = a[2216] + 9;
    return a[a[5]];
}

int main()
{
    int b[4][1024] = {{}, {1}, {2, 3}, {4, 5, 6}};
    int c[1024][4] = {{1, 2}, {3, 4}};
    putint(f1(c[0]));
    putch(10);
    return c[2][0];
}