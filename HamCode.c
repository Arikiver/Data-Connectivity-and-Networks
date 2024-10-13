#include <stdio.h>
#include <string.h>
#include <math.h>

int input[32];
int code[32];
int ham_calc(int, int);

void main() {
    int n, i, p_n = 0, c_l, j, k;
    char data_word[33]; // To store the input binary string

    printf("Please enter the length of the Data Word: ");
    scanf("%d", &n);
    
    printf("Please enter the Data Word (as a binary string):\n");
    scanf("%s", data_word); // Get the entire binary string at once

    // Convert the binary string to an integer array
    for (i = 0; i < n; i++) {
        if (data_word[i] == '1') {
            input[i] = 1;
        } else {
            input[i] = 0;
        }
    }

    i = 0;
    while (n > (int)pow(2, i) - (i + 1)) {
        p_n++;
        i++;
    }

    c_l = p_n + n;

    j = k = 0;
    for (i = 0; i < c_l; i++) {
        if (i == ((int)pow(2, k) - 1)) {
            code[i] = 0;
            k++;
        } else {
            code[i] = input[j];
            j++;
        }
    }

    // Calculate parity bits
    for (i = 0; i < p_n; i++) {
        int position = (int)pow(2, i);
        int value = ham_calc(position, c_l);
        code[position - 1] = value;
    }

    // Output the calculated code word
    printf("\nThe calculated Code Word is: ");
    for (i = 0; i < c_l; i++) {
        printf("%d", code[i]);
    }
    printf("\n");

    // Input the received code word
    printf("Please enter the received Code Word (as a binary string):\n");
    scanf("%s", data_word);

    // Convert received binary string to code array
    for (i = 0; i < c_l; i++) {
        if (data_word[i] == '1') {
            code[i] = 1;
        } else {
            code[i] = 0;
        }
    }

    // Check for errors in the received code word
    int error_pos = 0;
    for (i = 0; i < p_n; i++) {
        int position = (int)pow(2, i);
        int value = ham_calc(position, c_l);
        if (value != 0) {
            error_pos += position;
        }
    }

    if (error_pos == 0) {
        printf("The received Code Word is correct.\n");
    } else {
        printf("Error at bit position: %d\n", error_pos);
    }
}

int ham_calc(int position, int c_l) {
    int count = 0, i, j;
    i = position - 1;
    while (i < c_l) {
        for (j = i; j < i + position; j++) {
            if (code[j] == 1) {
                count++;
            }
        }
        i = i + 2 * position;
    }
    return (count % 2 == 0) ? 0 : 1;
}
