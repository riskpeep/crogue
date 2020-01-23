/*
 * cr_game
 *
 * Written by Robert Kerr
 * Started: 01/22/2020
 */

#ifndef RK_GAME_H
#define RK_GAME_H

#include <SDL2/SDL.h>

#include "texture.h"

/*****************************************************************************
 * Console Types
 *****************************************************************************/

/* The Game
 */
typedef struct cr_game_t {
    /* The window we'll be rendering to
    */
    SDL_Window* window;

    /* The renderer we'll use for accelerated rendering
     */
    SDL_Renderer* renderer;

    /* The surface contained by the window
    */
    SDL_Surface* screenSurface;

    /* The texture we will load and show on the screen
    */
    rk_texture_t* helloTexture;

} cr_game_t;

#endif /* !RK_GAME_H */
