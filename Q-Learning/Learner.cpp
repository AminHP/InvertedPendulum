#include "Learner.h"

#include "RandomGenerator.h"

#include <fstream>
#include <sstream>

using namespace std;
using namespace tr1;

Learner::Learner(): error_angle_finish(3.0f), gamma(0.9f)
{
	wm = shared_ptr<WorldModel> (new WorldModel());
}

Learner *Learner::instance()
{
	static Learner *l = new Learner();
	return l;
}

void Learner::run()
{
	EventType event = GUI::instance()->handleEvents();

	for (unsigned int i = 0; i < 10000; i++)
	{
		currentState = generateRandomState();

		while (1)
		{
			Action randAct;
			if (fabs(currentState.cart_pos - wm->getMinRange()) < 0.01f)
			{
				while (1)
				{
					randAct = Action(RandomGenerator::instance()->getInt(0, ACTIONS_MAX - 1));
					if (randAct.act != DO_LEFT_FORCE)
						break;
				}
			}
			else if (fabs(currentState.cart_pos - wm->getMaxRange()) < 0.01f)
			{
				while (1)
				{
					randAct = Action(RandomGenerator::instance()->getInt(0, ACTIONS_MAX - 1));
					if (randAct.act != DO_RIGHT_FORCE)
						break;
				}
			}
			else
				randAct = Action(RandomGenerator::instance()->getInt(0, ACTIONS_MAX - 1));

			State nextState = wm->computeState(currentState, randAct);

			State normalCurrentState = wm->normalizeState(currentState);
			State normalNextState    = wm->normalizeState(nextState);

			double maxQNB = -99999;
			for (unsigned int j = 0; j < ACTIONS_MAX; j++)
			{
				Action nextAct(j);

				if (!Q_mark[Pair(normalNextState, nextAct).toStr()])
				{
					Q_mark[Pair(normalNextState, nextAct).toStr()] = 1;
					Q[Pair(normalNextState, nextAct).toStr()] = -99999;
				}
				double tmp = Q[Pair(normalNextState, nextAct).toStr()];
				if (tmp > maxQNB)
					maxQNB = tmp;
			}

			Q[Pair(normalCurrentState, randAct).toStr()] = calculateReward(currentState) + gamma * maxQNB;
			Q_mark[Pair(normalCurrentState, randAct).toStr()] = 1;

			wm->update(currentState);
			GUI::instance()->show(*wm);

			if (isEpisodeFinished(currentState))
				break;
			currentState = nextState;

			event = GUI::instance()->handleEvents();
			if (event == EQUIT)
				break;
		}
		cerr << "Episode " << i + 1 << " finished." << endl;

		if (event == EQUIT)
			break;
	}

	saveData();
}

const State Learner::generateRandomState() const
{
	State res;
	res.pendulum_angle = RandomGenerator::instance()->getReal(-M_PI, M_PI);
	res.pendulum_vel   = RandomGenerator::instance()->getReal(wm->getMinPendulumVel(), wm->getMaxPendulumVel());
	res.cart_vel       = RandomGenerator::instance()->getReal(wm->getMinCartVel(), wm->getMaxCartVel());
	res.cart_pos       = RandomGenerator::instance()->getReal(wm->getMinRange(), wm->getMaxRange());
	return res;
}

const double Learner::calculateReward(const State &s) const
{
	double fitness = 0;

	double angle = s.pendulum_angle;
	while (angle > M_PI)
		angle -= 2.0f * M_PI;
	while (angle < 0)
		angle += 2.0f * M_PI;

	fitness -= fabs(angle - M_PI_2);
	fitness -= fabs(s.pendulum_vel);
	fitness -= fabs(s.cart_vel);
	fitness -= fabs(s.cart_pos);

	double error = error_angle_finish * (M_PI / 180.0f);
	if (angle > M_PI_2 - error && angle < M_PI_2 + error)// && s.pendulum_vel < error && fabs(s.cart_vel) < 1.0f)
		fitness += 100.0f;

	return fitness;
}

const bool Learner::isEpisodeFinished(const State &s) const
{
	double angle = s.pendulum_angle;
	while (angle > M_PI)
		angle -= 2.0f * M_PI;
	while (angle < 0)
		angle += 2.0f * M_PI;

	double error = error_angle_finish * (M_PI / 180.0f);
	if (angle > M_PI_2 - error && angle < M_PI_2 + error)// && s.pendulum_vel < error && fabs(s.cart_vel) < 1.0f)
		return 1;

	return 0;
}

void Learner::saveData()
{
	ofstream save("Data/LearnedData");
	save << Q.size() << endl;
	for (map<string, double>::iterator it = Q.begin(); it != Q.end(); it++)
		save << it->first << " " << it->second << endl;
	save.close();
}
