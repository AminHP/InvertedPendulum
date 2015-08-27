#include "Manager.h"

#include <iostream>

using namespace std;
using namespace tr1;

Manager::Manager()
{
	wm = shared_ptr<WorldModel> (new WorldModel());
}

Manager *Manager::instance()
{
	static Manager *m = new Manager();
	return m;
}

void Manager::run()
{
	while (1)
	{
		GUI::instance()->show(*wm);
		EventType event = GUI::instance()->handleEvents();

		if (event == EQUIT)
			break;

		MovementType mt = MSTATIC;
		if (event == ELEFT)
			mt = MLEFT;
		else if (event == ERIGHT)
			mt = MRIGHT;
		wm->update(mt);
	}
}
