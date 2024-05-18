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
