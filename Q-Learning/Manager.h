#ifndef __MANAGER_H_
#define __MANAGER_H_

#include "WorldModel.h"
#include "GUI.h"
#include "Pair.h"

#include <map>
#include <string>

class Manager
{
private:
	std::tr1::shared_ptr<WorldModel> wm;
	std::map<std::string, double> Q;
	std::map<std::string, bool> Q_mark;

	Manager();
	void loadData();
	const Action findBestAction();

public:
	static Manager *instance();
	void run();
};

#endif // __MANAGER_H_
