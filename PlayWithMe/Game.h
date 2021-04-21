#pragma once

#include "Window.h"
#include<vector>

#include "Stars.h"
enum GAME_TYPE { DRAGGAME = 0, SOUNDGAME, FALLINGGAME };

class Game
{
public:
	
	Game() = default;
protected:
	int strike;
};
