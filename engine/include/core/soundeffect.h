/*
 * Classe que representa um arquivo de efeito sonoro.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SOUNDEFFECT_H
#define SOUNDEFFECT_H

#include <string>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include "core/exception.h"

using std::string;
using std::unique_ptr;

class SoundEffect
{
public:
	explicit SoundEffect(Mix_Chunk* const soundeffect);
	~SoundEffect();

	Mix_Chunk* mix_chunk() const;
	int channel() const;
	void set_channel(const int channel);

    static SoundEffect * from_file(const string& path) throw (Exception);

private:
	class Impl;
	unique_ptr<Impl> m_impl;
};

#endif
