#include <string.h>
#include <stdbool.h>

#define MAX_STRLEN 1024

size_t strlen(const char* str) {
    size_t len = 0;
    for (size_t i = 0; i < MAX_STRLEN; i++) {
        if ( str[i] == '\0' ) {
            len = i;
            break;
        }
    }
    return len;
}

void swap(char* a, char* b) {
    char tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse(char* str, size_t length) {
    size_t start = 0;
    size_t end = length - 1;
    
    while (start < end) {
        swap( str + start++, str + end-- );
    }
}

char* itoa(int num, char* str, int base) {
    int i = 0;
    bool isNegative = false;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        isNegative = true;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    reverse(str, i);

    return str;
}


