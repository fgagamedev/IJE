/*
 * Classe que representa um arquivo de musica.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef MUSIC_H
#define MUSIC_H

#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include "core/exception.h"

using std::string;
using std::unique_ptr;

class Music
{
public:
	explicit Music(Mix_Music* const music);
	~Music();

	Mix_Music * mix_music() const;
	string path() const;

    static Music * from_file(const string& path) throw (Exception);

private:
	class Impl;
	unique_ptr<Impl> m_impl;
};

#endif
