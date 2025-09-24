#include <stdio.h>

// Converts an octal string to its binary representation
void oct_to_bin(const char *oct, char *out) {
    // First I get the length of the octal string and initialize an index for
    // the output
    int oct_len = strlen(oct);
    int out_index = 0;
    // Then I loop through each character in the octal string
    for (int i = 0; i < oct_len; i++) {
        // I convert the octal character to its integer value
        char oct_char = oct[i];
        int octal_digit = oct_char - '0';

        // I then convert the integer value to its 3-bit binary representation
        out[out_index++] = (octal_digit >> 2) & 1 ? '1' : '0';
        out[out_index++] = (octal_digit >> 1) & 1 ? '1' : '0';
        out[out_index++] = (octal_digit >> 0) & 1 ? '1' : '0';
    }
    out[out_index] = '\0';
}

// Converts an octal string to its hexadecimal representation
void oct_to_hex(const char *oct, char *out) {
    // First I create a buffer to store the binary representation of the octal
    // I also call oct_to_bin to fill this buffer
    char buffer[100];
    oct_to_bin(oct, buffer);

    // Then I get the length of the binary string and initialize an index for
    // the output
    int bin_len = strlen(buffer);
    int out_index = 0;
    // I pad the binary string with leading zeros to make its length a multiple
    // of 4
    if (bin_len % 4 != 0) {
        // I calculate the amount of padding needed
        int padding = 4 - (bin_len % 4);
        // Then I use memmove to shift the existing bits to the right and add
        // the padding
        memmove(buffer + padding, buffer, bin_len + 1);
        for (int i = 0; i < padding; i++) {
            buffer[i] = '0';
        }
        // Lastly I update the length of the binary string
        bin_len += padding;
    }
    // Now I convert each group of 4 bits to its hexadecimal representation
    for (int i = 0; i < bin_len; i += 4) {
        int hex_digit = 0;
        // I convert the 4 bits to their integer value
        for (int j = 0; j < 4; j++) {
            hex_digit = (hex_digit << 1) | (buffer[i + j] - '0');
        }
        // Then I convert the integer value to its hexadecimal character
        if (hex_digit < 10) {
            out[out_index++] = '0' + hex_digit;
        } else {
            out[out_index++] = 'A' + (hex_digit - 10);
        }
    }
    out[out_index] = '\0';

    // I remove any leading zeros from the hexadecimal output
    if (out[0] == '0' && out[1] != '\0') {
        memmove(out, out + 1, strlen(out + 1) + 1);
    }
}

// Converts a hexadecimal string to its binary representation
void hex_to_bin(const char *hex, char *out) {
    // First I get the length of the hex string and initialize an index for the
    // output
    int hex_len = strlen(hex);
    int out_index = 0;
    // Then I loop through each character in the hex string
    for (int i = 0; i < hex_len; i++) {
        // I convert the hex character to lowercase to simplify
        char hex_char = hex[i];
        hex_char = tolower(hex_char);
        int hex_digit;
        // I convert the hex character to its integer value
        if (hex_char >= '0' && hex_char <= '9') {
            hex_digit = hex_char - '0';
        } else if (hex_char >= 'a' && hex_char <= 'f') {
            hex_digit = hex_char - 'a' + 10;
        } else {
            // If invalid char its skipped
            continue;
        }

        // Then I convert the integer value to its 4-bit binary representation
        out[out_index++] = (hex_digit >> 3) & 1 ? '1' : '0';
        out[out_index++] = (hex_digit >> 2) & 1 ? '1' : '0';
        out[out_index++] = (hex_digit >> 1) & 1 ? '1' : '0';
        out[out_index++] = (hex_digit >> 0) & 1 ? '1' : '0';
    }
    out[out_index] = '\0';
}

// Converts a signed integer to its sign-magnitude binary representation
void to_sign_magnitude(int num, char *out) {
    // First I set the sign bit and make the number positive if it's negative
    if (num < 0) {
        out[0] = '1';
        num = -num;
    } else {
        out[0] = '0';
    }
    // Then I convert the absolute value of the number to its binary
    for (int i = 31; i >= 1; i--) {
        // I set each bit from the least significant to the most significant
        out[i] = (num & 1) ? '1' : '0';
        // I then right shift the number to check the next bit
        num >>= 1;
    }
    out[32] = '\0';
}

// Converts a signed integer to its one's complement binary representation
void to_ones_complement(int num, char *out) {
    int flip = 0;
    // First I check if the number is negative and set a boolean to flip bits
    if (num < 0) {
        flip = 1;
        num = -num;
    }

    // Then I convert the absolute value of the number to its binary
    for (int i = 31; i >= 0; i--) {
        // I set each bit from the least significant to the most significant
        out[i] = (num & 1) ? '1' : '0';
        // I then right shift the number to check the next bit
        num >>= 1;
    }

    // If the number is negative I invert all bits to get one's complement
    if (flip) {
        for (int i = 0; i < 32; i++) {
            out[i] = (out[i] == '0') ? '1' : '0';
        }
    }

    out[32] = '\0';
}

// Converts a signed integer to its two's complement binary representation
void to_twos_complement(int num, char *out) {
    // First I get the one's complement representation
    to_ones_complement(num, out);
    // After I check if the number is negative to determine if I need to add 1
    if (num < 0) {
        // Then I add 1 to the least significant bit to get two's complement
        int carry = 1;
        // I loop from the least significant bit to the most significant
        for (int i = 31; i >= 0 && carry; i--) {
            // I add the carry to the current bit
            if (out[i] == '1') {
                out[i] = '0';
            } else {
                // If the bit is 0 I set it to 1 and clear the carry
                out[i] = '1';
                carry = 0;
            }
        }
    }
}