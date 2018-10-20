#ifndef IMAGE_H
#define IMAGE_H

unsigned char **CreateImageMatrix(int, int);
unsigned char **ImageToGrayscale(char[], int*, int*);
unsigned char **GrayscaleToBinarized(unsigned char**, int, int);

#endif