//
//  Adam Patyk
//  decompress.c
//  ECE 6680 Lab 2
//
//  Copyright © 2020 Adam Patyk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    FILE            *fpt_in, *fpt_out;
    unsigned char   a, num;
    char            *new_name;
    short int        len, i, rle = 1;


    if (argc != 2 || strcmp(&argv[1][strlen(argv[1]) - 4], ".rle") != 0) {
        fprintf(stderr, "Usage: ./decompress <file.rle>\nMust be an .rle archive\n");
        exit(0);
        }

    // open files needed, including renamed output file
    fpt_in = fopen(argv[1], "rb");
    len = strlen(argv[1]);
    new_name = (char *)calloc(len + 10, sizeof(char));
    // check for original extension
    if (argv[1][len - 8] == '.') {
        strncpy(new_name, argv[1], len - 8);
        // append "-recovered" to name
        strcpy(new_name + len - 8, "-recovered");
        // append original extension
        strncpy(new_name + len + 2, &argv[1][len - 8], 4);
        }
    // no extension (binary files)
    else {
        // append "-recovered" to name
        strncpy(new_name, argv[1], len - 4);
        strcpy(new_name + len - 4, "-recovered");
        }
    fpt_out = fopen(new_name, "wb");

    while(!feof(fpt_in)) {
        if (rle) {
            // read in compressed file in pairs of bytes
            fread(&num, 1, 1, fpt_in);
            fread(&a, 1, 1, fpt_in);

            if (num == 0 && a != 0) {
              rle = !rle; // toggle RLE
              fwrite(&a, 1, 1, fpt_out); // empty buffer to file
            }
            if (!feof(fpt_in)) {
                // write out recovered file
                for (i = 0; i < num; i++) {
                    fwrite(&a, 1, 1, fpt_out);
                }
            }
        }
        else {
            fread(&a, 1, 1, fpt_in);
            if (a == 0)
              rle = !rle; // toggle RLE
            else
              fwrite(&a, 1, 1, fpt_out);
        }
    }

    // cleanup
    fclose(fpt_in);
    fclose(fpt_out);
    free(new_name);

    return 0;
    }
