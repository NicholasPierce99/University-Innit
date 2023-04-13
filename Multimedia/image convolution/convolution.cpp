#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#define DATASIZE 375000

//convolution function
//takes in data, filter, and outdata
void convolution(unsigned char data[], int filter[], unsigned char outdata[]){
    //loop over the size of image
    for (int i = 0; i < DATASIZE; i++ ){
        int accumulation = 0;
        //output data
        outdata[i] = 0;
        //loop over 1d kernel                       
        for (int  j = 0; j < 9 ; j++ ){
            //convolution operation, inner product
            accumulation += data[i - j] * filter[j];    
        }
        outdata[i] = accumulation/9;
    }
}

int main( ){
    FILE *file_id1, *file_id2;
    //input and output arrays
    unsigned char data[DATASIZE], outdata[DATASIZE];
    
    //image filter matrix
    int filter[9] = {1, 2, 3, 4, 5, 4, 3, 2, 1};

    //file open
    file_id1 = fopen("unesco750-1.raw", "r");
    fread(data, 1, DATASIZE, file_id1);
    fclose(file_id1);

    //run convolution function
    convolution(data, filter, outdata);
    
    //write to output file
    file_id2 = fopen("output.raw", "w");
    fwrite(outdata, 1, DATASIZE, file_id2);
    fclose(file_id2);


    return 0;
}

//function prototype
void convolution(unsigned char data[], int filter[], int h, int w);
