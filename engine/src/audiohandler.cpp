/*
 * Implementação da classe AudioHandler.
 *
 * Autor: Caio Nardelli
 * Data: 17/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/audiohandler.h"
#include <cassert>
#include <iostream>
#include <SDL2/SDL_mixer.h>
#include "core/music.h"
#include "core/soundeffect.h"
#include "core/environment.h"

using std::cout;
using std::endl;

namespace {

static constexpr auto k_all_channels = -1;
static constexpr auto k_any_channel = -1;

} // namespace

// ----------------------------------------------------------- //
//                       Music Handling
// ----------------------------------------------------------- //

template <>
void
AudioHandler<AudioType::Music>::play(const std::string& path, const int times)
{
	assert((times == k_infinite_loop || times >= 1) && "Must be k_infinite_loop or >= 1.");

	const auto music = Environment::get_instance()->resources_manager->get_music(path);
	assert(music != nullptr && "Shouldn't be playing null music.");

	const auto k_played_music = (Mix_PlayMusic(music->mix_music(), times) == 0);
	if(!k_played_music)
	{
		cout << "Couldn't play music (" << path << "). " << Mix_GetError() << endl;
	}
}

template <>
void
AudioHandler<AudioType::Music>::set_volume(const int percent)
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
AudioHandler<AudioType::Music>::pause()
{
	Mix_PauseMusic();
}

template <>
void
AudioHandler<AudioType::Music>::resume()
{
	Mix_ResumeMusic();
}

template <>
void
AudioHandler<AudioType::Music>::stop()
{
	Mix_HaltMusic();
}

template <>
void
AudioHandler<AudioType::Music>::fade_out(const double seconds)
{
	const auto k_milliseconds = static_cast<int>(seconds*1000);
	const auto k_faded = (Mix_FadeOutMusic(k_milliseconds) == 1);
	if(!k_faded)
	{
		cout << "Could not fade music. Probably no music playing/already faded." << endl;
	}
}

template <>
bool AudioHandler<AudioType::Music>::faded_out()
{
	const auto k_fading = (Mix_FadingMusic() == MIX_FADING_OUT);
	const auto k_playing = (Mix_PlayingMusic() == 1);
	return !k_fading && !k_playing;
}

// ----------------------------------------------------------- //
//                    Sound Effects Handling
// ----------------------------------------------------------- //

template <>
void
AudioHandler<AudioType::SoundEffect>::play(const std::string& path, const int times)
{
	assert((times == k_infinite_loop || times >= 1) && "Must be k_infinite_loop or >= 1.");

	const auto k_played_channel = Mix_PlayChannel(k_any_channel,
		Environment::get_instance()->resources_manager->get_soundeffect(path)->mix_chunk(),
		(times - 1));
	if(k_played_channel == -1)
	{
		cout << "Failed to play sound effect for any channel (" << k_played_channel <<
			"). " << Mix_GetError() << endl;
	}
}

template <>
void
AudioHandler<AudioType::SoundEffect>::set_volume(const int percent)
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
AudioHandler<AudioType::SoundEffect>::pause()
{
	Mix_Pause(k_all_channels);
}

template <>
void
AudioHandler<AudioType::SoundEffect>::resume()
{
	Mix_Resume(k_all_channels);
}

template <>
void
AudioHandler<AudioType::SoundEffect>::stop()
{
	Mix_HaltChannel(k_all_channels);
}

template <>
void
AudioHandler<AudioType::SoundEffect>::fade_out(const double seconds)
{
	const auto k_milliseconds = static_cast<int>(seconds*1000);
	Mix_FadeOutChannel(k_all_channels, k_milliseconds);
}

// template <>
// bool AudioHandler<AudioType::SoundEffect>::faded_out()
// {
// 	return false;
// }
