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

bool cr_init( cr_game_t *theGame )
{
    int imgFlags;

    /* Initialization flag */
    bool success = true;

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
    theGame->helloTexture = rk_texture_create();
    if( theGame->helloTexture == NULL ) {
        printf( "Unable to load image %s! SDL Error: %s\n", "assets/hello.png", SDL_GetError() );
        success = false;
    } else {
        if( !rk_texture_loadFromFile( theGame->helloTexture, theGame->renderer, "assets/hello.png" ) ) {
            /*Failed - Clean up and return false */
            rk_texture_destroy( theGame->helloTexture );

            printf( "Unable to load image %s! SDL Error: %s\n", "Spacefox_16x16.bmp", SDL_GetError() );
            success = false;
        } /* else */
            /* Success */
    }

    return success;
}

void cr_close( cr_game_t *theGame )
{
    /* Deallocate surface */
    rk_texture_destroy( theGame->helloTexture );
    theGame->helloTexture = NULL;

    /* Destroy window */
    SDL_DestroyWindow( theGame->window );
    theGame->window = NULL;

    /* Quit SDL subsystems */
    SDL_Quit();
}

int main( int argc, char* args[])
{
    /* Create our game object */
    cr_game_t theGame;

    /* Initialize the game */
    theGame.window = NULL;
    theGame.screenSurface = NULL;
    theGame.helloTexture = NULL;

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
                rk_texture_render( theGame.helloTexture, theGame.renderer, 0, 0, NULL, NULL );

                /* Update screen */
                SDL_RenderPresent( theGame.renderer );
            }
        }
    }

    /* Free resources and close SDL */
    cr_close( &theGame );

    return 0;
}
