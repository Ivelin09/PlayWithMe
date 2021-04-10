#pragma once

#include "Images.h"

class Stars : public Image
{
public:
	Stars() : Image() {

	}

	void activate() {
		this->setTexture("star.png");
	}
};

