#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imagen.h"

#define MASK_D 3

void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height );
void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height );

void bp_filter(unsigned char *gray_image, unsigned char *filtered_image, uint32_t width, uint32_t height);

unsigned char * reservarMemoria( uint32_t width, uint32_t height );

int main( )
{
    bmpInfoHeader info;
    unsigned char *imagenRGB, *imagenGray, *filtered_image;

    imagenRGB = abrirBMP("../images/linux.bmp", &info );

    displayInfo( &info );
    imagenGray = reservarMemoria( info.width, info.height );
    RGBToGray( imagenRGB, imagenGray, info.width, info.height );

    // brilloImagen( imagenGray, info.width, info.height );
    filtered_image = reservarMemoria(info.width, info.height);
    bp_filter(imagenGray, filtered_image, info.width, info.height);

    memset(filtered_image, 255, info.width * info.height);

    GrayToRGB( imagenRGB, imagenGray, info.width, info.height );

    guardarBMP("result.bmp", &info, imagenRGB );

    free( imagenRGB );
    free( imagenGray );
    free(filtered_image);

    return 0;
}

void bp_filter(unsigned char *gray_image, unsigned char *filtered_image, uint32_t width, uint32_t height){
    register int x, y, ym, xm;
    int image_i, mask_i, conv;
    
    int mask[MASK_D * MASK_D] = {
        1, 1, 1,
        1, 1, 1,
        1, 1, 1
    };

    for (y = 0; y <= height - MASK_D; ++y){
        for (x = 0; x <= width - MASK_D; ++x){
            mask_i = 0;
            conv = 0;
            for (ym = 0; ym < MASK_D; ++ym){
                for (xm = 0; xm < MASK_D; ++xm){
                    image_i = (y + ym) * width + (x + xm);
                    conv += gray_image[image_i] * mask[mask_i++];
                }
            }

            conv /= 9;
            image_i = (y + 1) * width + (x + 1);
            filtered_image[image_i] = conv;
        }
    }

}

void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height )
{
    register int indiceGray;
    int pixel;

    for( indiceGray = 0; indiceGray < (height*width); indiceGray++ )
    {
        pixel = imagenGray[indiceGray] + 70;
        imagenGray[indiceGray] = (pixel > 255)? 255 : (unsigned char)pixel;
    }
}

void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height )
{
    int indiceRGB, indiceGray;

    for( indiceGray = 0, indiceRGB = 0; indiceGray < (height*width); indiceGray++, indiceRGB += 3 )
    {
        imagenRGB[indiceRGB]   = imagenGray[indiceGray];
        imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
        imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
    }
}
void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height )
{
    unsigned char nivelGris;
    int indiceRGB, indiceGray;

    for( indiceGray = 0, indiceRGB = 0; indiceGray < (height*width); indiceGray++, indiceRGB += 3 )
    {
    //	nivelGris = (imagenRGB[indiceRGB] + imagenRGB[indiceRGB+1] + imagenRGB[indiceRGB+2]) / 3;
        nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2]) / 100;
        // 0.30 = 30 / 100
        // 0.59 = 59 / 100
        // 0.11 = 11 / 100
        imagenGray[indiceGray] = nivelGris;
    }
}

/*
void GrayToRGB( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height )
{
    register int x, y;
    int indiceRGB, indiceGray;

    for( y = 0; y < height; y++ )
        for( x = 0; x < width; x++ )
        {
            indiceGray = (y*width + x);
            indiceRGB =  indiceGray * 3;
            imagenRGB[indiceRGB]   = imagenGray[indiceGray];
            imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
            imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
        }
}

void RGBToGray( unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t height )
{
    register int x, y;
    unsigned char nivelGris;
    int indiceRGB, indiceGray;

    for( y = 0; y < height; y++ )
        for( x = 0; x < width; x++ )
        {
            indiceGray = (y*width + x);
            indiceRGB =  indiceGray * 3;
        //	nivelGris = (imagenRGB[indiceRGB] + imagenRGB[indiceRGB+1] + imagenRGB[indiceRGB+2]) / 3;
            nivelGris = (30*imagenRGB[indiceRGB] + 59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2]) / 100;
        // 0.30 = 30 / 100
        // 0.59 = 59 / 100
        // 0.11 = 11 / 100
            imagenGray[indiceGray] = nivelGris;
        }
}*/

unsigned char * reservarMemoria( uint32_t width, uint32_t height )
{
    unsigned char *imagen;

    imagen = (unsigned char *)malloc( width*height*sizeof(unsigned char) );
    if( imagen == NULL )
    {
        perror("Error al asignar memoria a la imagen");
        exit(EXIT_FAILURE);
    }

    return imagen;
}
