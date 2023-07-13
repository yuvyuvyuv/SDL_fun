/*This source code copyrighted by Lazy Foo' Productions 2004-2023
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>

double XL = -2.00;
double XH = 2;

double YL = -1.12;
double YH = 1.12;



double xl = -2.00;
double xh = 0.47;

double yl = -1.12;
double yh = 1.12;

const int max_iter = 100;
int mand(double x0, double y0){
	int iter = 0;
	double max_bound = 4.0;
	double temp,x=0.0,y=0.0;
	while(x * x + y * y <= max_bound && iter < max_iter){
		temp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = temp;
		iter++;
	}
	return iter;

}

//Screen dimension constants
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;


void draw(SDL_Renderer* renderer){
	double x,y,c;
			
	for (int i = 0; i < SCREEN_WIDTH; i++){
		for(int j = 0; j < SCREEN_HEIGHT; j++){
			x = ((double)i / (double)SCREEN_WIDTH) * (xh - xl) + xl;
			y = ((double)j / (double)SCREEN_HEIGHT) * (yh - yl) + yl;
			
			c  = 256*(double)mand(x,y)/(double)max_iter;
			
			SDL_SetRenderDrawColor(renderer, c,c,c, 255);
			SDL_RenderDrawPoint(renderer,i,j);
		}
	}	
	SDL_RenderPresent(renderer);

	return;
}
int main( int argc, char* args[] )
{

	//renderer
    SDL_Renderer *renderer;

	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		//SDL_CreateWindowAndRenderer(SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN,&window,&renderer);
		renderer=SDL_CreateRenderer(window,-1,0);
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

			//Fill the surface white
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
			
			//Update the surface
			SDL_UpdateWindowSurface( window );

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			
			double x,y,c;
			
			for (int i = 0; i < SCREEN_WIDTH; i++){
				for(int j = 0; j < SCREEN_HEIGHT; j++){
					x = ((double)i / (double)SCREEN_WIDTH) * (xh - xl) + xl;
					y = ((double)j / (double)SCREEN_HEIGHT) * (yh - yl) + yl;
					
					c  = 256*(double)mand(x,y)/(double)max_iter;
					
					SDL_SetRenderDrawColor(renderer, c,c,c, 255);
					SDL_RenderDrawPoint(renderer,i,j);
				}
			}	
			SDL_RenderPresent(renderer);

			double d = 0.1;
            //Hack to get window to stay up
            SDL_Event event; 
			bool quit = false; 
			while( quit == false ){
				while( SDL_PollEvent( &event ) ){
					if(event.type == SDL_KEYDOWN){
						switch(event.key.keysym.sym){
							case SDLK_w:
								xh*=1-d;
								xl*=1-d;
								yh*=1-d;
								yl*=1-d;
								d*=1.1;
								printf("+\n");
								break;
							case SDLK_s:
								xh*=1+d;
								xl*=1+d;
								yh*=1+d;
								yl*=1+d;
								d*=0.9;
								printf("-\n");
								break;
							case SDLK_UP:
								yh-=0.1;
								yl-=0.1;
								printf("^\n");
								break;
							case SDLK_DOWN:
								yh+=0.1;
								yl+=0.1;
								printf("\\\/\n");
								break;
							case SDLK_RIGHT:
								xh+=0.1;
								xl+=0.1;
								printf("->\n");
								break;
							case SDLK_LEFT:
								xh-=0.1;
								xl-=0.1;
								printf("<-\n");
								break;	
							case SDLK_0:
								xh=XH;
								xl=XL;
								yh=YH;
								yl=YL;
								printf("<-\n");
								break;							
						}
						draw(renderer);
					}

					
					if( event.type == SDL_QUIT ) 
						quit = true; 
				} 
			}
		}
	}

    SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
