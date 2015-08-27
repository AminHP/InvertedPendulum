#ifndef __PAIR_H_H
#define __PAIR_H_H

#include "State.h"
#include "Action.h"

#include <iostream>
#include <string>

struct Pair
{
	State state;
	Action act;

	Pair();
	Pair(const State, const Action);

	const std::string toStr() const;

	void operator =(const Pair &);
	const bool operator <(const Pair &) const;
	const bool operator ==(const Pair &) const;

	friend std::ostream &operator <<(std::ostream &, const Pair &);
	friend std::istream &operator >>(std::istream &, Pair &);
};

#endif // __PAIR_H_H
