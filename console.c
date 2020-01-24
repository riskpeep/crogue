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

    printf("Height = %u, Width = %u\n", height, width);

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

