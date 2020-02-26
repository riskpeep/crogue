/*
 * rk_util
 *
 * Provides utility functions
 *
 * Written by Robert Kerr
 * Started: 01/18/2020
 */

#include "util.h"

bool cr_dummy_data( rk_console_t* theConsole ) {

    uint16_t c_height = rk_console_height( theConsole );
    uint16_t c_width = rk_console_width( theConsole );
    rk_tile_t *tiles = rk_console_tiles( theConsole );
    uint16_t i_height, i_width;

    /* Fill the console up with dummy data */
    /* First set the ground to ground */
    memset( tiles, 0x2e, c_height * c_width * sizeof( rk_tile_t ) );

    /* Next set the edges to walls */
    for( i_height = 0; i_height < c_height; i_height++ ) {
        for( i_width = 0; i_width < c_width; i_width++ ) {
            if((( i_height == 0 )              && (( i_width == 0 ) || ( i_width == ( c_width - 1 )))) ||
               (( i_height == ( c_height - 1 )) && (( i_width == 0 ) || ( i_width == ( c_width - 1 ))))) {
                tiles[ i_height * c_width + i_width ].glyph = 0x2b; 
            } else if(( i_height == 0 ) || ( i_height == ( c_height - 1))) {
                tiles[ i_height * c_width + i_width ].glyph = 0x2d;
            } else if(( i_width == 0 ) || ( i_width == ( c_width - 1))) {
                tiles[ i_height * c_width + i_width ].glyph = 0x7c;
            }
        }
    }

    return false;
}
