/*
 * Crogue
 *
 * Written by Robert Kerr
 * Started: 01/22/2020
 */

#include <SDL2/SDL.h> /* Using SDL */
#include <SDL2/SDL_image.h> /* Using SDL */
#include <stdbool.h>  /* For bool, true, and false */
#include <stdint.h>   /* For uintxx_t types */

#include "game.h"
#include "console.h"
#include "texture.h"

/* Screen dimension constants 
 */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/* Starts up SDL and creates window
 */
bool cr_init( cr_game_t *theGame );

/* Loads individual image
 */
SDL_Surface* cr_loadSurface( cr_game_t* theGame, char* path );

/* Loads individual image as texture
 */
SDL_Texture* cr_loadTexture( cr_game_t* theGame, char* path );

/* Loads media
 */
bool cr_loadMedia( cr_game_t* theGame );

/* Frees media and shuts down SDL
 */
void cr_close( cr_game_t *theGame );

/* Renders a console to the the screen using tile set glyphs
 */
void cr_render_console( rk_console_t *console, rk_texture_t *tileSet, SDL_Renderer *renderer );

bool cr_init( cr_game_t *theGame )
{
    int imgFlags;

    /* Initialization flag */
    bool success = true;

    /* Initialize the console */
    theGame->console = rk_console_init( 16, 16 );

    if( theGame->console == NULL ) {
        printf( "Coule not initialize the console!\n" );
        success = false;
    }

    /* Initialize SDL */
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        /* Create window */
        theGame->window = SDL_CreateWindow( "Crogue Game", 
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                SCREEN_WIDTH, SCREEN_HEIGHT, 
                SDL_WINDOW_SHOWN );
        if( theGame->window == NULL ) {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            /* Create renderer for window */
            theGame->renderer = SDL_CreateRenderer( theGame->window, -1, SDL_RENDERER_ACCELERATED );
            if( theGame->renderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                /* Initialize renderer color */
                SDL_SetRenderDrawColor( theGame->renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                /* Initialize PNG Loading */
                imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

SDL_Surface* cr_loadSurface( cr_game_t* theGame, char* path )
{
    /* The final optimized image */
    SDL_Surface* optimizedSurface = NULL;

    /* Load image at specified path */
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    } else {
        /* Convert surface to screen format */
        optimizedSurface = SDL_ConvertSurface( loadedSurface, theGame->screenSurface->format, 0 );
        if( optimizedSurface == NULL ) {
            printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        /* Get rid of old loaded surface */
        SDL_FreeSurface( loadedSurface );
    }

    return optimizedSurface;
}

SDL_Texture* cr_loadTexture( cr_game_t* theGame, char* path )
{
    /* The final texture */
    SDL_Texture* newTexture = NULL;

    /* Load image at specified path */
    SDL_Surface* loadedSurface = IMG_Load( path );
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    } else {
        /* Create texture from surface pixels */
        newTexture = SDL_CreateTextureFromSurface( theGame->renderer, loadedSurface );

        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }

        /* Get rid of old loaded surface */
        SDL_FreeSurface( loadedSurface );
    }

    return newTexture;
}

bool cr_loadMedia( cr_game_t* theGame )
{
    /* Loading success flag */
    bool success = true;

    /* Load splash image */
    theGame->tileSet = rk_texture_create();
    if( theGame->tileSet == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", "assets/Spacefox_16x16.png", SDL_GetError() );
        success = false;
    } else {
        if( !rk_texture_loadFromFile( theGame->tileSet, theGame->renderer, "assets/Spacefox_16x16.png" ) ) {
            /*Failed - Clean up and return false */
            rk_texture_destroy( theGame->tileSet );

            printf( "Unable to load image %s! SDL Error: %s\n", "assets/Spacefox_16x16.bmp", SDL_GetError() );
            success = false;
        } /* else */
            /* Success */
    }

    return success;
}

void cr_close( cr_game_t *theGame )
{
    /* Deallocate surface */
    rk_texture_destroy( theGame->tileSet );
    theGame->tileSet = NULL;

    /* Destroy window */
    SDL_DestroyWindow( theGame->window );
    theGame->window = NULL;

    /* Quit SDL subsystems */
    SDL_Quit();

    /* Clean up the console */
    rk_console_destroy( theGame->console );
    theGame->console = NULL;

    return;
}

void cr_render_console( rk_console_t *console, rk_texture_t *tileSet, SDL_Renderer *renderer ) {

    /* Loop iterators */
    uint16_t iter_height;
    uint16_t iter_width;
    SDL_Rect src_rect;
    SDL_Rect dst_rect;
    uint16_t TILE_SIZE = 16;
    uint8_t glyph;

    /* Console information */
    const uint16_t c_height = rk_console_height( console );
    const uint16_t c_width = rk_console_width( console );
    const rk_tile_t *c_tiles = rk_console_tiles( console );

    /* Setup our source and destination rects */
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = TILE_SIZE;
    src_rect.h = TILE_SIZE;

    /* Setup our source and destination rects */
    dst_rect.x = 0;
    dst_rect.y = 0;
    dst_rect.w = SCREEN_WIDTH / 16;
    dst_rect.h = SCREEN_HEIGHT/ 16;

    /* Iterate the glyphs */
    for( iter_height = 0; iter_height < c_height; iter_height++ ) {
        for( iter_width = 0; iter_width < c_width; iter_width++ ) {
            glyph = c_tiles[ iter_height * c_height + iter_width ].glyph;
            /*glyph = (iter_height * c_height) + iter_width;*/

            /* Do some mojo for the src rect to get the right glyph */
            src_rect.x = glyph % 16 * TILE_SIZE;
            src_rect.y = ((uint8_t)(glyph) / 16) * TILE_SIZE;

            /* Do some mojo for the dst rect to put it in the right place */
            /* For now just wing it */
            dst_rect.x = iter_width * (SCREEN_WIDTH / 16);
            dst_rect.y = iter_height * (SCREEN_HEIGHT / 16);

            /*printf("%u, Loc %u,%u is src %u,%u\n", glyph, iter_height, iter_width, src_rect.x, src_rect.y);
            printf("Loc %u,%u is dst %u,%u\n", iter_height, iter_width, dst_rect.x, dst_rect.y);
            fflush(stdout); */

            /* Render each glyph to the renderer */
            rk_texture_render( tileSet, renderer, 0, 0, &src_rect, &dst_rect );
        }
    }

    return;
}


int main( int argc, char* args[])
{
    /* Create our game object */
    cr_game_t theGame;

    /* Initialize the game */
    theGame.window = NULL;
    theGame.screenSurface = NULL;
    theGame.tileSet = NULL;
    theGame.console = NULL;

    /* Start up SDL and create window */
    if( !cr_init( &theGame ) ) {
        printf( "Failed to initialize!\n" );
    } else {
        /* Load media */
        if( !cr_loadMedia( &theGame ) ) {
            printf( "Failed to load media!\n" );
        } else {
            /* Main loop flag */
            bool quit = false;

            /* Event handler */
            SDL_Event e;

            /* While application is running */
            while( !quit ) {
                /* Handle events on queue */
                while( SDL_PollEvent( &e ) != 0 ) {
                    /* User requests quit */
                    if( e.type == SDL_QUIT ) {
                        quit = true;
                    }
                }

                /* Clear screen */
                SDL_SetRenderDrawColor( theGame.renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( theGame.renderer );

                /* Render texture to screen */
                rk_texture_render( theGame.tileSet, theGame.renderer, 0, 0, NULL, NULL );

                /* Update screen */
                SDL_RenderPresent( theGame.renderer );
            }
        }
    }

    /* Free resources and close SDL */
    cr_close( &theGame );

    return 0;
}
