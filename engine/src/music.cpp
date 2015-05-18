/*
 * Implementação da classe Music.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/music.h"

class Music::Impl
{
public:
	Impl(Mix_Music* const music)
		: m_mix_music{music}
	{
	}

	~Impl()
	{
		if(m_mix_music != nullptr) {
			Mix_FreeMusic(m_mix_music);
		}
	}

	Mix_Music * mix_music() const { return m_mix_music; };

private:
	Mix_Music* const m_mix_music;
};

Music::Music(Mix_Music* const music)
	: m_impl{new Impl(music)}
{
}

Music::~Music()
{
}

Mix_Music*
Music::mix_music() const
{
	return m_impl->mix_music();
}

Music *
Music::from_file(const string& path) throw (Exception)
{
    Mix_Music *music = Mix_LoadMUS(path.c_str());

    if (music == nullptr)
    {
        throw Exception(Mix_GetError());
    }

    Music *m = new Music(music);

    if (not m)
    {
        throw Exception("Out of memory for a new Music");
    }

    return m;
}
