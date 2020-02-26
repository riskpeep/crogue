/*
 * cr_game_state
 *
 * Manages game state data
 *
 * Written by Robert Kerr
 * Started: 02/03/2020
 */

#include "constants.h"
#include "game_state.h"
#include "game_screen_welcome.h"
#include "game_screen_play.h"
#include "game_screen_win.h"
#include "game_screen_lose.h"

/* cr_game_init
 * Initializes a new game state.  This is the only way to create a console.
 *
 * @return A new console object
 */
cr_game_t *cr_game_init() {

    /* Create a new game */
    cr_game_t* newGame = (cr_game_t *)malloc( sizeof( cr_game_t ) );

    if( newGame == NULL ) {
        /* Failure - Couldn't create a game.  Return NULL */
        return NULL;
    }

    /* Initialize the game */
    newGame->state = CR_GAME_STATE_WELCOME;

    newGame->window = NULL;
    newGame->isMinimized = false;
    newGame->isMaximized = false;
    newGame->hasFocus = true;
    newGame->wHeight = SCREEN_HEIGHT;
    newGame->wWidth = SCREEN_WIDTH;

    newGame->screenSurface = NULL;
    newGame->tileSet = NULL;
    newGame->console = NULL;

    newGame->displayOutput = NULL;
    newGame->respondToUserInput = NULL;

    cr_game_set_state( newGame, CR_GAME_STATE_WELCOME );

    /* Success */
    return newGame;
}

/* Destroy a game
 */
void cr_game_destroy( cr_game_t ** theGame ) {

    /* Allocated window,
     *           screenSurface,
     *           tileSet,
     *           console, should be released before calling this function */

    /* Reset the game */
    /* Not strictly necessary, but good hygene */
    (*theGame)->state = CR_GAME_STATE_WELCOME;

    (*theGame)->window = NULL;
    (*theGame)->isMinimized = false;
    (*theGame)->isMaximized = false;
    (*theGame)->hasFocus = true;
    (*theGame)->wHeight = SCREEN_HEIGHT;
    (*theGame)->wWidth = SCREEN_WIDTH;

    (*theGame)->screenSurface = NULL;
    (*theGame)->tileSet = NULL;
    (*theGame)->console = NULL;

    (*theGame)->displayOutput = NULL;
    (*theGame)->respondToUserInput = NULL; 

    free( *theGame );

    *theGame = NULL;

    return;
}

/* cr_game_set_state
 * Sets the game to the named state. 
 *
 * @param newState The new game state.
 */
cr_game_state_enum_t cr_game_set_state( cr_game_t *theGame, const cr_game_state_enum_t newState ) {

    cr_game_state_enum_t returnState;

    switch( newState ) {
        case CR_GAME_STATE_WELCOME:
            /* Update function pointers */
            theGame->displayOutput = cr_displayOutputWelcome;
            theGame->respondToUserInput = cr_respondToUserInputWelcome;

            /* return the new state */
            returnState = newState;
            break;

        case CR_GAME_STATE_PLAY:
            /* Update function pointers */
            theGame->displayOutput = cr_displayOutputPlay;
            theGame->respondToUserInput = cr_respondToUserInputPlay;

            /* return the new state */
            returnState = newState;
            break;

        case CR_GAME_STATE_WIN:
            /* Update function pointers */
            theGame->displayOutput = cr_displayOutputWin;
            theGame->respondToUserInput = cr_respondToUserInputWin;

            /* return the new state */
            returnState = newState;
            break;

        case CR_GAME_STATE_LOSE:
            /* Update function pointers */
            theGame->displayOutput = cr_displayOutputLose;
            theGame->respondToUserInput = cr_respondToUserInputLose;

            /* return the new state */
            returnState = newState;
            break;

        default:
            /* We should never be here.  If we are, go back to welcome */
            returnState = cr_game_set_state( theGame, CR_GAME_STATE_WELCOME );
            break;
    }

    return returnState;
    theGame->state = newState;

    /* TODO update game function pointers */

    return newState;
}

