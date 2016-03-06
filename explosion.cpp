#include "explosion.h"

Explode::Explode(SDL_Renderer *rrenderer, string filePath, float x, float y)
{
	active = false;

	string explodePath = filePath + "boom3.png";

	frameCounter = 0.0f;

	SDL_Surface *surface = IMG_Load(explodePath.c_str());

	texture = SDL_CreateTextureFromSurface(rrenderer, surface);

	SDL_FreeSurface(surface);

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	textureWidth = w;
	textureHeight = h;

	posRect.w = 128;
	posRect.h = 128;

	posRect.x = x;
	posRect.y = y;

	FrameWidth = 128;
	FrameHeight = 128;

	drawRect.x = 128;
	drawRect.y = 0;
	drawRect.w = FrameWidth;
	drawRect.h = FrameHeight;

}

void Explode::Update(float deltaTime) 
{
	if (active) {

		frameCounter += deltaTime;

		if (frameCounter >= .035f) {

			frameCounter = 0.0f;

			drawRect.x += FrameWidth;

			if (drawRect.x >= textureWidth)
			{
				drawRect.x = 0;

				active = false;

				posRect.x = -1000;
				posRect.y = -1000;

			}
		}
	}
}

void Explode::Reset() {

	active = false;

}

void Explode::Draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, &drawRect, &posRect);
}

Explode::~Explode()
{

}