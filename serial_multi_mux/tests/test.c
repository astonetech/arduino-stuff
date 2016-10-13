/**
 * Author: Leo Vidarte <http://nerdlabs.com.ar>
 *
 * This is free software:
 * you can redistribute it and/or modify it
 * under the terms of the GPL version 3
 * as published by the Free Software Foundation.
 */

#include <stdio.h>

int units [2][4] = {{1, 2, 4, 10}, {5, 6, 7, 11}};

int main(int argc, char **argv) {
    int i;
    for (i = 0; i < 2; i++) {
        printf("%d %d %d (%d)\n", units[i][0], units[i][1], units[i][2], units[i][3]);
    }
    return 0;
}
