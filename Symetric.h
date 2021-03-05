#pragma once

#include<vector>
template<typename A>
void setSymetric(std::vector<A>& buttons, const int startWidth,
	const int width, const double x, const double y)
{
	double substractedWidth = width - startWidth - (x * buttons.size());
	double deltaWidth = substractedWidth / (buttons.size() * 2);

	double currPos = startWidth;

	for (auto& k : buttons)
	{
		currPos += deltaWidth;

		k.getShape().setPosition(currPos, y);
		currPos += x + deltaWidth;
	}

}
