/*
 * cr_game_screen_lose
 *
 * Written by Robert Kerr
 * Started: 02/01/2020
 */

#ifndef RK_GAME_SCREEN_LOSE_H
#define RK_GAME_SCREEN_LOSE_H

#include <SDL2/SDL.h>

#include "console.h"
#include "texture.h"
#include "game_state.h"

/*****************************************************************************
 * Lose screen implementation
 *****************************************************************************/

/* Display Output
 *
 * Draws output onto the passed screen
 *
 * @return bool True if successful
 */
bool cr_displayOutputLose( rk_console_t *console );

/* Respond to user input
 *
 * Responds to user input 
 *
 * @return bool True if successful
 */
bool cr_respondToUserInputLose( cr_game_t *theGame, SDL_KeyboardEvent key );

#endif /* !RK_GAME_SCREEN_LOSE_H */
