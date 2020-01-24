/*
 * rk_console
 *
 * Provides an emulation of a code page 437 based terminal display
 *
 * Written by Robert Kerr
 * Started: 01/18/2020
 */

#ifndef RK_CONSOLE_H
#define RK_CONSOLE_H

#include <stdbool.h>
#include <stdint.h>

/*****************************************************************************
 * Defaults and constants
 *****************************************************************************/
#define RK_CONSOLE_DEFAULT_HEIGHT  24
#define RK_CONSOLE_DEFAULT_WIDTH   80
/*****************************************************************************
 * Console Types
 *****************************************************************************/
typedef struct rk_tile_t {
    uint8_t glyph;
    bool isDirty;
} rk_tile_t ;

/*****************************************************************************
 * Opaque types
 *****************************************************************************/
typedef struct rk_console_t rk_console_t;

/*****************************************************************************
 * Console API
 *****************************************************************************/

/* Create a new console
 * Creates a new console.  This is the only way to create a console.
 *
 * @param height The height of the console in tiles
 * @param width The width of the console in tiles
 * @return A new console object
 */
rk_console_t *rk_console_init( uint16_t height, uint16_t width );

/* Destroy a console
 * Destroys an existing console.  This operation deletes the console and all
 * tilesets, and tilemaps associated with it.
 *
 * @param console The console to destroy.
 */
void rk_console_destroy( rk_console_t *console );

/* Gets the console height
 *
 * @return The console height
 */
const uint16_t rk_console_height( rk_console_t *console );

/* Gets the console width
 *
 * @return The console width
 */
const uint16_t rk_console_width( rk_console_t *console );

/* Gets the console tile array
 *
 * @return The console tile array
 */
rk_tile_t* rk_console_tiles( rk_console_t *console );

#endif /* !RK_CONSOLE_H */
