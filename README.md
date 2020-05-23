# RLE-Codec

## Overview
### Run-length encoding compression/decompression

This program utilizes run-length encoding compression/decompression. Markers are utilized to avoid negative compression on streams of non-repeating values.

The basic functionality of this algorithm is to replace a sequence of symbols of the same value with a count-symbol pair. For example, a sequence of `AAAAA` could be replaced by `5A` saving 3 bytes (if the symbols were characters). As a result, this codec works best on data with lots of repetition.

## Usage

The program produces `.rle` compressed archive files that can be decompressed.

### Compression

`./rlecomp <file>`

### Decompression

`./decompress <file.rle>`

## Test Cases

A PPM image (`golfcore.ppm`), text file (`declaration.txt`), and a binary file (`hello`) are included in this repository.
