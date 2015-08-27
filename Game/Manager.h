#ifndef __MANAGER_H_
#define __MANAGER_H_

#include "WorldModel.h"
#include "GUI.h"

class Manager
{
private:
	std::tr1::shared_ptr<WorldModel> wm;

	Manager();

public:
	static Manager *instance();
	void run();
};

#endif // __MANAGER_H_
