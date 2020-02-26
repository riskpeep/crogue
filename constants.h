/*
 * constants.h
 *
 * Provides constants for the game Crogue, a roguelike written in C
 *
 * Written by Robert Kerr
 * Started: 02/01/2020
 */

#ifndef CR_CONSTANTS_H
#define CR_CONSTANTS_H

/*****************************************************************************
 * Defaults and constants
 *****************************************************************************/

/* Screen dimension constants
 */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 480

/* Console dimension constants
 */
#define DEFAULT_HEIGHT 24
#define DEFAULT_WIDTH 80


/*****************************************************************************
 * Strings
 *****************************************************************************/
#define CR_WELCOME_MESSAGE          "Welcome to CROGUE... Uga Uga!"
#define CR_WELCOME_START_MESSAGE    "-- press [enter] to start --"

#define CR_PLAY_MESSAGE             "You are having fun... Uga Booga!"
#define CR_PLAY_ACTION_MESSAGE      "-- press [escape] to lose or [enter] to win --"

#define CR_WIN_MESSAGE             "You Won! ... Uga Booga Uga Wooga!"
#define CR_WIN_ACTION_MESSAGE      "-- press [enter] to restart --"

#define CR_LOSE_MESSAGE             "You Lost! ... Uga Looga Looga"
#define CR_LOSE_ACTION_MESSAGE      "-- press [enter] to restart --"

#endif /* !CR_CONSTANTS_H */
