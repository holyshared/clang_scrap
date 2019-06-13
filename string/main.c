#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define N 256


int concat_char_array() {
    char s1[N] = "Snoopy";
    char s2[] = "Charlie Brown";

    strcat(s1, s2);
    printf("char_pointer: s1 + s2 : %s\n", s1);

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

    return EXIT_SUCCESS;
}
