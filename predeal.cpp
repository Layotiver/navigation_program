#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;

char buffer[1 << 20], *p1, *p2;

inline char gc()
{
    return p1 == p2 && (p2 = (p1 = buffer) + fread(buffer, 1, 1 << 20, stdin), p1 == p2) ? EOF : *p1++;
}

inline void re(int &a)
{
    char c;
    while (!isdigit(c = gc()))
    {
        if (c == EOF)
        {
            a = EOF;
            return;
        }
    }
    a = c - '0';
    while (isdigit(c = gc()))
        a = a * 10 + c - '0';
    return;
}

int main()
{
    freopen("distance_info.txt", "r", stdin);
    freopen("dis.bit", "wb", stdout);
    int a;
    while (1)
    {
        re(a);
        if (a == -1)
            break;
        fwrite(&a, sizeof(int), 1, stdout);
    }
    return 0;
}