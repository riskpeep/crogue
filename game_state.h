/*
 * cr_game_state
 *
 * Written by Robert Kerr
 * Started: 01/22/2020
 */

#ifndef RK_GAME_STATE_H
#define RK_GAME_STATE_H

#include <SDL2/SDL.h>

#include "console.h"
#include "texture.h"

/*****************************************************************************
 * The Game State
 *****************************************************************************/
/* Game States
 */
typedef enum cr_game_state_enum_t {
    CR_GAME_STATE_WELCOME,
    CR_GAME_STATE_PLAY,
    CR_GAME_STATE_WIN,
    CR_GAME_STATE_LOSE
} cr_game_state_enum_t;

/* Pre-declaration of the game struct */
typedef struct cr_game_s cr_game_t;

/* Game state functions 
 */
typedef bool (*displayOutput_t)( rk_console_t * );
typedef bool (*respondToUserInput_t)( cr_game_t *, SDL_KeyboardEvent );

/* The Game
 */
struct cr_game_s {
    /* The window we'll be rendering to
    */
    cr_game_state_enum_t    state;

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

    /* Game function pointers.  We use function pointers here so that in 
     * different game states appropriate functions can be called without
     * having big ugly switch statements per state
     */
    /* displayOutput - updates the screen each frame */
    displayOutput_t displayOutput;

    /* respondToUserInput - processes user input each frame */
    respondToUserInput_t respondToUserInput;

};


/*****************************************************************************
 * Game State Functions
 *****************************************************************************/

/* cr_game_init
 * Initializes a new game state.  This is the only way to create a console.
 *
 * @return A new console object
 */
cr_game_t *cr_game_init();

/* cr_game_destroy
 * Destroys an existing game.  This operation deletes the game and all
 * associated data
 *
 * Allocated window,
 *           screenSurface,
 *           tileSet,
 *           console, should be released before calling this function 
 *
 * @param theGame The game to destroy.
 */
void cr_game_destroy( cr_game_t **theGame );

/* cr_game_set_state
 * Sets the game to the named state. 
 *
 * @param newState The new game state.
 */
cr_game_state_enum_t cr_game_set_state( cr_game_t *theGame, const cr_game_state_enum_t newState );

#endif /* !RK_GAME_STATE_H */
