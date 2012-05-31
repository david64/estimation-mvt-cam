

/* charger_image.c */
/* Charger une image en utilisant la SDL */


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "params_mvt.h"


// Recupere la valeur d'un pixel d'une surface SDL (source : site du zero)
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y) {

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

// Donne la taille d'une image
taille taille_image(char* fichier) {

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	SDL_Surface* sdl_img = IMG_Load(fichier);
	taille t;
	t.l = sdl_img->w;
	t.h = sdl_img->h;
	SDL_FreeSurface(sdl_img);
    IMG_Quit();
	return t;  

}

// Charge l'image bmp contenue dans fichier dans f 
void charger_image(int** f, char* fichier) {

	int i,j;

    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    
	// Charger l'image à l'aide de la SDL
	SDL_Surface* sdl_img;
	sdl_img = IMG_Load(fichier);

    IMG_Quit();

	// Récupère les pixels (on ne prend que les pixels rouges (par exemple) car on 
	// traite des images en niveaux de gris
	for(i=0; i<sdl_img->h; i++) {
		for(j=0; j<sdl_img->w; j++) {
			
			Uint32 pixel;
			pixel = obtenirPixel(sdl_img,j,i);
			Uint8 r,g,b,a;
			SDL_GetRGBA(pixel, sdl_img->format, &r, &g, &b, &a);
			f[i][j] = (int) r;
		}
	}
	
	SDL_FreeSurface(sdl_img);
}

