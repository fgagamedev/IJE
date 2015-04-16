#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "exception.h"

using std::string;

class Image {
public:
	Image();
	~Image();

	int w() const;
    int h() const;
	void load_texture(SDL_Renderer *renderer, string path = "") throw (Exception);
	SDL_Texture * texture() const;

private:
	SDL_Texture *m_texture;
	int m_w, m_h;
};

#endif