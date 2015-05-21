/*
 * Classe que representa o sistema de audio.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>

using std::string;

static constexpr int k_infinite_loop = -1;

enum class AudioType
{
    Music,
    SoundEffect
};

template <AudioType type>
class AudioManager final
{
public:
    AudioManager();

    void play(const string& path, const int times);
    void set_volume(const int percent);
    void pause();
    void resume();
    void stop();
    void fade_out(const double seconds);
    bool faded_out();
};

using AudioManagerSfx = AudioManager<AudioType::SoundEffect>;
using AudioManagerMusic = AudioManager<AudioType::Music>;

#endif
