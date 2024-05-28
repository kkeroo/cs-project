#define MAT_SIZE 1024   

//#define PARTITION  1

extern "C" {
  
    void idwt(double *image, double* output, int levels) {
        int i, j, i_sc, j_sc;
        double temp;
        int height = MAT_SIZE;
        int width = MAT_SIZE;

        // Temporary arrays to store intermediate results
        double temp_row[width];
        double temp_col[height];

        // Iterate over each level of decomposition (in reverse order)
    levels_loop:
        for (int level = levels - 1; level >= 0; level--) {
            #pragma HLS LOOP_TRIPCOUNT min=1 max=1
            int current_width = width >> level;
            int current_height = height >> level;

            // Process columns
        processing_cols:
            for (j = 0; j < current_width; j++) {
            processing_cols_2:
                for (i = 0; i < current_height / 2; i++) {
                    temp_col[2 * i] = (image[i * current_width + j] + image[(current_height / 2 + i) * current_width + j]);
                    temp_col[2 * i + 1] = (image[i * current_width + j] - image[(current_height / 2 + i) * current_width + j]);
                }
            processing_cols_3:
                for (i = 0; i < current_height; i++) {
                    image[i * current_width + j] = temp_col[i];
                }
            }

            // Process rows
        processing_rows:
            for (i = 0; i < current_height; i++) {
            processing_rows_2:
                for (j = 0; j < current_width / 2; j++) {
                    temp_row[2 * j] = (image[i * current_width + j] + image[i * current_width + current_width / 2 + j]);
                    temp_row[2 * j + 1] = (image[i * current_width + j] - image[i * current_width + current_width / 2 + j]);
                }
            processing_rows_3:
                for (j = 0; j < current_width; j++) {
                    image[i * current_width + j] = temp_row[j];
                }
            }
        }

        // Copy the reconstructed image to the output
    copying:
        for (i = 0; i < height * width; i++) {
            output[i] = image[i];
        }
    }
   
}