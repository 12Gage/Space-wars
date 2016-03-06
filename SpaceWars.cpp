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
#include "rock.h"
#include"littleRock.h"
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "explosion.h"

vector<Rock> rockList;

vector<littleRock> rockList1;

vector<Explode> explosionList;

void MakeExplosion(int x, int y) {
	for (int i = 0; i < explosionList.size(); i++)
	{
		if (explosionList[i].active == false) {

			explosionList[i].active = true;

			explosionList[i].posRect.x = x;
			explosionList[i].posRect.y = y;

			break;
		}
	}
}

float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

SDL_Rect playerPos;

int main(int argc, char* argv[]){

	srand(time_t(NULL));

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

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "background.mp3").c_str());

	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	Mix_Chunk *explosionSound = Mix_LoadWAV((audio_dir + "Explosion.wav").c_str());

	SDL_Event e;

	SDL_GameControllerEventState(SDL_ENABLE);

	SDL_GameController* gGameController0 = NULL;

	gGameController0 = SDL_GameControllerOpen(0);

	Ship Ship1 = Ship(renderer, 0, images_dir.c_str(), audio_dir.c_str(), 400.0,250.0);

	SDL_Texture *bkgd = IMG_LoadTexture(renderer, (images_dir + "background.png").c_str());

	SDL_Rect bkgdRect;

	bkgdRect.x = 0;

	bkgdRect.y = 0;

	bkgdRect.w = 1024;

	bkgdRect.h = 768;

	playerPos.x = 10;
	playerPos.y = 10;

	for(int i = 0; i < 1; i++)
	{
		Rock tmpRock(renderer, images_dir);

		rockList.push_back(tmpRock);
	}

	for (int i = 0; i < 2; i++)
	{
		littleRock tmpRock(renderer, images_dir);

		rockList1.push_back(tmpRock);
	}

	for (int i = 0; i < 20; i++)
	{
		Explode tmpExplode(renderer, images_dir, -1000, -1000);

		explosionList.push_back(tmpExplode);
	}

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

		Ship1.Update(deltaTime, renderer);

		for(int i = 0; i < rockList.size(); i ++)
		{
			rockList[i].Update(deltaTime);
		}

		for (int i = 0; i < rockList1.size(); i++)
		{
			rockList1[i].Update(deltaTime);
		}

		for (int i = 0; i < Ship1.bulletList.size(); i++)
		{
			if (Ship1.bulletList[i].active == true) {

				for (int j = 0; j < rockList.size(); j++)
				{
					if (SDL_HasIntersection(&Ship1.bulletList[i].posRect, &rockList[j].posRect)) {

						Mix_PlayChannel(-1, explosionSound, 0);

						MakeExplosion(rockList[j].posRect.x, rockList[j].posRect.y);

						rockList[j].Reset();

						Ship1.bulletList[i].Reset();

						Ship1.playerScore += 50;

					}
				}
			}
		}

		for (int i = 0; i < Ship1.bulletList.size(); i++)
		{
			if (Ship1.bulletList[i].active == true) {

				for (int j = 0; j < rockList1.size(); j++)
				{
					if (SDL_HasIntersection(&Ship1.bulletList[i].posRect, &rockList1[j].posRect)) {

						Mix_PlayChannel(-1, explosionSound, 0);

						MakeExplosion(rockList1[j].posRect.x, rockList1[j].posRect.y);

						rockList1[j].Reset();

						Ship1.bulletList[i].Reset();

						Ship1.playerScore += 100;

					}
				}
			}
		}

		for (int i = 0; i < rockList.size(); i++) {

			if (SDL_HasIntersection(&Ship1.posRect, &rockList[i].posRect)) {

				Mix_PlayChannel(-1, explosionSound, 0);

				MakeExplosion(Ship1.posRect.x - 32, Ship1.posRect.y - 32);

				rockList[i].Reset();

				Ship1.playerLives -= 1;
			}
		}

		for (int i = 0; i < rockList1.size(); i++) {

			if (SDL_HasIntersection(&Ship1.posRect, &rockList1[i].posRect)) {

				Mix_PlayChannel(-1, explosionSound, 0);

				MakeExplosion(Ship1.posRect.x - 32, Ship1.posRect.y - 32);

				rockList1[i].Reset();

				Ship1.playerLives -= 1;
			}
		}

		for (int i = 0; i < explosionList.size(); i++)
		{
			if (explosionList[i].active == true) {

				explosionList[i].Update(deltaTime);
			}
		}

		SDL_RenderClear(renderer);

		SDL_RenderCopy(renderer,bkgd,NULL, &bkgdRect);

		for(int i = 0; i < rockList.size(); i ++)
		{
			rockList[i].Draw(renderer);
		}

		for (int i = 0; i < rockList1.size(); i++)
		{
			rockList1[i].Draw(renderer);
		}

		for (int i = 0; i < explosionList.size(); i++)
		{
			if (explosionList[i].active == true) {

				explosionList[i].Draw(renderer);
			}
		}

		Ship1.Draw(renderer);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}
