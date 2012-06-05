

/* save_image.c */
// Use the SDL to save an image


#include <SDL/SDL.h>
#include "motion_params.h"


// define_px : change the color of a pixel in an SDL_Surface
void define_px(SDL_Surface *surface, int x, int y, Uint32 pixel) {

    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *) surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else {
            
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

// Save the image stored in f in filename
void save_image(int** f, char* filename, size s) {

	SDL_Surface *sdl_img;

	sdl_img = SDL_CreateRGBSurface(0, s.w, s.h, 32, 0,0,0,0);

	int i,j;

	for(i=0; i<s.h; i++) {
		for(j=0; j<s.w; j++) {
            
            Uint32 pixel;
			Uint8 r,g,b,a;
			r = f[i][j];
			g = f[i][j];
			b = f[i][j];
			a = 255;
			pixel = SDL_MapRGBA(sdl_img->format, r, g, b, a);
			define_px(sdl_img,j,i,pixel);
		}
	}

	SDL_SaveBMP(sdl_img, filename);
	SDL_FreeSurface(sdl_img);

}

