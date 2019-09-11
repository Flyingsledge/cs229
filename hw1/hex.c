/*
 * CSF Fall 2019
 * Homework 1
 * Jerry Chen
 * jchen268@jhu.edu
 */

#include <stdio.h>
#include <ctype.h>

/* The number of data bytes corresponding to one line of hexdump output. */
#define HEXDUMP_BUFSIZE 16

    /** Print a line using the first len values stored in the buffer.
     *
     * @param buf the char buffer storing the input values
     * @param len the amount of chars we want to print from the buffer
     * @param counter the amount of chars printed so far
     */
    void printLine(char* buf, int len, int counter) {
        //The left column
        printf("%08x: ", counter - 1 - ((counter - 1) % HEXDUMP_BUFSIZE));

        //The middle column
        for (int i = 0; i < len; i++) {
            printf("%02x ", buf[i]);
        }

        //Fill in the space if there aren't a full 16 chars
        for (int i = 16; i > len; i--){
            printf("   ");
        }

        //Nice formatting
        printf(" ");

        //The right column
        for (int i = 0; i < len; i++){
            if ((buf[i] == '\n')||((int)buf[i] == 9)) {
                printf(".");
            }
            else{
                printf("%c", buf[i]);
            }
        }

        //Nice formatting
        printf("\n");
    }

    int main(int argc, char **argv) {
        FILE *in;

    if (argc > 2) {
        fprintf(stderr, "Usage: %s [<filename>]\n", argv[0]);
        fprintf(stderr, "Reads from standard input if <filename> is omitted\n");
        return 1;
    }

    if (argc == 1) {
        in = stdin;
    } else {
        in = fopen(argv[1], "rb");
        if (in == NULL){
            fprintf(stderr, "File %s couldn't be opened.\n", argv[1]);
            return 1;
        }
    }

    char buf[HEXDUMP_BUFSIZE]; /* storage for data read from input */

    //Keep track of how many chars we've read
    int counter = 0;
    //Get first char
    char ch = getc(in);

    //Loops until end of file or input
    while(ch != EOF){
        //add char to buffer, loops around from end to beginning
        buf[counter%HEXDUMP_BUFSIZE] = ch;
        //increment counter so we can move to the next buffer slot
        counter++;
        //Go ahead and print a line if 16 chars have been read
        if (counter%HEXDUMP_BUFSIZE == 0){
            printLine(buf, HEXDUMP_BUFSIZE, counter);
        }
        //get next char
        ch = getc(in);
    }

    //Print the remainders
    printLine(buf, counter%HEXDUMP_BUFSIZE, counter);
    //Close file
    fclose(in);

    return 0;
}
