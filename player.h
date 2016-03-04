#if defined(__APPLE__)
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"

#endif

#if defined(_WIN32) || (_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL_ttf.h"
#endif

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

#include <vector>
#include "missile.h"

class Ship{

public:

	bool active;

	int playerScore, oldScore, playerLives, oldLives;

	TTF_Font *font;

	SDL_Color colorP1 = {0,255,0,255};

	SDL_Surface *scoreSurface, *livesSurface;

	SDL_Texture *scoreTexture, *livesTexture;

	SDL_Rect scorePos, livesPos;

	string tempScore, tempLives;

	vector<Missile> bulletList;

	string playerPath;

	int playerNum;

	SDL_Texture *texture;

	SDL_Rect posRect;

	float xDir, xDirOld;
	float yDir, yDirOld;

	float speed;

	float pos_X, pos_Y;

	float x, y, shipangle;

	SDL_Point center;

	float oldAngle;

	Mix_Chunk *fire;

	Sint16 Xvalue, Yvalue;


	Ship (SDL_Renderer *renderer, int pNum, string filePath, string sudioPath, float x, float y);

	void OnControllerAxis(Sint16 Xvalue, Sint16 Yvalue);

	void OnControllerButton(const SDL_ControllerButtonEvent event);

	void Update(float deltaTime, SDL_Renderer *renderer);

	void Draw(SDL_Renderer * renderer);

	void Reset();

	void UpdateScore(SDL_Renderer *renderer);

	void UpdateLives(SDL_Renderer *renderer);

private:

	void CreateBullet();

};
