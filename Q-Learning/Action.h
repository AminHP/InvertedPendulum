#ifndef __ACTION_H_
#define __ACTION_H_

#include <iostream>
#include <string>

enum ActionType
{
	DO_NOTHING,
	DO_LEFT_FORCE,
	DO_RIGHT_FORCE,
	ACTIONS_MAX
};

struct Action
{
	ActionType act;

	Action();
	Action(const int);
	Action(const ActionType);

	const std::string toStr() const;

	void operator =(const Action &);
	const bool operator <(const Action &) const;
	const bool operator ==(const Action &) const;

	friend std::ostream &operator <<(std::ostream &, const Action &);
	friend std::istream &operator >>(std::istream &, Action &);
};

#endif // __ACTION_H_
