/*
 * cr_game
 *
 * Written by Robert Kerr
 * Started: 01/22/2020
 */

#ifndef RK_GAME_H
#define RK_GAME_H

#include <SDL2/SDL.h>

#include "console.h"
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

    /* Window info
    */
    bool isMinimized;
    bool isMaximized;
    bool hasFocus;
    uint16_t wHeight;
    uint16_t wWidth;

    /* The renderer we'll use for accelerated rendering
     */
    SDL_Renderer* renderer;

    /* The surface contained by the window
    */
    SDL_Surface* screenSurface;

    /* The tileSet we will load and show on the screen
    */
    rk_texture_t* tileSet;

    /* The console we draw our glyphs into
     */
    rk_console_t* console;

    /* The player position
     */
    uint16_t playerPosX;
    uint16_t playerPosY;

} cr_game_t;

#endif /* !RK_GAME_H */
