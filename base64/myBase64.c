/*
   ============================================================================
   Name        : myBase64.c
   Author      : 359234
   Version     : 10.3.2010
   Copyright   : 359234@mail.muni.cz
   Description : Base64 encoding
   ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Calculate the power
int MyPow(int base, int exponent) {
        int result = 1;

        for (int i = 0; i < exponent; i++) {
                result *= base;
        }

        return result;
}

int main(int argc, char *argv[]) {

        if(argc > 2) {
                printf("Wrong number of arguments!");
                return 1;
        }

        char baseChars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        //change two last chars
        if (argc==2 && strcmp(argv[1], "-URL") == 0) {
                baseChars[strlen(baseChars) - 1] = '_';
                baseChars[strlen(baseChars) - 2] = '-';
        }

        int cycle_number = 0;   // auxiliary variable

        while (1) {                   // if three chars were entered

                unsigned char input = 0; // input char
                unsigned char tmp = 0; // auxiliary variable
                int binaryTree[24] = {0};
                int baseChar = 0; // encoded char
                int index = 0; // auxiliary variable
                char encoded[6] = {0}; // encoded array

                fflush(stdout);

                if (cycle_number > 0)
                        tmp = getchar();

                cycle_number++;

                input = getchar();

                if (input == '\n')
                        exit(0);
                else {

                        index = 1;


                        //	Conversion one char to binary system
                        for (int i = 7; i >= 0; --i) {
                                binaryTree[i] = input % 2;
                                input = input / 2;
                        }

                        //	Conversion two or three chars to binary system
                        for (int j = 1; j < 3 && (input = getchar()) != '\n'; j++) {

                                if (input != '\n')
                                        index += 1;

                                for (int i = 7; i >= 0; --i) {
                                        binaryTree[(j * 8) + i] = input % 2;
                                        input = input / 2;
                                }

                        }

                        // Conversion chars from binary system to decimal system using six bites
                        for (int k = 0; k < 4; ++k) {

                                for (int i = 0; i < 6; ++i) {
                                        baseChar += binaryTree[(6 * k) + i] * MyPow(2, 5 - i);
                                }

                                encoded[k] = baseChars[baseChar];
                                baseChar = 0;
                        }

                        // If two chars were entered last char of output is '='
                        if ((index == 2) && (argc == 1))
                                encoded[3] = '=';

                        // If one char was entered last two chars of output is '='
                        if ((index == 1) && (argc == 1))
                                encoded[2] = encoded[3] = '=';

                        // If two chars were entered, print output
                        if (argc==2 && strcmp(argv[1], "-URL") == 0 && (index == 2)) {
                                for (int i = 0; i < 3; i++) {
                                        printf("%c", encoded[i]);
                                }
                        }

                        // If one char was entered, print output
                        if(argc==2 && strcmp(argv[1], "-URL") == 0 && (index == 1)) {
                                for (int i = 0; i < 2; i++) {
                                        printf("%c", encoded[i]);
                                }
                        }

                        // If three chars were entered, print output
                        if(index == 3 || ((index == 1) && (argc == 1)) || ((index == 2) && (argc == 1))) {
                                for (int i = 0; i < 4; i++) {
                                        printf("%c", encoded[i]);
                                }
                        }

                        if (index != 3) break; // If three chars wasn't entered

                        if(index == 3) printf("\n");

                }
        }

        printf("\n"); // Put newline to indent program output
        return 0;
}
