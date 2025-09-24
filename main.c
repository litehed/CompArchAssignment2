#include "convert.c"

// A function I made to test the oct_to_bin function while also making the code
// a little more organized
int test_oct_to_bin(int testNum, const char *oct, const char *expected) {
    // First I call oct_to_bin and store the result
    char result[33];
    oct_to_bin(oct, result);

    // Then I compare the result to the expected value and print where it passed
    // or failed
    char *passed;
    int resInt = strcmp(result, expected);
    if (resInt == 0) {
        passed = "PASS";
    } else {
        passed = "FAIL";
    }

    printf(
        "Test %d: oct_to_bin(\"%s\") -> Expected: \"%s\", Got: \"%s\" "
        "[%s]\n",
        testNum, oct, expected, result, passed);

    // I use this return to simplify counting the number of passed tests
    return resInt == 0;
}

// A function I made to test the oct_to_hex function while also making the code
// a little more organized much like the one above
int test_oct_to_hex(int testNum, const char *oct, const char *expected) {
    // First I call oct_to_hex and store the result
    char result[33];
    oct_to_hex(oct, result);

    // Then I compare the result to the expected value and print where it passed
    // or failed
    char *passed;
    int resInt = strcmp(result, expected);
    if (resInt == 0) {
        passed = "PASS";
    } else {
        passed = "FAIL";
    }

    printf(
        "Test %d: oct_to_hex(\"%s\") -> Expected: \"%s\", Got: \"%s\" "
        "[%s]\n",
        testNum, oct, expected, result, passed);

    // I use this return to simplify counting the number of passed tests
    return resInt == 0;
}

// A function I made to test the hex_to_bin function while also making the code
// a little more organized much like the one above
int test_hex_to_bin(int testNum, const char *hex, const char *expected) {
    // First I call hex_to_bin and store the result
    char result[33];
    hex_to_bin(hex, result);

    // Then I compare the result to the expected value and print where it passed
    // or failed
    char *passed;
    int resInt = strcmp(result, expected);
    if (resInt == 0) {
        passed = "PASS";
    } else {
        passed = "FAIL";
    }

    printf(
        "Test %d: hex_to_bin(\"%s\") -> Expected: \"%s\", Got: \"%s\" "
        "[%s]\n",
        testNum, hex, expected, result, passed);

    // I use this return to simplify counting the number of passed tests
    return resInt == 0;
}

int test_to_sign_magnitude(int testNum, int input, const char *expected) {
    // First I call to_sign_magnitude and store the result
    char result[33];
    to_sign_magnitude(input, result);

    // Then I compare the result to the expected value and print where it passed
    // or failed
    char *passed;
    int resInt = strcmp(result, expected);
    if (resInt == 0) {
        passed = "PASS";
    } else {
        passed = "FAIL";
    }

    printf(
        "Test %d: to_sign_magnitude(\"%d\") -> Expected: \"%s\", Got: "
        "\"%s\" [%s]\n",
        testNum, input, expected, result, passed);

    // I use this return to simplify counting the number of passed tests
    return resInt == 0;
}

int test_to_ones_complement(int testNum, int input, const char *expected) {
    // First I call to_ones_complement and store the result
    char result[33];
    to_ones_complement(input, result);

    // Then I compare the result to the expected value and print where it passed
    // or failed
    char *passed;
    int resInt = strcmp(result, expected);
    if (resInt == 0) {
        passed = "PASS";
    } else {
        passed = "FAIL";
    }

    printf(
        "Test %d: to_ones_complement(\"%d\") -> Expected: \"%s\", Got: "
        "\"%s\" [%s]\n",
        testNum, input, expected, result, passed);

    // I use this return to simplify counting the number of passed tests
    return resInt == 0;
}

int test_to_twos_complement(int testNum, int input, const char *expected) {
    // First I call to_twos_complement and store the result
    char result[33];
    to_twos_complement(input, result);

    // Then I compare the result to the expected value and print where it passed
    // or failed
    char *passed;
    int resInt = strcmp(result, expected);
    if (resInt == 0) {
        passed = "PASS";
    } else {
        passed = "FAIL";
    }

    printf(
        "Test %d: to_twos_complement(\"%d\") -> Expected: \"%s\", Got: "
        "\"%s\" [%s]\n",
        testNum, input, expected, result, passed);

    // I use this return to simplify counting the number of passed tests
    return resInt == 0;
}

// This code handles reading the test cases from the file and running the tests
void test_from_file() {
    // I check if the file exists and open it
    FILE *file = fopen("a2_test.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file \n ");
        return;
    }

    // First I initialize line to hold each line of the file and testNum to keep
    // track of which test I'm on I read each line of the file using fgets and
    // parse it using sscanf
    char line[256];
    int testNum = 1;
    int testsPassed = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        // I ignore empty lines and comments
        line[strcspn(line, "\n")] = '\0';

        if (line[0] == '\n' || line[0] == '#') {
            continue;
        }

        // I parse the line to determine which function to test and its
        // parameters
        char funcName[65];
        char oct_in[65];
        char hex_in[65];
        char expected[65];
        int input;

        if (strncmp(line, "oct_to_bin", 10) == 0) {
            if (sscanf(line, "%s %s %s", funcName, oct_in, expected) == 3) {
                testsPassed += test_oct_to_bin(testNum, oct_in, expected);
                testNum++;
            }
        } else if (strncmp(line, "oct_to_hex", 10) == 0) {
            if (sscanf(line, "%s %s %s", funcName, oct_in, expected) == 3) {
                testsPassed += test_oct_to_hex(testNum, oct_in, expected);
                testNum++;
            }
        } else if (strncmp(line, "hex_to_bin", 10) == 0) {
            if (sscanf(line, "%s %s %s", funcName, hex_in, expected) == 3) {
                testsPassed += test_hex_to_bin(testNum, hex_in, expected);
                testNum++;
            }
        } else if (strncmp(line, "to_sign_magnitude", 17) == 0) {
            if (sscanf(line, "%s %d %s", funcName, &input, expected) == 3) {
                testsPassed += test_to_sign_magnitude(testNum, input, expected);
                testNum++;
            }
        } else if (strncmp(line, "to_ones_complement", 18) == 0) {
            if (sscanf(line, "%s %d %s", funcName, &input, expected) == 3) {
                testsPassed +=
                    test_to_ones_complement(testNum, input, expected);
                testNum++;
            }
        } else if (strncmp(line, "to_twos_complement", 18) == 0) {
            if (sscanf(line, "%s %d %s", funcName, &input, expected) == 3) {
                testsPassed +=
                    test_to_twos_complement(testNum, input, expected);
                testNum++;
            }
        }
    }
    // Finally I print a summary of the tests and close the file
    printf("Summary: %d / %d tests passed", testsPassed, testNum - 1);
    fclose(file);
}

int main() {
    test_from_file();
    return 0;
}
