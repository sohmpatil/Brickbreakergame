#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_mixer.h"

//Defining Screen Width and Height
#define SCREEN_W 640
#define SCREEN_H 480

//Defining Paddle1 Parameters
#define PADDLE1_W 80
#define PADDLE1_H 10

//Defining Paddle2 Parameters
#define PADDLE2_W 120
#define PADDLE2_H 10 

//Defining Ball Parameters
#define BALL_W 30
#define BALL_H 30

//Defining Brick Position
#define BRICK_W 35
#define BRICK_H 20

//Defining Number of the bricks1
#define NUMBRICKS 27

//Defining max number of menu boxes
#define MAXMENU 6

//Defining Body Structure for paddles & balls
typedef struct body {
	SDL_Rect place;
	int x_vel;
	int y_vel;
}body;

//Defining Body Structure for bricks
typedef struct brick {
	SDL_Rect bplace[NUMBRICKS];
	int alive[NUMBRICKS];
}brick;

//Creating Renderer Variable
SDL_Renderer *rend = NULL;

//Creating True Type Font
TTF_Font *fonts;

//Declaring Collision Function For Balls and Paddle
int collision(body *a, body *b);

//Declaring Collision Function For Balls and Brick
int collision1(body *a, SDL_Rect *rects);

//Declaring the menu function
int menu();

