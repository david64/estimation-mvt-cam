

/* enregistrer_image.c */
/* permet d'enregistrer une image au format BMP à l'aide de la SDL */


#include <SDL/SDL.h>
#include "params_mvt.h"


// definirPixel : permet de modifier la couleur d'un pixel dans une SDL_Surface
void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel) {

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

// Enregistre l'image stockee dans f, au format BMP, dans filename
void enregistrer_image(int** f, char* filename, taille t) {

	SDL_Surface *sdl_img;

	sdl_img = SDL_CreateRGBSurface(0, t.l, t.h, 32, 0,0,0,0);

	int i,j;

	for(i=0; i<t.h; i++) {
		for(j=0; j<t.l; j++) {
            
            Uint32 pixel;
			Uint8 r,g,b,a;
			r = f[i][j];
			g = f[i][j];
			b = f[i][j];
			a = 255;
			pixel = SDL_MapRGBA(sdl_img->format, r, g, b, a);
			definirPixel(sdl_img,j,i,pixel);
		}
	}

	SDL_SaveBMP(sdl_img, filename);
	SDL_FreeSurface(sdl_img);

}

