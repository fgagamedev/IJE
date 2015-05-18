/*
 * Implementação da classe AudioManager.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/audiomanager.h"
#include <cassert>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "core/music.h"
#include "core/soundeffect.h"
#include "core/environment.h"

using std::cout;
using std::endl;

namespace
{
static constexpr auto k_all_channels = -1;
static constexpr auto k_any_channel = -1;
} // namespace

// ----------------------------------------------------------- //
//                       Music Handling
// ----------------------------------------------------------- //
template<>
AudioManager<AudioType::Music>::AudioManager()
{
    SDL_InitSubSystem(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_AllocateChannels(4000);
}

template <>
void
AudioManager<AudioType::Music>::play(const string& path, const int times)
{
    assert((times == k_infinite_loop || times >= 1) && "Must be k_infinite_loop or >= 1.");

    const auto music = Environment::get_instance()->resources_manager->get_music(path);
    assert(music != nullptr && "Shouldn't be playing null music.");

    const auto k_played_music = (Mix_PlayMusic(music->mix_music(), times) == 0);
    if (not k_played_music)
    {
        cout << "Couldn't play music (" << path << "). " << Mix_GetError() << endl;
    }
}

template <>
void
AudioManager<AudioType::Music>::set_volume(const int percent)
{
    /// @todo Decide whether the <= 100 assertion is necessary.
    // No need to check for percent being above 100, SDL_Mixer already caps the volume to
    // MIX_MAX_VOLUME.
    assert(percent >= 0   && "Must be >= 0");
    assert(percent <= 100 && "Must be <= 100");

    const auto k_volume_value = percent * MIX_MAX_VOLUME/100;
    Mix_VolumeMusic(k_volume_value);
}

template <>
void
AudioManager<AudioType::Music>::pause()
{
    Mix_PauseMusic();
}

template <>
void
AudioManager<AudioType::Music>::resume()
{
    Mix_ResumeMusic();
}

template <>
void
AudioManager<AudioType::Music>::stop()
{
    Mix_HaltMusic();
}

template <>
void
AudioManager<AudioType::Music>::fade_out(const double seconds)
{
    const auto k_milliseconds = static_cast<int>(seconds*1000);
    const auto k_faded = (Mix_FadeOutMusic(k_milliseconds) == 1);
    if (not k_faded)
    {
        cout << "Could not fade music. Probably no music playing/already faded." << endl;
    }
}

template <>
bool AudioManager<AudioType::Music>::faded_out()
{
    const auto k_fading = (Mix_FadingMusic() == MIX_FADING_OUT);
    const auto k_playing = (Mix_PlayingMusic() == 1);

    return not k_fading and not k_playing;
}

// ----------------------------------------------------------- //
//                    Sound Effects Handling
// ----------------------------------------------------------- //
template<>
AudioManager<AudioType::SoundEffect>::AudioManager()
{
}

template <>
void
AudioManager<AudioType::SoundEffect>::play(const string& path, const int times)
{
    assert((times == k_infinite_loop || times >= 1) && "Must be k_infinite_loop or >= 1.");

    const auto sound_effect =
        Environment::get_instance()->resources_manager->get_sound_effect(path);

    assert(sound_effect != nullptr && "Shouldn't be playing a null sound effect.");

    const auto k_played_channel = Mix_PlayChannel(k_any_channel, sound_effect->mix_chunk(),
        (times - 1));
    if (k_played_channel == -1)
    {
        cout << "Failed to play sound effect for any channel (" << k_played_channel <<
            "). " << Mix_GetError() << endl;
    }
}

template <>
void
AudioManager<AudioType::SoundEffect>::set_volume(const int percent)
{
    /// @todo Decide whether the <= 100 assertion is necessary.
    // No need to check for percent being above 100, SDL_Mixer already caps the volume to
    // MIX_MAX_VOLUME.
    assert(percent >= 0   && "Must be >= 0");
    assert(percent <= 100 && "Must be <= 100");

    const auto k_volume_value = percent * MIX_MAX_VOLUME/100;
    Mix_Volume(k_all_channels, k_volume_value);
}

template <>
void
AudioManager<AudioType::SoundEffect>::pause()
{
    Mix_Pause(k_all_channels);
}

template <>
void
AudioManager<AudioType::SoundEffect>::resume()
{
    Mix_Resume(k_all_channels);
}

template <>
void
AudioManager<AudioType::SoundEffect>::stop()
{
    Mix_HaltChannel(k_all_channels);
}

template <>
void
AudioManager<AudioType::SoundEffect>::fade_out(const double seconds)
{
    const auto k_milliseconds = static_cast<int>(seconds*1000);
    Mix_FadeOutChannel(k_all_channels, k_milliseconds);
}

// template <>
// bool AudioManager<AudioType::SoundEffect>::faded_out()
// {
//     return false;
// }
