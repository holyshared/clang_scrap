#include <stdio.h>

char *impl_strcat(char *s1, const char *s2) {
    char *p = s1;
    while(*p) p++;
    while((*p++ = *s2++));
    return s1;
}

char *str_repeat(char *dist, const char *repeat, const int times) {
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

/**
 * ext_repeat_join(dist, "?", ",", 3);
 */
char *str_repeat_join(char *dist, const char *repeat, const char *delimiter, const int times) {
    char *p = dist;
    while(*p) p++;

    const char *rpos = repeat;
    const char *dpos = delimiter;

    for (int i = 0; i < times - 1; i++) {
        while ((*p++ = *repeat++));
        p--;
        while ((*p++ = *delimiter++));
        p--;

        repeat = rpos;
        delimiter = dpos;
    }
    while ((*p++ = *repeat++));
    p--;
    *p++ = '\0';

    return dist;
}
