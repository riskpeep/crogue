/*
 * cr_texture
 *
 * Provides a wrapper around a texture
 *
 * Based on the the SDL tutorials (lesson 10 & 11) at 
 * https://lazyfoo.net/tutorials/SDL/index.php
 *
 * Written by Robert Kerr
 * Started: 01/18/2020
 */

#ifndef RK_TEXTURE_H
#define RK_TEXTURE_H

#include <stdbool.h>
#include <stdint.h>

/*****************************************************************************
 * Opaque types
 *****************************************************************************/
typedef struct rk_texture_t rk_texture_t;

/*****************************************************************************
 * Texture API
 *****************************************************************************/

/* Create a new texture
 * Creates a new texture.  This is the only way to create a texture.
 *
 * @return A new console object
 */
rk_texture_t *rk_texture_create();

/* Destroy a texture
 * Destroys an existing texture.  This operation deletes the console and all
 * resources associated with it.
 *
 * @param texture The texture to destroy.
 */
void rk_texture_destroy( rk_texture_t *texture );

/* Loads an image at the specified path */
bool rk_texture_loadFromFile( rk_texture_t *theTexture, SDL_Renderer* theRenderer, const char* path );

/* Deallocates memory */
void rk_texture_free( rk_texture_t *theTexture );

/* Renders a texture at a given point */
void rk_texture_render( rk_texture_t *theTexture, SDL_Renderer *theRenderer, 
                         int x, int y,
                         SDL_Rect *srcRect, const SDL_Rect *dstRect );

/* Gets image dimensions */
int rk_texture_getHeight( rk_texture_t *theTexture );
int rk_texture_getWidth( rk_texture_t *theTexture );

#endif /* !RK_TEXTURE_H */
