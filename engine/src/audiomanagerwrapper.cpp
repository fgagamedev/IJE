/*
 * Implementação da classe AudioManagerWrapper.
 *
 * Autor: Caio Nardelli
 * Data: 18/05/2015
 * Licença: LGPL. Sem copyright.
 */
#include "core/audiomanagerwrapper.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

using std::cout;
using std::endl;

AudioManagerWrapper::AudioManagerWrapper()
	: sfx_manager{nullptr}, music_manager{nullptr}
{
	open_audio();
}

AudioManagerWrapper::~AudioManagerWrapper()
{
	close_audio();
	delete music_manager;
	delete sfx_manager;
}

void
AudioManagerWrapper::init() throw (Exception)
{
    sfx_manager = new AudioManagerSfx();

    if (not sfx_manager)
    {
        throw Exception("Out of memory for a new AudioManagerSfx");
    }

    music_manager = new AudioManagerMusic();


    if (not music_manager)
    {
        throw Exception("Out of memory for a new AudioManagerMusic");
    }
}

AudioManagerSfx *
AudioManagerWrapper::sfx() const
{
	return sfx_manager;
}

AudioManagerMusic *
AudioManagerWrapper::music() const
{
	return music_manager;
}

void
AudioManagerWrapper::open_audio()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_AllocateChannels(4000);
}

void
AudioManagerWrapper::close_audio()
{
	// Query the specifications of the opened audio, to figure out how many times we need to
	// close the audio.
	int frequency = 0;
	int channels = 0;
	Uint16 format = 0;
	const int k_numbers_of_times_opened = Mix_QuerySpec(&frequency, &format, &channels);
	int times_to_close = k_numbers_of_times_opened;

	if(k_numbers_of_times_opened == 0) {
		cout << "Error querying the specifications of the audio. " << Mix_GetError() << endl;

		// Set the amount of times to close the audio to one, just for safety.
		times_to_close = 1;
	}

	// Close the audio the necessary amount of times.
	while(times_to_close > 0){
		Mix_CloseAudio();
		times_to_close--;
	}

	// "Since each call to Mix_Init may set different flags, there is no way, currently, to
	// request how many times each one was initted. In other words, the only way to quit for
	// sure is to do a loop like so: "
	while(Mix_Init(0)){
		Mix_Quit();
	}

	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}
