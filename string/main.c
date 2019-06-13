#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "extstr.h"

#define N 255

int impl_concat_char_array() {
    char s1[N] = "Snoopy";
    char s2[] = "Charlie Brown";

    impl_strcat(s1, s2);
    printf("impl_char_array: s1 + s2 : %s\n", s1);

    return 0;
}


int str_repeat() {
    char s[3] = "";
    char rs[] = "rx";

    ext_repeat(s, rs, 2);
    printf("%s\n", s);

    return 0;
}


int concat_char_array() {
    char s1[N] = "Snoopy";
    char s2[] = "Charlie Brown";

    strcat(s1, s2);
    printf("char_array: s1 + s2 : %s\n", s1);

    return 0;
}


int concat_char_pointer() {
    char s1[N] = "Snoopy";
    char *s2 = "Charlie Brown";

    strcat(s1, s2);
    printf("char_pointer: s1 + s2 : %s\n", s1);

    return 0;
}





int main(void) {
    concat_char_pointer();
    concat_char_array();
    impl_concat_char_array();
    str_repeat();

    return EXIT_SUCCESS;
}
