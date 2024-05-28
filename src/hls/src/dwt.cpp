#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define MAT_SIZE 1024

//#define PARTITION  1

extern "C" {
  
    void dwt(double *image, double* output, int levels) {
        #pragma HLS INTERFACE m_axi port=image offset=slave bundle=gmem
        #pragma HLS INTERFACE m_axi port=output offset=slave bundle=gmem
        #pragma HLS INTERFACE s_axilite port=image bundle=control
        #pragma HLS INTERFACE s_axilite port=output bundle=control
        #pragma HLS INTERFACE s_axilite port=levels bundle=control
        #pragma HLS INTERFACE s_axilite port=return bundle=control
        int i, j, i_sc, j_sc;
        double temp;
        int height = MAT_SIZE;
        int width = MAT_SIZE;


        // Temporary arrays to store intermediate results
        double temp_row[width];
        double temp_col[height];
        
    levels_loop:
        // Iterate over each level of decomposition
        for (int level = 0; level < levels; level++) {
            #pragma HLS LOOP_TRIPCOUNT min=1 max=1
            int current_width = width >> level;
            int current_height = height >> level;

            // Process rows
        processing_rows:
            for (i = 0; i < current_height; i++) {
            processing_rows_2:
                for (j = 0; j < current_width / 2; j++) {
                    temp_row[j] = (image[i * current_width + 2 * j] + image[i * current_width + 2 * j + 1]) / 2.0;
                    temp_row[current_width / 2 + j] = (image[i * current_width + 2 * j] - image[i * current_width + 2 * j + 1]) / 2.0;
                }
            processing_rows_3:
                for (j = 0; j < current_width; j++) {
                    image[i * current_width + j] = temp_row[j];
                }
            }

        processing_cols:
            // Process columns
            for (j = 0; j < current_width; j++) {
            processing_cols_2:
                for (i = 0; i < current_height / 2; i++) {
                    temp_col[i] = (image[2 * i * current_width + j] + image[(2 * i + 1) * current_width + j]) / 2.0;
                    temp_col[current_height / 2 + i] = (image[2 * i * current_width + j] - image[(2 * i + 1) * current_width + j]) / 2.0;
                }
            processing_cols_3:
                for (i = 0; i < current_height; i++) {
                    image[i * current_width + j] = temp_col[i];
                }
            }
        }

    copying:
        // Copy the transformed image to the output
        for (i = 0; i < height * width; i++) {
            output[i] = image[i];
        }
    }
}