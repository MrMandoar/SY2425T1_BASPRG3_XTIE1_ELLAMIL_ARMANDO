#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include <vector>

using namespace std;


class Player : public GameObject
{
public:
    ~Player();
    void start();
    void update();
    void draw();

private:
    int x;
    int y;
    int width;
    int height;

    int Speed;
    int InitialSpeed;

    float reloadTime;
    float currentReloadTime;

    vector<Bullet*> bullets;

    SDL_Texture* texture;
    Mix_Chunk* sound;


};