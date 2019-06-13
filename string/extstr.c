#include <stdio.h>

char *impl_strcat(char *s1, const char *s2) {
    char *p = s1;
    while(*p) p++;
    while((*p++ = *s2++));
    return s1;
}

char *ext_repeat(char *dist, const char *repeat, const int times) {
    char *p = dist;

    while(*p) p++;

    const char *pos = repeat;

    for (int i = 0; i < times; i++) {
        while ((*p++ = *repeat++));
        p--;
        repeat = pos;
    }
    *p++ = '\0';

    return dist;
}
