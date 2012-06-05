

/* load_image.c */
/* Use the SDL to load an image */


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "motion_params.h"


// Get the value written in a pixel of a SDL surface (source : Site du zero)
Uint32 get_px(SDL_Surface *surface, int x, int y) {

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {

        case 1: return *p;

        case 2: return *(Uint16 *)p;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4: return *(Uint32 *)p;

        default: return 0; 
    }
}

// Get the size of an image
size image_size(char* file) {

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	SDL_Surface* sdl_img = IMG_Load(file);
	size s;
	s.w = sdl_img->w;
	s.h = sdl_img->h;
	SDL_FreeSurface(sdl_img);
    IMG_Quit();
	return s;  

}

// Load the "file" image in f
void load_image(int** f, char* file) {

	int i,j;

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    
    	// Use the SDL to load the image
	SDL_Surface* sdl_img;
	sdl_img = IMG_Load(file);

    IMG_Quit();
	
    	// Get the pixels (because we are only interested in grayscale, we can choose any colour, so for exemple let use the red pixels)
	for(i=0; i<sdl_img->h; i++) {
		for(j=0; j<sdl_img->w; j++) {
			
			Uint32 pixel;
			pixel = get_px(sdl_img,j,i);
			Uint8 r,g,b,a;
			SDL_GetRGBA(pixel, sdl_img->format, &r, &g, &b, &a);
			f[i][j] = (int) r;
		}
	}
	
	SDL_FreeSurface(sdl_img);
}

