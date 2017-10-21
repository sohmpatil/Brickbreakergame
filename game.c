#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h" 
#include "SDL2/SDL_mixer.h"

//Screen Dimension Defining
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//Defining true and false values for further use
#define true 1
#define false 0
#define TRUE 1
#define FALSE 0

//For ball and paddle (For paddle set y_velocity as 0)
typedef struct object {
	SDL_Rect position;
	int x_velocity;
	int y_velocity;
}object;

//For bricks
typedef struct bricks {
	SDL_Rect position1;
	int alive;//For hardness of the brick
}bricks;

//Showing the menu of(1.Play/Resume 2.Easy 3.Hard 4.Quit)
int menu();

//Ball and paddle collision checking
int checkcollision1();

//Ball and Wall collision checking(If the ball touches the lower part of the game goes to reset)
int checkcollision2();

//Ball and Brick Collision
int checkcollision3();

int main(int argc, char *argv[]) {
	//int select;
	
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL Initialization Error: %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_Window *window = SDL_CreateWindow("Brick Breaker Game",
						SDL_WINDOWPOS_CENTERED,
						SDL_WINDOWPOS_CENTERED,
						SCREEN_WIDTH,
						SCREEN_HEIGHT,
						SDL_WINDOW_RESIZABLE);
	
	if(window == NULL) {
		printf("Window Initialization Error :%s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	
	//Create a renderer which sets up the graphics hardware
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *rend = SDL_CreateRenderer(window,
						-1,
						render_flags);
	
	if(!rend) {
		printf("Renderer Creating Error :%s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	SDL_Surface *surface = IMG_Load("Resources/background.jpg");
	
	if(!surface) {
		printf("Surface Creating Error :%s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_Texture *tex = SDL_CreateTextureFromSurface(rend,
						surface);
	SDL_FreeSurface(surface);
	if(!tex) {
		printf("Texture Creating Error :%s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, tex, NULL, NULL);
	SDL_RenderPresent(rend);
	SDL_Event event;
	int isRunning = TRUE;
	
	//main game loop
	while(isRunning) {
		//Event handling
		while(SDL_PollEvent(&event) != 0) {
			if(event.type == SDL_QUIT) {
				isRunning = FALSE;
			}
		}
		
		//Logic
		
		//Rendering
		
	}
	
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
