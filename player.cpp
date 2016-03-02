#include "player.h"

const int JOYSTICK_DEAD_ZONE = 8000;

Ship::Ship(SDL_Renderer *renderer, int pNum, string filePath, string audioPath, float x, float y)
{
	active = true;

	playerNum = pNum;

	speed = 200.0f;

	fire = Mix_LoadWAV((audioPath + "Laser.wav").c_str());

	if(playerNum == 0){
		playerPath = filePath + "spaceship.png";
	}

	texture = IMG_LoadTexture(renderer, playerPath.c_str());

	posRect.x = x;
	posRect.y = y;
	posRect.w = 144;
	posRect.h = 104;

	pos_X = x;
	pos_Y = y;

	xDir = 0;
	yDir = 0;

	xDirOld = 1;
	yDirOld = 0;

	center.x = posRect.w/2;
	center.y = posRect.h/2;

	string bulletPath;

	if(playerNum == 0){
		//create the bullet 1 texture
		bulletPath = filePath + "missile.png";
	}

	for(int i = 0; i < 10; i++)
	{
		Missile tmpBullet(renderer,bulletPath,-1000,-1000,0,0);

		bulletList.push_back(tmpBullet);
	}
}

void Ship::Update(float deltaTime)
{
	if(Xvalue != 0 || Yvalue != 0){
		shipangle = atan2(Yvalue,Xvalue) * 180/3.14;

		oldAngle = shipangle;

		float radians = (shipangle * 3.14)/180;

		float move_x = speed *cos(radians);
		float move_y = speed *sin(radians);

		pos_X += (move_x) * deltaTime;
		pos_Y += (move_y) * deltaTime;

		posRect.x = (int)(pos_X + 0.5f);
		posRect.y = (int)(pos_Y + 0.5f);

	}else {
		shipangle = oldAngle;
	}

	if(posRect.x < 0){
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if(posRect.x > 1024 - posRect.w){
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}

	if(posRect.y < 0){
		posRect.y = 0;
		pos_Y = posRect.y;
	}

	if(posRect.y > 768 - posRect.h){
		posRect.y = 768 - posRect.h;
		pos_Y = posRect.y;
	}

	 for(int i = 0; i< bulletList.size(); i++)
	  {
		  if(bulletList[i].active){

			  bulletList[i].Update(deltaTime);
		  }
	  }

}

void Ship::Draw(SDL_Renderer *renderer)
{

	for(int i = 0; i < bulletList.size(); i++)
	{
		if(bulletList[i].active){

			//draw bullet
			bulletList[i].Draw(renderer);
		}
	}

	SDL_RenderCopyEx(renderer, texture, nullptr, &posRect, shipangle, &center, SDL_FLIP_NONE);

}

void Ship::OnControllerButton(const SDL_ControllerButtonEvent event)
{
	if(event.which == 0 && playerNum == 0)
	{
		if(event.button == 0)
		{
			CreateBullet();

		}

	}

	if(event.which == 1 && playerNum == 1)
	{
		if(event.button == 0)
		{

			CreateBullet();

		}
	}
}

void Ship::OnControllerAxis(Sint16 X, Sint16 Y)
{
	Xvalue = X;
	Yvalue = Y;

	if(!(Xvalue < -JOYSTICK_DEAD_ZONE)&&!(Xvalue > JOYSTICK_DEAD_ZONE))
	{
		Xvalue = 0.0f;
	}

	if(!(Yvalue < -JOYSTICK_DEAD_ZONE)&&!(Yvalue > JOYSTICK_DEAD_ZONE))
	{
		Yvalue = 0.0f;
	}


}

//create a bullet
void Ship::CreateBullet(){

	for(int i = 0; i < bulletList.size(); i ++)
	{
		if(bulletList[i].active == false){

		Mix_PlayChannel(-1 ,fire, 0);

		//set bullet to active
		bulletList[i].active = true;

		bulletList[i].posRect.x = (posRect.x + (posRect.w/2));
		bulletList[i].posRect.y = (posRect.y + (posRect.h/2));

		bulletList[i].posRect.x = bulletList[i].posRect.x - (bulletList[i].posRect.w/2);
		bulletList[i].posRect.y = bulletList[i].posRect.y - (bulletList[i].posRect.h/2);

		bulletList[i].pos_X = bulletList[i].posRect.x;
		bulletList[i].pos_Y = bulletList[i].posRect.y;

		if(Xvalue != 0 || Yvalue != 0){
			bulletList[i].shipangle = shipangle;

		}else{
			bulletList[i].shipangle = oldAngle;
			}

		break;

		}
	}

}
