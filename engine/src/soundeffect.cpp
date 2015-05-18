/*
 * Implementação da classe AudioHandler.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/soundeffect.h"

class SoundEffect::Impl
{
public:
	Impl(Mix_Chunk* const soundeffect)
		: m_mix_chunk{soundeffect}, m_channel{-1}
	{
	}

	~Impl()
	{
		if(m_mix_chunk != nullptr) {
			Mix_FreeChunk(m_mix_chunk);
		}
	}

	Mix_Chunk * mix_chunk() const { return m_mix_chunk; }
	int channel() const { return m_channel; }
	void set_channel(const int channel) { m_channel = channel; }

private:
	Mix_Chunk* const m_mix_chunk;
	int m_channel;
};

SoundEffect::SoundEffect(Mix_Chunk* const soundeffect)
	: m_impl(new Impl(soundeffect))
{
}

SoundEffect::~SoundEffect()
{
}

Mix_Chunk*
SoundEffect::mix_chunk() const
{
	return m_impl->mix_chunk();
}

int
SoundEffect::channel() const
{
	return m_impl->channel();
}

void
SoundEffect::set_channel(const int channel)
{
	m_impl->set_channel(channel);
}

SoundEffect *
SoundEffect::from_file(const string& path) throw (Exception)
{
    Mix_Chunk *soundeffect = Mix_LoadWAV(path.c_str());

    if (soundeffect == nullptr)
    {
        throw Exception(Mix_GetError());
    }

    SoundEffect *sfx = new SoundEffect(soundeffect);

    if (not sfx)
    {
        throw Exception("Out of memory for a new SoundEffect");
    }

    return sfx;
}
