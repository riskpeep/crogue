/*
 * rk_util
 *
 * Provides utility functions
 *
 * Written by Robert Kerr
 * Started: 01/18/2020
 */

#include "util.h"

bool cr_dummy_data( cr_game_t* theGame ) {

    uint16_t c_height = rk_console_height( theGame->console );
    uint16_t c_width = rk_console_width( theGame->console );
    rk_tile_t *tiles = rk_console_tiles( theGame->console );
    uint16_t i_height, i_width;

    /* Fill the console up with dummy data */
    /* First set the ground to ground */
    memset( tiles, 0x7e, c_height * c_width * sizeof( rk_tile_t ) );

    /* Next set the edges to walls */
    for( i_height = 0; i_height < c_height; i_height++ ) {
        for( i_width = 0; i_width < c_width; i_width++ ) {
            if(( i_height == 0 ) || ( i_height == ( c_height - 1)) ||
                    ( i_width == 0 ) || ( i_width == ( c_width - 1))) {
                tiles[ i_height * c_height + i_width ].glyph = 0x8e;
            }
        }
    }

    return false;
}
