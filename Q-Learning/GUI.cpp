#include "GUI.h"

#include <iostream>

using namespace std;

GUI::GUI(): screen_width(1000), screen_height(400), startX(100), startY(200), range(800)
{
	SDL_Init(SDL_INIT_VIDEO);
	screen = SDL_SetVideoMode(screen_width, screen_height, 0, SDL_HWSURFACE);
	canShow = 1;
}

GUI *GUI::instance()
{
	static GUI *gui = new GUI();
	return gui;
}

void GUI::show(const WorldModel &wm) const
{
	if (!canShow)
		return ;

	boxRGBA(screen, 0, 0, screen_width, screen_height, 0, 0, 0, 255);

	lineRGBA(screen, startX, startY - 5, startX, startY + 5, 255, 0, 0, 255);
	lineRGBA(screen, startX + range, startY - 5, startX + range, startY + 5, 255, 0, 0, 255);
	lineRGBA(screen, startX, startY, startX + range, startY, 100, 100, 100, 255);

	double r2r = range / wm.getRange();
	double startPos = wm.getCart().pos * r2r;
	double endPosX  = wm.getPendulum().length * cos(wm.getPendulum().angle) * r2r;
	double endPosY  = wm.getPendulum().length * sin(wm.getPendulum().angle) * r2r;
	lineRGBA(screen, startX + range / 2.0f + startPos, startY, startX + startPos + range / 2.0f + endPosX, startY - endPosY, 255, 255, 255, 255);

	SDL_Delay(wm.getCycleTime() * 1000);
	SDL_Flip(screen);
}

EventType GUI::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return EQUIT;

		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_q)
				return EQUIT;
			if (event.key.keysym.sym == SDLK_s)
				canShow = !canShow;
		}
	}

	return ENULL;
}
