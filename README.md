# RLE-Codec

## Overview
### Run-length encoding compression/decompression

This program utilizes run-length encoding compression/decompression. Markers are utilized to avoid negative compression on streams of non-repeating values.

## Usage

The program produces `.rle` compressed archive files that can be decompressed.

### Compression

`./rlecomp <file>`

### Decompression

`./decompress <file.rle>`

## Test Cases

A PPM image (`golfcore.ppm`), text file (`declaration.txt`), and a binary file (`hello`) are included in this repository.
