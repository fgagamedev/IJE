#include "font.h"

Font_Manager*
Font_Manager::instance = NULL;

Font_Manager*
Font_Manager::Instance()
{
    if (not instance)
    {
        instance = new Font_Manager;
        init();
    }

    return instance;
}


Font_Manager::Font_Manager()
{
}

void
Font_Manager::init() throw (Exception)
{
    int rc = TTF_Init();

    if (rc < 0)
    {
        throw Exception(SDL_GetError());
    }
}

Font_Manager::~Font_Manager()
{
    delete instance;
    TTF_Quit();
}

void
Font_Manager::load_font( string path, unsigned int font_size) throw (Exception)
{
    m_font = TTF_OpenFont(path.c_str(), font_size);

    if (m_font == nullptr)
    {
        throw Exception(TTF_GetError());
    }
}

void
Font_Manager::close_font()
{
    TTF_CloseFont(m_font);
    m_font = NULL;
}


void
Font_Manager::make_message(SDL_Renderer *renderer, string message, Color color) throw (Exception)
{
    SDL_Surface* surfaceMessage = nullptr;
    SDL_Color m_color = {color.r(), color.g(), color.b(), color.a()};
    surfaceMessage = TTF_RenderText_Solid(m_font, message.c_str(), m_color);

    if (surfaceMessage == nullptr)
    {
        throw Exception(TTF_GetError());
    }

    m_message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    if (m_message == nullptr)
    {
        throw Exception(TTF_GetError());
    }
}

SDL_Texture*
Font_Manager::message() const
{
    return m_message;
}
