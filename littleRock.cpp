#include "littleRock.h"

littleRock::littleRock(SDL_Renderer *renderer, string filePath)
{
	string enemyPath = filePath + "littleRock.png";

	SDL_Surface *surface = IMG_Load(enemyPath.c_str());

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	int h, w;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	posRect.w = w;
	posRect.h = h;

	Reset();

	xDir = 1;
	yDir = 1;

	angle = rand() % (360);

	center.x = posRect.w / 2;
	center.y = posRect.h / 2;

}

void littleRock::Reset() {

	speed = rand() % (5) + 1;
	speed *= 100;

	posRect.x = rand() % (1024) + 1;
	posRect.y = -posRect.h;

	pos_X = posRect.x;
	pos_Y = posRect.y;
}

void littleRock::Update(float deltaTime)
{
	pos_X += (speed *xDir) * deltaTime;

	posRect.x = (int)(pos_X + 0.5f);

	pos_Y += (speed *yDir) * deltaTime;

	posRect.y = (int)(pos_Y + 0.5f);

	if (posRect.x > 1024) {

		Reset();
	}

	if (posRect.y > 768) {

		Reset();
	}

	angle += .1;

}

void littleRock::Draw(SDL_Renderer * renderer)
{
	SDL_RenderCopyEx(renderer, texture, NULL, &posRect, angle, &center, SDL_FLIP_NONE);
}

littleRock::~littleRock()
{

}
