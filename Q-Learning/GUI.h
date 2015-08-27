#ifndef __GUI_H_
#define __GUI_H_

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "WorldModel.h"

enum EventType
{
	ENULL,
	EQUIT,
};

class GUI
{
private:
	SDL_Surface* screen;
	SDL_Event event;

	const float screen_width;
	const float screen_height;
	const float startX, startY;
	const float range;

	bool canShow;

	GUI();

public:
	static GUI *instance();

	void show(const WorldModel &) const;
	EventType handleEvents();
};

#endif // __GUI_H_
