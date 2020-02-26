/*
 * cr_game_screen_play
 *
 * Written by Robert Kerr
 * Started: 02/01/2020
 */

#include "constants.h"
#include "game_screen_play.h"
#include "util.h"

/*****************************************************************************
 * Play screen implementation
 *****************************************************************************/

/* Display Output
 */
bool cr_displayOutputPlay( rk_console_t *console ) {
    /* Make some dummy data */
    cr_dummy_data( console );

    rk_console_write( console, 2, 2, CR_PLAY_MESSAGE );
    rk_console_write( console, 2, 4, CR_PLAY_ACTION_MESSAGE );

    return true;
}

/* Respond to user input
 */
bool cr_respondToUserInputPlay( cr_game_t *theGame, SDL_KeyboardEvent key ) {
    bool retVal = false;

    switch( key.keysym.sym ) {
        case SDLK_RETURN:
            cr_game_set_state( theGame, CR_GAME_STATE_WIN );
            break;
        case SDLK_ESCAPE:
            cr_game_set_state( theGame, CR_GAME_STATE_LOSE );
            break;
        default:
            false;
            break;
    }

    return retVal;
}

