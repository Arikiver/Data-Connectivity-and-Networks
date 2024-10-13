#include <stdio.h>
#include <stdlib.h> // For malloc() and free()
#include <string.h>

// Function to perform XOR operation
void xorOperation(char dividend[], char divisor[], int start) {
    for (int i = 0; i < strlen(divisor); i++) {
        dividend[start + i] = dividend[start + i] == divisor[i] ? '0' : '1';
    }
}

// Function to perform the division step for CRC
void crcDivision(char dividend[], char divisor[], int data_len, int div_len) {
    for (int i = 0; i <= data_len - div_len; i++) {
        if (dividend[i] == '1') {
            xorOperation(dividend, divisor, i);
        }
    }
}

// Function to calculate CRC and return the remainder
void calculateCRC(char data[], char divisor[], char remainder[]) {
    int data_len = strlen(data);
    int div_len = strlen(divisor);
    
    // Allocate memory dynamically for the temporary array
    char *temp = (char *)malloc((data_len + div_len) * sizeof(char));
    strcpy(temp, data);
    
    for (int i = 0; i < div_len - 1; i++) {
        temp[data_len + i] = '0';
    }
    temp[data_len + div_len - 1] = '\0';
    
    // Perform CRC division
    crcDivision(temp, divisor, data_len + div_len - 1, div_len);
    
    // The remainder is the last part of the result
    strncpy(remainder, &temp[data_len], div_len - 1);
    remainder[div_len - 1] = '\0';
    
    // Free the allocated memory
    free(temp);
}

int main() {
    char data[100], divisor[100], remainder[100];
    
    // Input data and divisor (polynomial)
    printf("Enter the data bits: ");
    scanf("%s", data);
    printf("Enter the divisor (polynomial): ");
    scanf("%s", divisor);
    
    // Calculate CRC
    calculateCRC(data, divisor, remainder);
    
    printf("CRC remainder: %s\n", remainder);
    
    // Append the remainder to the original data
    strcat(data, remainder);
    printf("Transmitted frame (data + CRC): %s\n", data);
    
    return 0;
}
