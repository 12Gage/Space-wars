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
string images_dir = currentWorkingDirectory + "/Space-wars/";
string audio_dir = currentWorkingDirectory + "/Space-wars/";
#endif

#if defined(_WIN32) || (_WIN64)

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_mixer.h"
#include <direct.h>
#define getcwd _getcwd

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Space-wars/";
string audio_dir = currentWorkingDirectory + "/Space-wars/";

#endif

#if defined(__linux__)

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <unistd.h>

string currentWorkingDirectory(getcwd(NULL, 0));
string images_dir = currentWorkingDirectory + "/Space-wars/";
string audio_dir = currentWorkingDirectory + "/Space-wars/";

#endif

#include "player.h"

float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

SDL_Rect playerPos;

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

	Ship Ship1 = Ship(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 50.0,50.0);

	SDL_Texture *bkgd = IMG_LoadTexture(renderer, (images_dir + "background.png").c_str());

	SDL_Rect bkgdRect;

	bkgdRect.x = 0;

	bkgdRect.y = 0;

	bkgdRect.w = 1024;

	bkgdRect.h = 768;

	playerPos.x = 10;
	playerPos.y = 10;

	while(!quit)
	{
		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime - lastTime)/1000;
		lastTime = thisTime;

		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;

			}

			switch(e.type){

			case SDL_CONTROLLERBUTTONDOWN:

				if(e.cdevice.which == 0){

					if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A){

						Ship1.OnControllerButton(e.cbutton);
						break;
					}

				}

				break;

			case SDL_CONTROLLERAXISMOTION:

			break;

			}
		}

		const Sint16 Xvalue = SDL_GameControllerGetAxis(gGameController0,SDL_CONTROLLER_AXIS_LEFTX);
		const Sint16 Yvalue = SDL_GameControllerGetAxis(gGameController0,SDL_CONTROLLER_AXIS_LEFTY);

		Ship1.OnControllerAxis(Xvalue,Yvalue);

		Ship1.Update(deltaTime);


		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer,bkgd,NULL, &bkgdRect);

		Ship1.Draw(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
