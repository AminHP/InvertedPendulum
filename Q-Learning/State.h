#ifndef __STATE_H_
#define __STATE_H_

#include <iostream>
#include <string>

struct State
{
	double pendulum_angle;
	double pendulum_vel;
	double cart_vel;
	double cart_pos;

	State();
	State(const double, const double, const double, const double);

	const std::string toStr() const;

	void operator =(const State &);
	const bool operator <(const State &) const;
	const bool operator ==(const State &) const;

	friend std::ostream &operator <<(std::ostream &, const State &);
	friend std::istream &operator >>(std::istream &, State &);
};

#endif // __STATE_H_
