#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>


#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

#define IMAGE_WIDTH 512



// Define image structure
// struct Image {
//     uint8_t pixels[IMAGE_WIDTH][IMAGE_HEIGHT];
// };



// calculate DWT 
void forward_wavelet_transform(double *image, double* output, int levels) {
    int i, j, i_sc, j_sc;
    double temp;
    int height = IMAGE_WIDTH;
    int width = IMAGE_WIDTH;

    // Temporary arrays to store intermediate results
    double* temp_row = (double*)malloc(width * sizeof(double));
    double* temp_col = (double*)malloc(height * sizeof(double));
    // Iterate over each level of decomposition
    for (int level = 0; level < levels; level++) {
        int current_width = width >> level;
        int current_height = height >> level;

        // Process rows
        for (i = 0; i < current_height; i++) {
            for (j = 0; j < current_width / 2; j++) {
                temp_row[j] = (image[i * current_width + 2 * j] + image[i * current_width + 2 * j + 1]) / 2.0;
                temp_row[current_width / 2 + j] = (image[i * current_width + 2 * j] - image[i * current_width + 2 * j + 1]) / 2.0;
            }
            for (j = 0; j < current_width; j++) {
                image[i * current_width + j] = temp_row[j];
            }
        }

        // Process columns
        for (j = 0; j < current_width; j++) {
            for (i = 0; i < current_height / 2; i++) {
                temp_col[i] = (image[2 * i * current_width + j] + image[(2 * i + 1) * current_width + j]) / 2.0;
                temp_col[current_height / 2 + i] = (image[2 * i * current_width + j] - image[(2 * i + 1) * current_width + j]) / 2.0;
            }
            for (i = 0; i < current_height; i++) {
                image[i * current_width + j] = temp_col[i];
            }
        }
    }

    // Copy the transformed image to the output
    for (i = 0; i < height * width; i++) {
        output[i] = image[i];
    }

    // Free temporary arrays
    free(temp_row);
    free(temp_col);
    // Approximation coefficient 

    // Horizontal coefficients

    // Vertical coefficients

    // Diagonal coefficients

}


// calculate Inverse DWT (IDWT) 
void inverse_wavelet_transform(double *image, double* output, int levels) {
    int i, j, i_sc, j_sc;
    double temp;
    int height = IMAGE_WIDTH;
    int width = IMAGE_WIDTH;

    // Temporary arrays to store intermediate results
    double* temp_row = (double*)malloc(width * sizeof(double));
    double* temp_col = (double*)malloc(height * sizeof(double));

    // Iterate over each level of decomposition (in reverse order)
    for (int level = levels - 1; level >= 0; level--) {
        int current_width = width >> level;
        int current_height = height >> level;

        // Process columns
        for (j = 0; j < current_width; j++) {
            for (i = 0; i < current_height / 2; i++) {
                temp_col[2 * i] = (image[i * current_width + j] + image[(current_height / 2 + i) * current_width + j]);
                temp_col[2 * i + 1] = (image[i * current_width + j] - image[(current_height / 2 + i) * current_width + j]);
            }
            for (i = 0; i < current_height; i++) {
                image[i * current_width + j] = temp_col[i];
            }
        }

        // Process rows
        for (i = 0; i < current_height; i++) {
            for (j = 0; j < current_width / 2; j++) {
                temp_row[2 * j] = (image[i * current_width + j] + image[i * current_width + current_width / 2 + j]);
                temp_row[2 * j + 1] = (image[i * current_width + j] - image[i * current_width + current_width / 2 + j]);
            }
            for (j = 0; j < current_width; j++) {
                image[i * current_width + j] = temp_row[j];
            }
        }
    }

    // Copy the reconstructed image to the output
    for (i = 0; i < height * width; i++) {
        output[i] = image[i];
    }

    // Free temporary arrays
    free(temp_row);
    free(temp_col);
}



// improve for showing 
void improve(double *image, double* output) {
    int i, j;
    int height = IMAGE_WIDTH;
    int width = IMAGE_WIDTH;
    // Approximation coefficient 
    for (i = 0; i < height/2; i++) {
        for (j = 0; j < width/2; j++) {
            // calculate average of 4 pixels in the neighborhood
            output[i * width + j] = image[i * width + j]/4;
            output[(i + height/2) * width + j] = image[(i + height/2) * width + j]+0.5;
            output[i * width + j + height/2] = image[i * width + j + height/2]+0.5;
            output[(i + height/2) * width + j + height/2] = image[(i + height/2) * width + j + height/2]+0.5;
        }
    }
}



int main() {
    // Define sample grayscale image

    // Load image from file and allocate space for the output image
    char image_name[] = "./elaine.jpg";
    int width, height, cpp;
    // load only gray scale image
    unsigned char *h_imageIn;
    h_imageIn = stbi_load(image_name, &width, &height, &cpp, STBI_grey);
    if (h_imageIn == NULL)
    {
        printf("Error reading loading image %s!\n", image_name);
        exit(EXIT_FAILURE);
    }
    printf("Loaded image %s of size %dx%d.\n", image_name, width, height);
    printf("Image is %d bytes per pixel.\n", cpp);
    // Save grayscale image to file
    printf("Size of image is %ld, %ld\n", sizeof(unsigned char), sizeof(h_imageIn));
    


    double *image_pixels = (double*)malloc(sizeof(double) * width * height);
    double *output = (double*)malloc(sizeof(double) * width * height);
    double *show_output = (double*)malloc(sizeof(double) * width * height);

    // convert to grayscale 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image_pixels[i*width + j] = h_imageIn[i * width + j]/255.0;
        }
    }

    forward_wavelet_transform(image_pixels, output, 1);
    // used only for showing purposes, not needed for IDWT
    improve(output, show_output);
    
    inverse_wavelet_transform(image_pixels, output, 1);

    // Save image to file

    int image_size = width * height;


    // Save image to file
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            h_imageIn[i*width + j] = (char)(output[i*width + j]*255);
        }
    }
    // Free memory

    // free(image.pixels[0]);
    // free(image.pixels);
    //free(clusters->num_points);
    stbi_write_jpg("dwt_output.jpg", width, height,STBI_grey, h_imageIn, 100);
    free(image_pixels);

    return 0;
}
