/*
 * rk_texture
 *
 * Provides a wrapper around a texture
 *
 * Based on the the SDL tutorials (lesson 10 & 11) at 
 * https://lazyfoo.net/tutorials/SDL/index.php
 *
 * Written by Robert Kerr
 * Started: 01/18/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture.h"

#define RK_TEXTURE_MAX_WIDTH 65535
#define RK_TEXTURE_MAX_HEIGHT 65535

struct rk_texture_t {
    uint16_t height;
    uint16_t width;

    SDL_Texture* texture;
};

/* Create a new texture
 */
rk_texture_t *rk_texture_create() {

    /* Create a new texture */
    rk_texture_t* newTexture = (rk_texture_t *)malloc( sizeof( rk_texture_t ) );

    if( newTexture == NULL ) {
        /* Failure - Couldn't create a texture.  Return NULL */
        return NULL;
    }

    /* Success - Initialize the members */
    newTexture->height = 0;
    newTexture->width = 0;
    newTexture->texture = NULL;

    return newTexture;
}

/* Destroy a texture
 */
void rk_texture_destroy( rk_texture_t *theTexture ) {

    /* Free the texture if it exists */
    rk_texture_free( theTexture );

    /* And then free the texture struct */
    free( theTexture );

    return;
}

/* Loads an image at the specified path
 */
bool rk_texture_loadFromFile( rk_texture_t *theTexture, SDL_Renderer *theRenderer, const char* path ) {

    /* The final texture */
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = NULL;

    /* Get rid of preexisting texture */
    rk_texture_free( theTexture );

    /* Load image at specified path */
    loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load texture image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    } else {
        if( loadedSurface->h > RK_TEXTURE_MAX_HEIGHT || loadedSurface->w > RK_TEXTURE_MAX_WIDTH ) {
            printf( "Texture dimensions greater than max size of %u x %u!\n", RK_TEXTURE_MAX_HEIGHT, RK_TEXTURE_MAX_WIDTH );
        } else {

            /* Color key image */
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

            /* Create texture from surface pixels */
            newTexture = SDL_CreateTextureFromSurface( theRenderer, loadedSurface );
            if( newTexture == NULL ) {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
            } else {
                /* Get image dimensions */
                theTexture->width = loadedSurface->w;
                theTexture->height = loadedSurface->h;
            }
        }

        /* Get rid of loaded surface */
        SDL_FreeSurface( loadedSurface );
    }

    /* Return success */
    theTexture->texture = newTexture;
    return theTexture->texture != NULL;
}

/* Deallocates memory
 */
void rk_texture_free( rk_texture_t *theTexture ) {

    /* Free the texture if it exists */
    if( theTexture->texture != NULL ) {
        /* Free the tile array */
        SDL_DestroyTexture( theTexture->texture );
        theTexture->texture = NULL;
        theTexture->height = 0;
        theTexture->width = 0;
    }

    return;
}

/* Renders a texture at a given point
 */
void rk_texture_render( rk_texture_t *theTexture, SDL_Renderer *theRenderer, 
                         int x, int y,
                         SDL_Rect *srcRect, const SDL_Rect *dstRect ) {

    /* Copy the whole texture to the renderer */
    SDL_RenderCopy( theRenderer, theTexture->texture, srcRect, dstRect );
}

/* Gets image dimensions
 */
int rk_texture_getHeight( rk_texture_t *theTexture ) {
    return theTexture->height;
}

int rk_texture_getWidth( rk_texture_t *theTexture ) {
    return theTexture->width;
}

