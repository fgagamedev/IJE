#ifndef FONT_H
#define FONT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "exception.h"
#include "color.h"

using std::string;

class Font_Manager
{
public:
	static Font_Manager * Instance();
	static void init() throw (Exception);
	void load_font(string path, unsigned int font_size) throw (Exception);
	void close_font();
	
	SDL_Texture* message()const ;
	void make_message(SDL_Renderer * renderer, string message, Color color) throw (Exception); 

protected:
	Font_Manager();
	~Font_Manager();

private:
    static Font_Manager * instance;
	SDL_Texture* m_message;
	TTF_Font    * m_font;
};

#endif
