//
//  Adam Patyk
//  compress.c
//  ECE 6680 Lab 2
//
//  Copyright © 2020 Adam Patyk. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USE_MARKERS 1

int main(int argc, const char * argv[]) {
    FILE            *fpt_in, *fpt_out;
    unsigned char   a, b, run_count, buf[4];
    short int       buf_bytes = 4, rle = 1, prev_rle,zero = 0x0;
    int             zero_rep = 0x00000100;

    if (argc != 2) {
        fprintf(stderr, "Usage: ./rlecomp <file>\n");
        exit(0);
        }

    fpt_in = fopen(argv[1], "rb");
    fpt_out = fopen(strcat((char *)argv[1],".rle"), "wb");

    if (USE_MARKERS) {
        run_count = 1;
        // read first symbol
        fread(&a, 1, 1, fpt_in);
        while(buf_bytes > 0) {
            // buffer next 4 symbols
            fread(&buf, 1, buf_bytes, fpt_in);
            b = buf[0];
            if (feof(fpt_in)) buf_bytes--;
            fseek(fpt_in, -(buf_bytes - 1), SEEK_CUR);
            // check buffer for repeated bytes
            prev_rle = rle;
            if (buf[0] != buf[1] && buf[1] != buf[2] && buf[2] != buf[3] && run_count == 1)
                rle = 0;
            else if (rle == 0 && buf[0] == buf[1] && buf[1] == buf[2])
                rle = 1;
            // RLE on
            if (rle) {
                  // designate that RLE is on if previously off
                  if (prev_rle == 0) fwrite(&zero, 1, 1, fpt_out);
                  // keep tally of repeated bytes
                  if (a == b && run_count < 255) {
                      run_count++;
                  }
                  // write out to compressed file
                  else {
                      fwrite(&run_count, 1, 1, fpt_out);
                      fwrite(&a, 1, 1, fpt_out);
                      a = b;
                      run_count = 1;
                  }
              }
              // RLE off
              else {
                  // designate in file that RLE is off
                  if (prev_rle == 1) fwrite(&zero, 1, 1, fpt_out);
                  if (a == 0) { // 0 literal must be written differently in this mode
                      fwrite(&zero_rep, 1, 4, fpt_out);
                  }
                  else {
                      fwrite(&a, 1, 1, fpt_out);
                  }
                  a = b;
              }
        }
        run_count--;
        fwrite(&run_count, 1, 1, fpt_out);
        fwrite(&b, 1, 1, fpt_out);
        }
      else {
        run_count = 1;
        // read first symbol
        fread(&a, 1, 1, fpt_in);
        while(!feof(fpt_in)) {
            // read next symbol
            fread(&b, 1, 1, fpt_in);
            // keep tally of repeated bytes
            if (a == b && run_count < 255) {
                run_count++;
            }
            // write out to compressed file
            else {
                fwrite(&run_count, 1, 1, fpt_out);
                fwrite(&a, 1, 1, fpt_out);
                a = b;
                run_count = 1;
            }
        }
        run_count--;
        fwrite(&run_count, 1, 1, fpt_out);
        fwrite(&a, 1, 1, fpt_out);
    }

    // cleanup
    fclose(fpt_in);
    fclose(fpt_out);

    return 0;
    }
