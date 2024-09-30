#include "Player.h"

Player::~Player()
{
}

void Player::start()
{
	// playah
	texture = loadTexture("gfx/player.png");

	// da start
	x = 100;
	y = 100;
	width = 0;
	height = 0;

	Speed = 3;
	InitialSpeed = Speed;
	// set da height and width
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}


// da inputs
void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= Speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += Speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= Speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += Speed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		Speed = 5;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		Speed = InitialSpeed;
	}

}

void Player::draw()
{
	blit(texture, x, y);
}
