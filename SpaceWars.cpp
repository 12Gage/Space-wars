#include <iostream>
#include <stdio.h>
#include <string>
#include <stdint.h>
#include <sstream>

using namespace std;

#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";
#endif

#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <direct.h>
#define getcw _getcw

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <unistd.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/src/";
string audio_dir = currentWorkingDirectory + "/src/";

#endif

int main(){

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = NULL;

	SDL_Renderer *renderer = NULL;

	window = SDL_CreateWindow("Space wars",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1024, 768,
			SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool quit = false;

	SDL_Event e;

	SDL_GameControllerEventState(SDL_ENABLE);

	SDL_GameController* gGameController0 = NULL;

	gGameController0 = SDL_GameControllerOpen(0);

	SDL_Texture *bkgd = IMG_LoadTexture(renderer, (images_dir + "background.png").c_str());

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
