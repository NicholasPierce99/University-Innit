#include <stdio.h>
#include <iostream>

#define HEIGHT 300
#define WIDTH 300

int main(){

    //input and output 2d matrices
    unsigned char img[HEIGHT][WIDTH];
    unsigned char outdata3v[HEIGHT][WIDTH];
    unsigned char outdata3h[HEIGHT][WIDTH];
    unsigned char outdata5v[HEIGHT][WIDTH];
    unsigned char outdata5h[HEIGHT][WIDTH];
    
    FILE *file_id1, *file_id2, *file_id3, *file_id4, *file_id5;
    file_id1 = fopen("portait.raw", "r");

    fread(img, HEIGHT * WIDTH, sizeof( unsigned char), file_id1);
    fclose(file_id1);
    
    //3x3 horizontal/vertical
    int filter2[3][3] = {-1, -2, -1,
                          0, 0, 0,
                          1, 2, 1};

    int filter1[3][3] = {-1,0,1,
                        -2,0, 2, 
                        -1, 0, 1};

    //5x5 horizontal/vertical
    int filter3[5][5] = {-2, -3, -4, -3, 2,
                         -1, -2, -3, -2, -1,
                         0, 0, 0, 0, 0,
                        1, 2, 3, 2, 1,
                        2, 3, 4, 3, 2};

    int filter4[5][5] = {-2, -1, 0, 1, 2,
                         -3, -2, 0, 2, 3,
                         -4, -3, 0, 3, 4,
                         -3, -2, 0, 2, 3,
                         -2, -1, 0, 1, 2};

    //2d convolution 3x3

    for(int i = 0; i < HEIGHT - 2; i++){

        for(int j = 0; j < WIDTH - 2; j++){

            for(int k = 0; k < 3; k++){

                for(int l = 0; l < 3; l++){

                    outdata3h[i+1][j+1] += filter1[k][l] * (int)(img[i+k][j+l]);
                    outdata3v[i+1][j+1] += filter2[k][l] * (int)(img[i+k][j+l]);
                }
            }
        }
    }
    //normalizing data for 3x3
    for(int i = 0; i < HEIGHT; i++){

        for(int j = 0; j < WIDTH; j++){

            outdata3h[i][j] = (unsigned char)(outdata3h[i][j] / 8 + 128);

            outdata3v[i][j] = (unsigned char)(outdata3v[i][j] / 8 + 128);
        }
    }
    //------------------------------------------------------------------------------------

    //2d convolution 5x5
     for(int i = 0; i < HEIGHT - 4; i++){

        for(int j = 0; j < WIDTH - 4; j++){

            for(int k = 0; k < 5; k++){

                for(int l = 0; l < 5; l++){

                    outdata5h[i+1][j+1] += filter3[k][l] * (int)(img[i+k][j+l]);
                    outdata5v[i+1][j+1] += filter4[k][l] * (int)(img[i+k][j+l]);
                }
            }
        }
    }
    //normalizing data for 5x5
    for(int i = 0; i < HEIGHT; i++){

        for(int j = 0; j < WIDTH; j++){

            outdata5h[i][j] = (unsigned char)(outdata5h[i][j] / 56 + 128);
            outdata5v[i][j] = (unsigned char)(outdata5v[i][j] / 56 + 128);
        }
    }
   
    file_id2 = fopen("output3h.raw", "w");
    file_id3 = fopen("output3v.raw", "w");
    file_id4 = fopen("output5h.raw", "w");
    file_id5 = fopen("output5v.raw", "w");

    fwrite(outdata3h, sizeof( unsigned char), HEIGHT * WIDTH, file_id2);
    fwrite(outdata3v, sizeof( unsigned char), HEIGHT * WIDTH, file_id3);
    fwrite(outdata5h, sizeof( unsigned char), HEIGHT * WIDTH, file_id4);
    fwrite(outdata5v, sizeof( unsigned char), HEIGHT * WIDTH, file_id5);

    fclose(file_id2);
    fclose(file_id3);
    fclose(file_id4);
    fclose(file_id5);
    return 0;
}