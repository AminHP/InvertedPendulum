#include <iostream>

#include "Manager.h"
#include "Learner.h"

using namespace std;

int main(int argc, char **argv)
{
	if (argc == 2)
		Learner::instance()->run();
	else
		Manager::instance()->run();
	return 0;
}
