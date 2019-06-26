#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ext_string.h"

#define N 255

int test_impl_concat_char_array() {
    char s1[N] = "Snoopy";
    char s2[] = "Charlie Brown";

    impl_strcat(s1, s2);
    printf("impl_char_array: s1 + s2 : %s\n", s1);

    return 0;
}


int test_str_repeat() {
    char s[3] = "";
    char rs[] = "rx";

    str_repeat(s, rs, 2);
    printf("%s\n", s);

    return 0;
}

int test_str_repeat_join() {
    char s1[100] = "";
    char s2[100] = "";
    char *rs = "?";
    char *ds = ", ";

    str_repeat_join(s1, rs, ds, 2);
    printf("%s\n", s1);

    str_repeat_join(s2, rs, ds, 5);
    printf("%s\n", s2);

    return 0;
}


int test_concat_char_array() {
    char s1[N] = "Snoopy";
    char s2[] = "Charlie Brown";

    strcat(s1, s2);
    printf("char_array: s1 + s2 : %s\n", s1);

    return 0;
}


int test_concat_char_pointer() {
    char s1[N] = "Snoopy";
    char *s2 = "Charlie Brown";

    strcat(s1, s2);
    printf("char_pointer: s1 + s2 : %s\n", s1);

    return 0;
}





int main(void) {
    test_concat_char_pointer();
    test_concat_char_array();
    test_impl_concat_char_array();
    test_str_repeat();
    test_str_repeat_join();

    return EXIT_SUCCESS;
}
