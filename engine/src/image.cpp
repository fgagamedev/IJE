#include "image.h"

Image::Image()
	: m_texture(nullptr), m_w(0), m_h(0)
{
}

Image::~Image()
{
}

SDL_Texture * 
Image::texture() const
{
	return m_texture;
}

int
Image::w() const
{
	return m_w;
}

int
Image::h() const
{
	return m_h;
}

void 
Image::load_texture(SDL_Renderer *renderer, string path) throw (Exception)
{
	m_texture = IMG_LoadTexture(renderer, path.c_str());

	if(m_texture == nullptr)
	{
		throw Exception(SDL_GetError());
	}

	int rc = SDL_QueryTexture(m_texture, nullptr, nullptr, &m_w, &m_h);

	if (rc)
	{
		throw Exception(SDL_GetError());
	}
}
