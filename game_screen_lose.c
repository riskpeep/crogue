/*
 * cr_game_screen_lose
 *
 * Written by Robert Kerr
 * Started: 02/01/2020
 */

#include "constants.h"
#include "game_screen_lose.h"
#include "util.h"

/*****************************************************************************
 * Lose screen implementation
 *****************************************************************************/

/* Display Output
 */
bool cr_displayOutputLose( rk_console_t *console ) {
    /* Make some dummy data */
    cr_dummy_data( console );

    rk_console_write( console, 2, 2, CR_LOSE_MESSAGE );
    rk_console_write( console, 2, 4, CR_LOSE_ACTION_MESSAGE );

    return true;
}

/* Respond to user input
 */
bool cr_respondToUserInputLose( cr_game_t *theGame, SDL_KeyboardEvent key ) {
    bool retVal = false;

    switch( key.keysym.sym ) {
        case SDLK_RETURN:
            cr_game_set_state( theGame, CR_GAME_STATE_WELCOME );
            break;
        default:
            false;
            break;
    }

    return retVal;
}