int main(int argc, char *argv[]) {
	//Integer declaration for all the for loops needed
	int i, j, k, l, m, n;
	
	//Integer declaration for level taking in pause
	int le1, le2, le3, le4;
	
	//Declaring the integer for getting the option from menu
	int choice;
	
	//Declaring the integer for level deciding
	int level;
	
	//Defining Paddles as a variable of the body
	body paddle1, paddle2;
	
	//Defining Balls as a variable of the body
	body ball1, ball2;
	
	//Defining bricks1 as a variables
	brick bricks1, bricks2;
	
	//Defining Youwin image as a variable of body
	body youwin;
	
	//Defining number bricks removed are zero at first
	int count;
	
	//Defining variable for main game loop
	int isRunning;
	
	SDL_Window *window;
	
	//Declaring Textures For The Uses Of Different Images
	SDL_Texture *tex = NULL;
	SDL_Texture *tex1 = NULL;
	SDL_Texture *tex2 = NULL;
	SDL_Texture *tex3 = NULL;
	SDL_Texture *tex4 = NULL;
	SDL_Texture *tex5 = NULL;
	SDL_Texture *tex6 = NULL;
	SDL_Texture *tex7 = NULL;
	SDL_Surface *img;
	
	//Defining the position of the paddle1
	paddle1.place.x = (SCREEN_W - PADDLE1_W) / 2;
	paddle1.place.y = 400;
	paddle1.place.w = PADDLE1_W;
	paddle1.place.h = PADDLE1_H;
	
	//Defining the position of the paddle2
	paddle2.place.x = (SCREEN_W - PADDLE2_W) / 2;
	paddle2.place.y = 400;
	paddle2.place.w = PADDLE2_W;
	paddle2.place.h = PADDLE2_H;
	
	//Defining the position of the ball1
	ball1.place.x = 160;
	ball1.place.y = 400;
	ball1.place.w = BALL_W;
	ball1.place.h = BALL_H;
	
	//Defining the position of the ball2
	ball2.place.x = BALL_W - 160;
	ball2.place.y = 400;
	ball2.place.w = BALL_W;
	ball2.place.h = BALL_H;
	
	//Defining the position of the brick1
	for(i = 0; i < NUMBRICKS; i++) {
		bricks1.bplace[i].x = (20 + (70 * i));	
		bricks1.bplace[i].y = 10;
		
		if(bricks1.bplace[i].x < (SCREEN_W * 2 - 10) && bricks1.bplace[i].x >= SCREEN_W) {
			bricks1.bplace[i].x = bricks1.bplace[i].x - (SCREEN_W - 10);
			bricks1.bplace[i].y = bricks1.bplace[i].y + (10 + 40);
		}
		
		if(bricks1.bplace[i].x >= (SCREEN_W * 2 - 10) && bricks1.bplace[i].x < (SCREEN_W * 3 - 20)) {
			bricks1.bplace[i].x = bricks1.bplace[i].x - (2 * (SCREEN_W - 10));
			bricks1.bplace[i].y = bricks1.bplace[i].y + ((10 + 40) * 2);
		}
		
		if(bricks1.bplace[i].x >= (SCREEN_W * 3 - 20) && bricks1.bplace[i].x < (SCREEN_W * 4 - 30)) {
			bricks1.bplace[i].x = bricks1.bplace[i].x - (3 * (SCREEN_W - 10));
			bricks1.bplace[i].y = bricks1.bplace[i].y + ((10 + 40) * 3);
		}
		
		if(bricks1.bplace[i].x >= (SCREEN_W * 4 - 30) && bricks1.bplace[i].x < (SCREEN_W * 5 - 40)) {
			bricks1.bplace[i].x = bricks1.bplace[i].x - (4 * (SCREEN_W - 10));
			bricks1.bplace[i].y = bricks1.bplace[i].y + ((10 + 40) * 4);
		}
		
		if(bricks1.bplace[i].x >= (SCREEN_W * 5 - 40) && bricks1.bplace[i].x < (SCREEN_W * 6 - 50)) {
			bricks1.bplace[i].x = bricks1.bplace[i].x - (5 * (SCREEN_W - 10));
			bricks1.bplace[i].y = bricks1.bplace[i].y + ((10 + 40) * 5);
		}
		bricks1.bplace[i].w = BRICK_W;
		bricks1.bplace[i].h = BRICK_H;
	}
	
	//Defining the position of the brick2
	for(i = 0; i < NUMBRICKS; i++) {
		bricks2.bplace[i].x = (20 + (70 * i)) - 2;	
		bricks2.bplace[i].y = 10 - 2;
		
		if(bricks2.bplace[i].x < (SCREEN_W * 2 - 10) && bricks2.bplace[i].x >= SCREEN_W) {
			bricks2.bplace[i].x = bricks2.bplace[i].x - (SCREEN_W - 10) - 2;
			bricks2.bplace[i].y = bricks2.bplace[i].y + (10 + 40) - 2;
		}
		
		if(bricks2.bplace[i].x >= (SCREEN_W * 2 - 10) && bricks2.bplace[i].x < (SCREEN_W * 3 - 20)) {
			bricks2.bplace[i].x = bricks2.bplace[i].x - (2 * (SCREEN_W - 10)) - 2;
			bricks2.bplace[i].y = bricks2.bplace[i].y + ((10 + 40) * 2) - 2;
		}
		
		if(bricks2.bplace[i].x >= (SCREEN_W * 3 - 20) && bricks2.bplace[i].x < (SCREEN_W * 4 - 30)) {
			bricks2.bplace[i].x = bricks2.bplace[i].x - (3 * (SCREEN_W - 10)) - 2;
			bricks2.bplace[i].y = bricks2.bplace[i].y + ((10 + 40) * 3) - 2;
		}
		
		if(bricks2.bplace[i].x >= (SCREEN_W * 4 - 30) && bricks2.bplace[i].x < (SCREEN_W * 5 - 40)) {
			bricks2.bplace[i].x = bricks2.bplace[i].x - (4 * (SCREEN_W - 10)) - 2;
			bricks2.bplace[i].y = bricks2.bplace[i].y + ((10 + 40) * 4) - 2;
		}
		
		if(bricks2.bplace[i].x >= (SCREEN_W * 5 - 40) && bricks2.bplace[i].x < (SCREEN_W * 6 - 50)) {
			bricks2.bplace[i].x = bricks2.bplace[i].x - (5 * (SCREEN_W - 10)) - 2;
			bricks2.bplace[i].y = bricks2.bplace[i].y + ((10 + 40) * 5) - 2;
		}
		bricks2.bplace[i].w = BRICK_W + 4;
		bricks2.bplace[i].h = BRICK_H + 4;
	}
	
	//Defining Position of the youuwin window
	youwin.place.x = 0;
	youwin.place.y = 0;
	youwin.place.w = SCREEN_W;
	youwin.place.h = SCREEN_H;
	
	//Defining Ball1 Velocity
	ball1.x_vel = 3;
	ball1.y_vel = - 3;
	
	//Defining Ball2 Velocity
	ball2.x_vel = - 2;
	ball2.y_vel = - 2;
	
	//Initialize TTF
	if( TTF_Init() < 0){
		printf( "Error Initialising Text:\n ");
	}
	
	//Font Loading
	fonts = TTF_OpenFont("Resources/courier.ttf", 80);
	
	if( fonts == NULL ){ 
		printf("Font didn't load TTF Error : %s\n", TTF_GetError());
	}
	
	//Initialising Audio and Video
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO );
	
	if(SDL_Init( SDL_INIT_VIDEO ) < 0 || SDL_INIT_AUDIO < 0) {
		printf("SDL Initialising Error: %s\n", SDL_GetError());
	}
	
	else if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("Audio Initialising Error: %s\n ", SDL_GetError());
	}
	else {
		//Creating Window
		window = SDL_CreateWindow("Brick Breaker Game",
					SDL_WINDOWPOS_UNDEFINED,
					SDL_WINDOWPOS_UNDEFINED,
					SCREEN_W,
					SCREEN_H,
					SDL_WINDOW_RESIZABLE);
		
		//Create Renderer
		rend = SDL_CreateRenderer(window,
					-1,
					SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		
		//Loading Music In The Renderer
		Mix_Chunk *ballwall = Mix_LoadWAV("Resources/tune1.wav");
		
		Mix_Chunk *ballbrick = Mix_LoadWAV("Resources/tune2.wav");
		
		Mix_Chunk *ballpaddle = Mix_LoadWAV("Resources/tune3.wav");
		
		Mix_Chunk *youwins = Mix_LoadWAV("Resources/youwin.wav");
		
		if(window == NULL) {
			printf("Window Creating Error: %s\n", SDL_GetError());
			return 1;
		}
		
		else {
			//Draw Black Color on Screen
			SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
			
			//Clearing the Renderer
			SDL_RenderClear(rend);
			
			//Presnting window on screen
			SDL_RenderPresent(rend);
			
			//Make the Rendering Smoother
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			
			//Setting the logical size 640 * 480
			SDL_RenderSetLogicalSize(rend, SCREEN_W, SCREEN_H);
			
			img = IMG_Load("Resources/background.jpg");
			
			if(img == NULL) {
				printf("Unable to load background.jpg. Error :%s\n", SDL_GetError());
				return 1;
			}
			
			//Creating Texture From The Surface
			tex = SDL_CreateTextureFromSurface(rend, img);
			
			//Free Surface
			SDL_FreeSurface(img);
			
			//Checking if the texture is copied from the Surface
			if(tex == NULL) {
				printf("Unable to load Surface Into Texture. backgroun.jpg SDL Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading Paddle Image
			img = SDL_LoadBMP("Resources/paddle1.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex1 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex1 == NULL) {
				printf("Unable to load Paddle1 image. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading Ball Image 
			img = SDL_LoadBMP("Resources/ball1.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex2 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex2 == NULL) {
				printf("Unable to load ball1 image. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading Brick Image 1
			img = SDL_LoadBMP("Resources/brick1.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex3 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex3 == NULL) {
				printf("Unable to load brick image1. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading Brick Image 2
			img = SDL_LoadBMP("Resources/brick2.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex4 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex4 == NULL) {
				printf("Unable to load brick image2. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading Ball2 Image
			img = SDL_LoadBMP("Resources/ball2.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex5 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex5 == NULL) {
				printf("Unable to load ball2 image. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading Paddle Image
			img = SDL_LoadBMP("Resources/paddle2.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex6 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex6 == NULL) {
				printf("Unable to load Paddle2 image. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			//Loading You Win Image
			img = SDL_LoadBMP("Resources/youwin.bmp");
			SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 255, 255, 255));
			tex7 = SDL_CreateTextureFromSurface(rend, img);
			SDL_FreeSurface(img);
			
			if(tex7 == NULL) {
				printf("Unable to load youwin image. Error: %s\n", SDL_GetError());
				return 1;
			}
			
			TTF_WasInit();
			
			LOOPN:
			
			//Defining the bricks broken to be zero
			count = 0;
			
			//Game loop running case
			isRunning = 1;
			
			choice = menu();
			
			if(choice == 1) {
				level = 1;
			}
			
			else if(choice == 2) {
				level = 1;
			}
			
			else if(choice == 3) {
				level = 2;
			}
			
			else if(choice == 4) {
				level = 3;
			}
			
			else if(choice == 5) {
				level = 4;
			}
			
			else if(choice == 6) {
				return 1;
			}
			
			LOOP1:
			
			switch(level) {
				case 1:
					
					//Defining Brick Alive Condition
					for(j = 0; j < NUMBRICKS; j++) {
						bricks1.alive[j] = 1;
					}
						
					ball1.place.x = 160;
					ball1.place.y = 400;
					ball1.place.w = BALL_W;
					ball1.place.h = BALL_H;
					
					LOOP:
					count = 0;
					
					//Main Game Loop
					while(isRunning) {
						
						//Event Handling
						SDL_Event event;
				
						//if all bricks1 are removed
						if(count == NUMBRICKS) {
							SDL_RenderClear(rend);
							SDL_RenderCopy(rend, tex7, NULL, &youwin.place);
							SDL_RenderPresent(rend);
							Mix_PlayChannel(-1, youwins, 0);
							SDL_Delay(2000);
							SDL_RenderClear(rend);
							goto LOOPN;
						}
				
						//Defining Ball1 Velocity_X
						ball1.place.x = ball1.place.x + ball1.x_vel;
				
						for(l = 0; l < NUMBRICKS; l++) {
							if(bricks1.alive[l] == 1) {
								if(collision1(&ball1, &bricks1.bplace[l]) == 1) {
									bricks1.alive[l] = 0;
									ball1.x_vel = - ball1.x_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
				
						//Defining Ball1 Velocity_Y
						ball1.place.y = ball1.place.y + ball1.y_vel;
				
						for(m = 0; m < NUMBRICKS; m++) {
							if(bricks1.alive[m] == 1) {
								if(collision1(&ball1, &bricks1.bplace[m]) == 1) {
									bricks1.alive[m] = 0;
									ball1.y_vel = - ball1.y_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
				
						//Collision of ball1 with the left wall
						if(ball1.place.x < 0) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of ball1 with the upper wall
						if(ball1.place.y < 0) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of the ball1 with the right wall
						if(ball1.place.x + ball1.place.w + 0 > SCREEN_W) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of the ball1 with the lower wall
						if(ball1.place.y + ball1.place.h > SCREEN_H) {
							ball1.y_vel = - ball1.y_vel;
							for(n = 0; n < NUMBRICKS; n++) {
								bricks1.alive[n] = 1;
							}
							ball1.place.x = 160;
							ball1.place.y = 400;
							ball1.x_vel = 3;
							ball1.y_vel = - 3;
							count = 0;
						}
				
						//Collision of the ball1 with paddle1
						if(collision(&ball1, &paddle1) == 1) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballpaddle, 0);
						}
				
						while(SDL_PollEvent(&event)) {
					
							//If the quit icon is clicked
							if(event.type == SDL_QUIT) {
								isRunning = 0;
								break;
							}
					
							if(event.type != SDL_KEYDOWN) {
								break;
							}
							SDL_Keycode keys = event.key.keysym.sym;
					
							switch(keys) {
								case SDLK_ESCAPE:
									le1 = menu();
									
									if(le1 == 1) {
										goto LOOP;
									}
									
									if(le1 == 2) {
										level = 1;
										goto LOOP1;
									}
									
									if(le1 == 3) {
										level = 2;
										goto LOOP1;
									}
									
									if(le1 == 4) {
										level = 3;
										goto LOOP1;
									}
									
									if(le1 == 5) {
										level = 4;
										goto LOOP1;
									}
									
									if(le1 == 6) {
										isRunning = 0;
									}
									
									break;
						
								case SDLK_LEFT:
									if(paddle1.place.x < 5) {
										break;
									}
									else{
										paddle1.place.x = paddle1.place.x - 20;
									}
									break;
						
								case SDLK_RIGHT:
									if(paddle1.place.x + paddle1.place.w + 5 > SCREEN_W) {
										break;
									}
									paddle1.place.x = paddle1.place.x + 20;
									break;

								case SDLK_a:
									if(paddle1.place.x < 5) {
										break;
									}
									else {
										paddle1.place.x = paddle1.place.x - 20;
									}
									break;

								case SDLK_d:
									if(paddle1.place.x + paddle1.place.w + 5 > SCREEN_W) {
										break;
									}
									else {
										paddle1.place.x = paddle1.place.x + 20;
									}
									break;

								default:
									break;
							}
						}
			
						//Clearing renderer
						SDL_RenderClear(rend);
				
						//Copying Each Texture On Renderer
						SDL_RenderCopy(rend, tex, NULL, NULL);
						SDL_RenderCopy(rend, tex1, NULL, &paddle1.place);
						SDL_RenderCopy(rend, tex2, NULL, &ball1.place);
						for(k = 0; k < NUMBRICKS; k++) {
							if(bricks1.alive[k] == 1) {
								SDL_RenderCopy(rend, tex3, NULL, &bricks1.bplace[k]);
							}
						}
				
						//Setting the Render as present
						SDL_RenderPresent(rend);
					}
					break;
				case 2:
					//Defining Brick Alive Condition
					for(j = 0; j < NUMBRICKS; j++) {
						bricks2.alive[j] = 1;
						bricks1.alive[j] = 0;
					}
					
					ball1.place.x = 160;
					ball1.place.y = 400;
					ball1.place.w = BALL_W;
					ball1.place.h = BALL_H;
					
					LOOP2:
					count = 0;
					
					//Main Game Loop
					while(isRunning) {
						//Event Handling
						SDL_Event event;
				
						//if all bricks1 are removed
						if(count == NUMBRICKS) {
							SDL_RenderClear(rend);
							SDL_RenderCopy(rend, tex7, NULL, &youwin.place);
							SDL_RenderPresent(rend);
							Mix_PlayChannel(-1, youwins, 0);
							SDL_Delay(2000);
							SDL_RenderClear(rend);
							goto LOOPN;
						}
				
						//Defining Ball1 Velocity_X
						ball1.place.x = ball1.place.x + ball1.x_vel;
				
						for(l = 0; l < NUMBRICKS; l++) {
							if(bricks1.alive[l] == 1) {
								if(collision1(&ball1, &bricks1.bplace[l]) == 1) {
									bricks1.alive[l] = 0;
									ball1.x_vel = - ball1.x_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
						for(l = 0; l < NUMBRICKS; l++) {
							if(bricks2.alive[l] == 1) {
								if(collision1(&ball1, &bricks2.bplace[l]) == 1) {
									bricks1.alive[l] = 1;
									bricks2.alive[l] = 0;
									ball1.x_vel = - ball1.x_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
								}
							}
						}
				
						//Defining Ball1 Velocity_Y
						ball1.place.y = ball1.place.y + ball1.y_vel;
				
						for(m = 0; m < NUMBRICKS; m++) {
							if(bricks1.alive[m] == 1) {
								if(collision1(&ball1, &bricks1.bplace[m]) == 1) {
									bricks1.alive[m] = 0;
									ball1.y_vel = - ball1.y_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
						
						for(m = 0; m < NUMBRICKS; m++) {
							if(bricks2.alive[m] == 1) {
								if(collision1(&ball1, &bricks2.bplace[m]) == 1) {
									bricks1.alive[m] = 1;
									bricks2.alive[m] = 0;
									ball1.y_vel = - ball1.y_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
								}
							}
						}
				
						//Collision of ball1 with the left wall
						if(ball1.place.x < 0) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of ball1 with the upper wall
						if(ball1.place.y < 0) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of the ball1 with the right wall
						if(ball1.place.x + ball1.place.w + 0 > SCREEN_W) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of the ball1 with the lower wall
						if(ball1.place.y + ball1.place.h > SCREEN_H) {
							ball1.y_vel = - ball1.y_vel;
							for(n = 0; n < NUMBRICKS; n++) {
								bricks2.alive[n] = 1;
								bricks1.alive[n] = 0;
							}
							ball1.place.x = 160;
							ball1.place.y = 400;
							ball1.x_vel = 3;
							ball1.y_vel = - 3;
							count = 0;
						}
				
						//Collision of the ball1 with paddle1
						if(collision(&ball1, &paddle1) == 1) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballpaddle, 0);
						}
				
						while(SDL_PollEvent(&event)) {
					
							//If the quit icon is clicked
							if(event.type == SDL_QUIT) {
								isRunning = 0;
								break;
							}
					
							if(event.type != SDL_KEYDOWN) {
								break;
							}
							SDL_Keycode keys = event.key.keysym.sym;
					
							switch(keys) {
								case SDLK_ESCAPE:
									le2 = menu();
									
									if(le2 == 1) {
										goto LOOP2;
									}
									
									if(le2 == 2) {
										level = 1;
										goto LOOP1;
									}
									
									if(le2 == 3) {
										level = 2;
										goto LOOP1;
									}
									
									if(le2 == 4) {
										level = 3;
										goto LOOP1;
									}
									
									if(le2 == 5) {
										level = 4;
										goto LOOP1;
									}
									
									if(le2 == 6) {
										isRunning = 0;
									}
									
									break;
						
								case SDLK_LEFT:
									if(paddle1.place.x < 5) {
										break;
									}
									else{
										paddle1.place.x = paddle1.place.x - 20;
									}
									break;
						
								case SDLK_RIGHT:
									if(paddle1.place.x + paddle1.place.w + 5 > SCREEN_W) {
										break;
									}
									paddle1.place.x = paddle1.place.x + 20;
									break;

								case SDLK_a:
									if(paddle1.place.x < 5) {
										break;
									}
									else {
										paddle1.place.x = paddle1.place.x - 20;
									}
									break;

								case SDLK_d:
									if(paddle1.place.x + paddle1.place.w + 5 > SCREEN_W) {
										break;
									}
									else {
										paddle1.place.x = paddle1.place.x + 20;
									}
									break;

								default:
									break;
							}
						}
			
						//Clearing renderer
						SDL_RenderClear(rend);
				
						//Copying Each Texture On Renderer
						SDL_RenderCopy(rend, tex, NULL, NULL);
						SDL_RenderCopy(rend, tex1, NULL, &paddle1.place);
						SDL_RenderCopy(rend, tex2, NULL, &ball1.place);
						for(k = 0; k < NUMBRICKS; k++) {
							if(bricks1.alive[k] == 1) {
								SDL_RenderCopy(rend, tex3, NULL, &bricks1.bplace[k]);
							}
							else if(bricks2.alive[k] == 1) {
								SDL_RenderCopy(rend, tex4, NULL, &bricks2.bplace[k]);
							}
						}
				
						//Setting the Render as present
						SDL_RenderPresent(rend);
					}
					break;
				case 3:
					//Defining Brick Alive Condition
					for(j = 0; j < NUMBRICKS; j++) {
						bricks1.alive[j] = 1;
					}
					
					//Defining Ball Count for ball challenge
					int ballcount1 = 1;
					int ballcount2 = 1;
					
					ball1.place.x = 160;
					ball1.place.y = 400;
					ball1.place.w = BALL_W;
					ball1.place.h = BALL_H;
					
					LOOP3:
					count = 0;
					
					//Main Game Loop
					while(isRunning) {
						//Event Handling
						SDL_Event event;
				
						//if all bricks1 are removed
						if(count == NUMBRICKS) {
							SDL_RenderClear(rend);
							SDL_RenderCopy(rend, tex7, NULL, &youwin.place);
							SDL_RenderPresent(rend);
							Mix_PlayChannel(-1, youwins, 0);
							SDL_Delay(2000);
							SDL_RenderClear(rend);
							goto LOOPN;
						}
				
						//Defining Ball1 Velocity_X
						ball1.place.x = ball1.place.x + ball1.x_vel;
				
						for(l = 0; l < NUMBRICKS; l++) {
							if(bricks1.alive[l] == 1) {
								if(collision1(&ball1, &bricks1.bplace[l]) == 1) {
									bricks1.alive[l] = 0;
									ball1.x_vel = - ball1.x_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
						
						//Defining Ball1 Velocity_Y
						ball1.place.y = ball1.place.y + ball1.y_vel;
				
						for(m = 0; m < NUMBRICKS; m++) {
							if(bricks1.alive[m] == 1) {
								if(collision1(&ball1, &bricks1.bplace[m]) == 1) {
									bricks1.alive[m] = 0;
									ball1.y_vel = - ball1.y_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
						
						//Defining Ball2 Velocity_X
						ball2.place.x = ball2.place.x + ball2.x_vel;
				
						for(l = 0; l < NUMBRICKS; l++) {
							if(bricks1.alive[l] == 1) {
								if(collision1(&ball2, &bricks1.bplace[l]) == 1) {
									bricks1.alive[l] = 0;
									ball2.x_vel = - ball2.x_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
						
						//Defining Ball2 Velocity_Y
						ball2.place.y = ball2.place.y + ball2.y_vel;
				
						for(m = 0; m < NUMBRICKS; m++) {
							if(bricks1.alive[m] == 1) {
								if(collision1(&ball2, &bricks1.bplace[m]) == 1) {
									bricks1.alive[m] = 0;
									ball2.y_vel = - ball2.y_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
						
						//Collision of ball1 with the left wall
						if(ball1.place.x < 0) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
						
												
						//Collision of ball2 with the left wall
						if(ball2.place.x < 0) {
							ball2.x_vel = - ball2.x_vel;
						}
												
						//Collision of ball1 with the upper wall
						if(ball1.place.y < 0) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
						
						//Collision of ball2 with the upper wall
						if(ball2.place.y < 0) {
							ball2.y_vel = - ball2.y_vel;
						}
						
						//Collision of the ball1 with the right wall
						if(ball1.place.x + ball1.place.w + 0 > SCREEN_W) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
						
										
						//Collision of the ball2 with the right wall
						if(ball2.place.x + ball2.place.w + 0 > SCREEN_W) {
							ball2.x_vel = - ball2.x_vel;
						}
						
						//Collision of the ball1 with the lower wall
						if(ball1.place.y + ball1.place.h > SCREEN_H) {
							if(ballcount1 == 1 && ballcount2 == 0) {
								for(n = 0; n < NUMBRICKS; n++) {
									bricks1.alive[n] = 1;
								}
								ballcount1 = 1;
								ballcount2 = 1;
								ball1.place.x = 160;
								ball1.place.y = 400;
								ball1.x_vel = 3;
								ball1.y_vel = - 3;
								ball2.place.x = SCREEN_W - 160;
								ball2.place.y = 400;
								ball2.x_vel = - 2;
								ball2.y_vel = - 2;
								count = 0;
							}
							else if(ballcount1 == 1 && ballcount2 == 1) {
								ballcount1 = 0;
							}
						}
				
						//Collision of the ball2 with the lower wall
						if(ball2.place.y + ball2.place.h > SCREEN_H) {
							if(ballcount1 == 0 && ballcount2 == 1) {
								for(n = 0; n < NUMBRICKS; n++) {
									bricks1.alive[n] = 1;
								}
								ballcount1 = 1;
								ballcount2 = 1;
								ball1.place.x = 160;
								ball1.place.y = 400;
								ball1.x_vel = 3;
								ball1.y_vel = - 3;
								ball2.place.x = SCREEN_W - 160;
								ball2.place.y = 400;
								ball2.x_vel = - 2;
								ball2.y_vel = - 2;
								count = 0;
							}
							else if(ballcount1 == 1 && ballcount2 == 1) {
								ballcount2 = 0;
							}
						}
						
						//Collision of the ball1 with paddle1
						if(collision(&ball1, &paddle1) == 1) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballpaddle, 0);
						}
						
						//Collision of the ball2 with paddle1
						if(collision(&ball2, &paddle1) == 1) {
							ball2.y_vel = - ball2.y_vel;
							Mix_PlayChannel(-1, ballpaddle, 0);
						}
				
						while(SDL_PollEvent(&event)) {
					
							//If the quit icon is clicked
							if(event.type == SDL_QUIT) {
								isRunning = 0;
								break;
							}
					
							if(event.type != SDL_KEYDOWN) {
								break;
							}
							SDL_Keycode keys = event.key.keysym.sym;
					
							switch(keys) {
								case SDLK_ESCAPE:
									le3 = menu();
									
									if(le3 == 1) {
										goto LOOP3;
									}
									
									if(le3 == 2) {
										level = 1;
										goto LOOP1;
									}
									
									if(le3 == 3) {
										level = 2;
										goto LOOP1;
									}
									
									if(le3 == 4) {
										level = 3;
										goto LOOP1;
									}
									
									if(le3 == 5) {
										level = 4;
										goto LOOP1;
									}
									
									if(le3 == 6) {
										isRunning = 0;
									}
									
									break;
						
								case SDLK_LEFT:
									if(paddle1.place.x < 5) {
										break;
									}
									else{
										paddle1.place.x = paddle1.place.x - 20;
									}
									break;
						
								case SDLK_RIGHT:
									if(paddle1.place.x + paddle1.place.w + 5 > SCREEN_W) {
										break;
									}
									paddle1.place.x = paddle1.place.x + 20;
									break;

								case SDLK_a:
									if(paddle1.place.x < 5) {
										break;
									}
									else {
										paddle1.place.x = paddle1.place.x - 20;
									}
									break;

								case SDLK_d:
									if(paddle1.place.x + paddle1.place.w + 5 > SCREEN_W) {
										break;
									}
									else {
										paddle1.place.x = paddle1.place.x + 20;
									}
									break;

								default:
									break;
							}
						}
			
						//Clearing renderer
						SDL_RenderClear(rend);
				
						//Copying Each Texture On Renderer
						SDL_RenderCopy(rend, tex, NULL, NULL);
						SDL_RenderCopy(rend, tex1, NULL, &paddle1.place);
						if(ballcount1 == 1) {
							SDL_RenderCopy(rend, tex2, NULL, &ball1.place);
						}
						if(ballcount2 == 1) {
							SDL_RenderCopy(rend, tex5, NULL, &ball2.place);
						}
						for(k = 0; k < NUMBRICKS; k++) {
							if(bricks1.alive[k] == 1) {
								SDL_RenderCopy(rend, tex3, NULL, &bricks1.bplace[k]);
							}
						}
									
						//Setting the Render as present
						SDL_RenderPresent(rend);
					}
					break;
				case 4:
					//Defining Brick Alive Condition
					for(j = 0; j < NUMBRICKS; j++) {
						bricks1.alive[j] = 1;
					}
						
					ball1.place.x = 160;
					ball1.place.y = 400;
					ball1.place.w = BALL_W;
					ball1.place.h = BALL_H;
					
					LOOP4:
					count = 0;
					
					//Main Game Loop
					while(isRunning) {
						
						//Event Handling
						SDL_Event event;
				
						//if all bricks1 are removed
						if(count == NUMBRICKS) {
							SDL_RenderClear(rend);
							SDL_RenderCopy(rend, tex7, NULL, &youwin.place);
							SDL_RenderPresent(rend);
							Mix_PlayChannel(-1, youwins, 0);
							SDL_Delay(2000);
							SDL_RenderClear(rend);
							goto LOOPN;
						}
						
						//Defining Ball1 Velocity_X
						ball1.place.x = ball1.place.x + ball1.x_vel;
				
						for(l = 0; l < NUMBRICKS; l++) {
							if(bricks1.alive[l] == 1) {
								if(collision1(&ball1, &bricks1.bplace[l]) == 1) {
									bricks1.alive[l] = 0;
									ball1.x_vel = - ball1.x_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
				
						//Defining Ball1 Velocity_Y
						ball1.place.y = ball1.place.y + ball1.y_vel;
				
						for(m = 0; m < NUMBRICKS; m++) {
							if(bricks1.alive[m] == 1) {
								if(collision1(&ball1, &bricks1.bplace[m]) == 1) {
									bricks1.alive[m] = 0;
									ball1.y_vel = - ball1.y_vel;
									Mix_PlayChannel(-1, ballbrick, 0);
									count++;
								}
							}
						}
				
						//Collision of ball1 with the left wall
						if(ball1.place.x < 0) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of ball1 with the upper wall
						if(ball1.place.y < 0) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of the ball1 with the right wall
						if(ball1.place.x + ball1.place.w + 0 > SCREEN_W) {
							ball1.x_vel = - ball1.x_vel;
							Mix_PlayChannel(-1, ballwall, 0);
						}
				
						//Collision of the ball1 with the lower wall
						if(ball1.place.y + ball1.place.h > SCREEN_H) {
							ball1.y_vel = - ball1.y_vel;
							for(n = 0; n < NUMBRICKS; n++) {
								bricks1.alive[n] = 1;
							}
							ball1.place.x = 160;
							ball1.place.y = 400;
							ball1.x_vel = 3;
							ball1.y_vel = - 3;
							count = 0;
						}
				
						//Collision of the ball1 with paddle2
						if(collision(&ball1, &paddle2) == 1) {
							ball1.y_vel = - ball1.y_vel;
							Mix_PlayChannel(-1, ballpaddle, 0);
						}
				
						while(SDL_PollEvent(&event)) {
					
							//If the quit icon is clicked
							if(event.type == SDL_QUIT) {
								isRunning = 0;
								break;
							}
					
							if(event.type != SDL_KEYDOWN) {
								break;
							}
							SDL_Keycode keys = event.key.keysym.sym;
					
							switch(keys) {
								case SDLK_ESCAPE:
									le4 = menu();
									
									if(le4 == 1) {
										goto LOOP4;
									}
									
									if(le4 == 2) {
										level = 1;
										goto LOOP1;
									}
									
									if(le4 == 3) {
										level = 2;
										goto LOOP1;
									}
									
									if(le4 == 4) {
										level = 3;
										goto LOOP1;
									}
									
									if(le4 == 5) {
										level = 4;
										goto LOOP1;
									}
									
									if(le4 == 6) {
										isRunning = 0;
									}
									
									break;
						
								case SDLK_LEFT:
									if(paddle2.place.x < 5) {
										break;
									}
									else{
										paddle2.place.x = paddle2.place.x - 8;
									}
									break;
						
								case SDLK_RIGHT:
									if(paddle2.place.x + paddle2.place.w + 5 > SCREEN_W) {
										break;
									}
									paddle2.place.x = paddle2.place.x + 8;
									break;

								case SDLK_a:
									if(paddle2.place.x < 5) {
										break;
									}
									else {
										paddle2.place.x = paddle2.place.x - 8;
									}
									break;

								case SDLK_d:
									if(paddle2.place.x + paddle2.place.w + 5 > SCREEN_W) {
										break;
									}
									else {
										paddle2.place.x = paddle2.place.x + 8;
									}
									break;

								default:
									break;
							}
						}
			
						//Clearing renderer
						SDL_RenderClear(rend);
				
						//Copying Each Texture On Renderer
						SDL_RenderCopy(rend, tex, NULL, NULL);
						SDL_RenderCopy(rend, tex6, NULL, &paddle2.place);
						SDL_RenderCopy(rend, tex2, NULL, &ball1.place);
						for(k = 0; k < NUMBRICKS; k++) {
							if(bricks1.alive[k] == 1) {
								SDL_RenderCopy(rend, tex3, NULL, &bricks1.bplace[k]);
							}
						}
				
						//Setting the Render as present
						SDL_RenderPresent(rend);
					}
					break;
				
				default :
					break;
			}
			SDL_Quit();
		}
	}
	return 0;
}

int collision(body *a, body *b) {
	int ball_x = a->place.x;
	int ball_y = a->place.y;
	int ball_w = a->place.w;
	int ball_h = a->place.h;
	int ball_v = a->y_vel;
	
	int paddle_x = b->place.x;
	int paddle_y = b->place.y;
	int paddle_w = b->place.w;
	int paddle_h = b->place.h;
	
	if((ball_v > 0) && (ball_y + ball_h >= paddle_y) && (ball_y + ball_h <= paddle_y + paddle_h)) {
		if((ball_x <= paddle_x + paddle_w) && (ball_x + ball_w >= paddle_x)) {
			return 1;
		}
	}
	return 0;
}

int collision1(body *a, SDL_Rect *rects) {
	int ball_x = a->place.x;
	int ball_y = a->place.y;
	int ball_w = a->place.w;
	int ball_h = a->place.h;
	
	int brick_x = rects->x;
	int brick_y = rects->y;
	int brick_w = rects->w;
	int brick_h = rects->h;

	if(ball_y + ball_h < brick_y) {
		return 0;
	}
	else if(ball_y > brick_y + brick_h) {
		return 0;
	}
	else if(ball_x + ball_w < brick_x) {
		return 0;
	}
	else if(ball_x > brick_x + brick_w) {
		return 0;
	}
	else {
		return 1;
	}
}

int menu() {
	int a, b, m, n;
	
	char *head[MAXMENU];
	
	head[0] = "PLAY/RESUME";
	head[1] = "CHALLENGE";
	head[2] = "BRICK CHALLENGE";
	head[3] = "BALL CHALLENGE";
	head[4] = "PADDLE CHALLENGE";
	head[5] = "QUIT";
	
	SDL_Surface* display[MAXMENU];
	SDL_Texture* displayTexture[MAXMENU];
	
	int selected[MAXMENU];
	
	for(a = 0; a < MAXMENU; a++) {
		selected[a] = 0;
	}
	
	//Declaring Colors For Furthur Use White & Pink
	SDL_Color white = {255, 255, 255, 1}; 
	SDL_Color pink = {255, 0, 255, 1};
	
	TTF_Font *fonts;
	fonts = TTF_OpenFont("Resources/allianz.ttf", 80);
	if( fonts == NULL ) { 
		printf("Failed to load font SDL_TTF Error : %s\n", TTF_GetError());
		return 1;
	}
	
	//Loading Music & Playing at the Starting Of the Game and menu window
	Mix_Chunk *start = Mix_LoadWAV("Resources/start.wav");
	Mix_PlayChannel(-1, start, 0);
	
	SDL_Surface* displayback;
	SDL_Texture* displaybackground;
	
	displayback = IMG_Load("Resources/menubackground.jpeg");
	
	if(displayback == NULL) {
		printf("menubackground.jpg can't be loaded, Error: %s\n", SDL_GetError());
	}
	
  	displaybackground = SDL_CreateTextureFromSurface(rend, displayback);
	
	if(displaybackground == NULL) {
		printf("Texture not loaded on menubackground.jpg . Error: %s\n", SDL_GetError());
	}
	
	SDL_FreeSurface(displayback);
	
	display[0] = TTF_RenderText_Blended(fonts, head[0], white);
	
	if(display[0] == NULL) {
		printf("Display Option 1 Can't be Loaded. Text Rendering Error: %s\n", TTF_GetError());
	}
	
	displayTexture[0] = SDL_CreateTextureFromSurface(rend, display[0]);
	
	if(displayTexture[0] == NULL) {
		printf("Create Texture from display Surface Failed, Option 1. Error: %s\n", SDL_GetError());
	}
	
	display[1] = TTF_RenderText_Blended(fonts, head[1], white);
	
	if(display[1] == NULL) {
		printf("Display Option 2 Can't be Loaded. Text Rendering Error: %s\n", TTF_GetError());
	}
	
	displayTexture[1] = SDL_CreateTextureFromSurface(rend, display[1]);
	
	if(displayTexture[1] == NULL) {
		printf("Create Texture from display Surface Failed, Option 2. Error: %s\n", SDL_GetError());
	}

	display[2] = TTF_RenderText_Blended(fonts, head[2], white);
	
	if(display[2] == NULL) {
		printf("Display Option 3 Can't be Loaded. Text Rendering Error: %s\n", TTF_GetError());
	}
	
	displayTexture[2] = SDL_CreateTextureFromSurface(rend, display[2]);
	
	if(displayTexture[2] == NULL) {
		printf("Create Texture from display Surface Failed, Option 3. Error: %s\n", SDL_GetError());
	}
	
	display[3] = TTF_RenderText_Blended(fonts, head[3], white);
	
	if(display[3] == NULL) {
		printf("Display Option 4 Can't be Loaded. Text Rendering Error: %s\n", TTF_GetError());
	}
	
	displayTexture[3] = SDL_CreateTextureFromSurface(rend, display[3]);
	
	if(displayTexture[3] == NULL) {
		printf("Create Texture from display Surface Failed, Option 4. Error: %s\n", SDL_GetError());
	}
	
	display[4] = TTF_RenderText_Blended(fonts, head[4], white);
	
	if(display[4] == NULL) {
		printf("Display Option 5 Can't be Loaded. Text Rendering Error: %s\n", TTF_GetError());
	}
	
	displayTexture[4] = SDL_CreateTextureFromSurface(rend, display[4]);
	
	if(displayTexture[4] == NULL) {
		printf("Create Texture from display Surface Failed, Option 5. Error: %s\n", SDL_GetError());
	}
	
	display[5] = TTF_RenderText_Blended(fonts, head[5], white);
	
	if(display[5] == NULL) {
		printf("Display Option 5 Can't be Loaded. Text Rendering Error: %s\n", TTF_GetError());
	}
	
	displayTexture[5] = SDL_CreateTextureFromSurface(rend, display[5]);
	
	if(displayTexture[5] == NULL) {
		printf("Create Texture from display Surface Failed, Option 5. Error: %s\n", SDL_GetError());
	}
	
	SDL_Rect position[MAXMENU];

	position[0].x = SCREEN_W / 2 - 90;
	position[0].y = 100;
	position[0].w = 180;
	position[0].h = 30;

	position[1].x = SCREEN_W / 2 - 80;
	position[1].y = 150;
	position[1].w = 160;
	position[1].h = 30;

	position[2].x = SCREEN_W / 2 - 120;
	position[2].y = 200;
	position[2].w = 240;
	position[2].h = 30;

	position[3].x = SCREEN_W / 2 - 120;
	position[3].y = 250;
	position[3].w = 240;
	position[3].h = 30;

	position[4].x = SCREEN_W / 2 - 120;
	position[4].y = 300;
	position[4].w = 240;
	position[4].h = 30;

	position[5].x = SCREEN_W / 2 - 40;
	position[5].y = 350;
	position[5].w = 80;
	position[5].h = 30;
	
	SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear"); 
	
	SDL_RenderSetLogicalSize(rend, 640, 480);

	SDL_Event event;
	while(1) {
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_QUIT:
					return 6;
					break;
				
				case SDL_KEYDOWN:
					if(event.key.keysym.sym == SDLK_ESCAPE) {
						return 6;
					}
					break;
				
				case SDL_MOUSEMOTION:
					m= event.motion.x;
					n = event.motion.y;
					for(b = 0; b < MAXMENU; b++) {
						if(m >= position[b].x && m <= position[b].x + position[b].w && n >= position[b].y && n <= position[b].y + position[b].h) {
							if(!selected[b]) {
								selected[b] = 1;
								display[b] = TTF_RenderText_Solid(fonts, head[b], pink);
								displayTexture[b] = SDL_CreateTextureFromSurface(rend, display[b]);
								SDL_FreeSurface(display[b]);
							}
						}
						else {
							selected[b] = 0;
							display[b] = TTF_RenderText_Solid(fonts, head[b], white);
							displayTexture[b] = SDL_CreateTextureFromSurface(rend, display[b]);
							SDL_FreeSurface(display[b]);		
 						}
					}
					break;

				case SDL_MOUSEBUTTONDOWN:
					m = event.button.x;
					n = event.button.y;
   					
   					if(m >= position[0].x && m <= position[0].x + position[0].w && n >= position[0].y && n <= position[0].y + position[0].h) {	
						return 1;
					}
					
					if(m >= position[1].x && m <= position[1].x + position[1].w && n >= position[1].y && n <= position[1].y + position[1].h) {
						return 2;
					}
					
					if(m >= position[2].x && m <= position[2].x + position[2].w && n >= position[2].y && n <= position[2].y + position[2].h){
						return 3;
					}
					
					if(m >= position[3].x && m <= position[3].x + position[3].w && n >= position[3].y && n <= position[3].y + position[3].h) {
						return 4;
					}
					
					if(m >= position[4].x && m <= position[4].x + position[4].w && n >= position[4].y && n <= position[4].y + position[4].h) {
						return 5;
					}
					
					if(m >= position[5].x && m <= position[5].x + position[5].w && n >= position[5].y && n <= position[5].y + position[5].h) {
						return 6;
					}			
					break;
			}
		}
		
		SDL_RenderClear(rend);
		
		SDL_RenderCopy(rend, displaybackground, NULL, NULL);
		SDL_RenderCopy(rend, displayTexture[0], NULL, &position[0]);
		SDL_RenderCopy(rend, displayTexture[1], NULL, &position[1]);
		SDL_RenderCopy(rend, displayTexture[2], NULL, &position[2]);
		SDL_RenderCopy(rend, displayTexture[3], NULL, &position[3]);
		SDL_RenderCopy(rend, displayTexture[4], NULL, &position[4]);
		SDL_RenderCopy(rend, displayTexture[5], NULL, &position[5]);
				
		SDL_RenderPresent(rend);
	}
}
