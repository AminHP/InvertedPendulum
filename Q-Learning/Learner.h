#ifndef __LEARNER_H_
#define __LEARNER_H_

#include "WorldModel.h"
#include "GUI.h"
#include "Pair.h"

#include <tr1/memory>
#include <map>
#include <string>

class Learner
{
private:
	const double error_angle_finish;
	const double gamma;

	std::tr1::shared_ptr<WorldModel> wm;
	State currentState;

	std::map<std::string, double> Q;
	std::map<std::string, bool> Q_mark;

	Learner();
	const State generateRandomState() const;
	const double calculateReward(const State &) const;
	const bool isEpisodeFinished(const State &) const;
	void updateQ();
	void saveData();

public:
	static Learner *instance();
	void run();
};

#endif // __LEARNER_H_
