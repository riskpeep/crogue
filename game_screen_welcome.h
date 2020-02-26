/*
 * cr_game_screen_welcome
 *
 * Written by Robert Kerr
 * Started: 02/01/2020
 */

#ifndef RK_GAME_SCREEN_WELCOME_H
#define RK_GAME_SCREEN_WELCOME_H

#include <SDL2/SDL.h>

#include "console.h"
#include "texture.h"
#include "game_state.h"

/*****************************************************************************
 * Welcome screen implementation
 *****************************************************************************/

/* Display Output
 *
 * Draws output onto the passed screen
 *
 * @return bool True if successful
 */
bool cr_displayOutputWelcome( rk_console_t *console );

/* Respond to user input
 *
 * Responds to user input 
 *
 * @return bool True if successful
 */
bool cr_respondToUserInputWelcome( cr_game_t *theGame, SDL_KeyboardEvent key );

#endif /* !RK_GAME_SCREEN_WELCOME_H */
