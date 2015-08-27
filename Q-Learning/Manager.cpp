#include "Manager.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace tr1;

Manager::Manager()
{
	wm = shared_ptr<WorldModel> (new WorldModel());
	loadData();
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

		wm->update(findBestAction());
	}
}

void Manager::loadData()
{
	ifstream load("Data/LearnedData");

	int size = 0;
	load >> size;
	for (int i = 0; i < size; i++)
	{
		Pair p;
		double reward = 0;
		load >> p >> reward;
		Q[p.toStr()] = reward;
		Q_mark[p.toStr()] = 1;
	}

	load.close();
}

const Action Manager::findBestAction()
{
	State currentState(wm->getPendulum().angle, wm->getPendulum().vel, wm->getCart().vel, wm->getCart().pos);
	State normalCurrentState = wm->normalizeState(currentState);

	double max = -99999;
	int index = 0;
	for (int i = 0; i < ACTIONS_MAX; i++)
	{
		Pair p(normalCurrentState, Action(i));
		double r = (Q_mark[p.toStr()]) ? Q[p.toStr()] : -99999;
		if (r >= max)
		{
			max = r;
			index = i;
		}
	}

	return Action(index);
}
