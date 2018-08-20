#include <stdio.h>
#include <string.h>

int main() {
    /* char *strstr(const char *haystack, const char *needle); */
    /* finds the first occurrence of the substring needle in the
     * string haystack. return a pointer to the beginning of the
     * located substring, or NULL if the substring is not found. */
    printf("strstr(\"number\", \"number\"): %s\n",
           strstr("number", "number"));
    printf("strstr(\"number2\", \"number\"): %s\n",
           strstr("number2", "number"));
    /* This returns the null pointer. */
    printf("strstr(\"number\", \"number2\"): %s\n",
           strstr("number", "number2"));

    printf("strstr(\"expr|number|regex\", \"number\"): %s\n",
           strstr("expr|number|regex", "number"));

    printf("strcmp(\"expr|number|regex\", \"number\"): %i\n",
           strcmp("expr|number|regex", "number"));
    printf("strcmp(\"number\", \"number\"): %i\n",
           strcmp("number", "number"));
    printf("strcmp(\"number\", \"expr|number|regex\"): %i\n",
           strcmp("number", "expr|number|regex"));

    return 0;
}
