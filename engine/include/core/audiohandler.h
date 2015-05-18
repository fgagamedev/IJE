/*
 * Classe que representa o sistema de audio.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

#include <string>

using std::string;

static constexpr int k_infinite_loop = -1;

enum class AudioType
{
	Music,
	SoundEffect
};

template <AudioType type>
class AudioHandler final
{
public:
	static void play(const string& path, const int times);
	static void set_volume(const int percent);
	static void pause();
	static void resume();
	static void stop();
	static void fade_out(const double seconds);
	static bool faded_out();
};

using AudioSfx = AudioHandler<AudioType::SoundEffect>;
using AudioMusic = AudioHandler<AudioType::Music>;

#endif
