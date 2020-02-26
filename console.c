/*
 * rk_console
 *
 * Provides an emulation of a code page 437 based terminal display
 *
 * Written by Robert Kerr
 * Started: 01/18/2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "console.h"

struct rk_console_t {
    uint16_t height;
    uint16_t width;

    rk_tile_t* tileArray;
};

/* Create a new console
 * Creates a new console.  This is the only way to create a console.
 */
rk_console_t *rk_console_init( uint16_t height, uint16_t width ) {

    /* Create a new console */
    rk_console_t* newConsole = (rk_console_t *)malloc( sizeof( rk_console_t ) );

    if( newConsole == NULL ) {
        /* Failure - Couldn't create a console.  Return NULL */
        return NULL;
    }

    /* Did we get good sizes */
    if(( height == 0 ) || ( width == 0 )) {
        /* No, use the defaults */
        height = RK_CONSOLE_DEFAULT_WIDTH;
        width = RK_CONSOLE_DEFAULT_HEIGHT;
    }

    /* Success - Initialize the members */
    newConsole->height = height;
    newConsole->width = width;
    newConsole->tileArray =
        (rk_tile_t *)calloc(height * width, sizeof( rk_tile_t ) );

    if( newConsole->tileArray == NULL ) {
        /* Failure - Couldn't create the tileArray */

        /* First, clean up the partially created console */
        free( newConsole );

        /* And return NULL to indicate failure */
        return NULL;
    }

    /* Success */
    return newConsole;
}

/* Destroy a console
 */
void rk_console_destroy( rk_console_t* console ) {

    /* First check and free the tile array */
    if( console->tileArray != NULL ) {
        /* Free the tile array */
        free( console->tileArray );
        console->tileArray = NULL;
    }

    free( console );

    return;
}


/* Gets the console height
 */
const uint16_t rk_console_height( rk_console_t *console ) {
    return console->height;
}

/* Gets the console width
 */
const uint16_t rk_console_width( rk_console_t *console ) {
    return console->width;
}

/* Gets the console tile array
 */
rk_tile_t* rk_console_tiles( rk_console_t *console ) {
    return console->tileArray;
}

/* Clears the console and fills it with the given character
 */
bool rk_console_clear( rk_console_t *console, const char clearChar ) {
    uint16_t tileIter = 0;

    /* Iterate all the glyphs and set to clearChar */
    for( tileIter = 0; tileIter < ( console->width * console->height ); tileIter++ ) {
        console->tileArray[ tileIter ].glyph = clearChar;
    }

    return true;
}

/* Writes text on the console
 */
bool rk_console_write( rk_console_t* console, const uint16_t posX, const uint16_t posY, const char *textString ) {
    bool success = false;
    size_t textLen = 0;
    size_t textIter = 0;

    /* How long is the string? */
    textLen = strlen( textString );

    /* Is the location valid? */
    if((( posX + textLen ) > console->width ) || ( posY > console->height )) {
        success = false;
    } else {
        /* Write the string */
        for( textIter = 0; textIter < textLen; textIter++ ) {
            console->tileArray[( posX + textIter ) + ( posY * console->width )].glyph = textString[ textIter ];
        }
    }

    return success;
}

