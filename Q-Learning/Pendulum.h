#ifndef __PENDULUM_H_
#define __PENDULUM_H_

struct Pendulum
{
	const double length;
	double angle;
	const double mass;
	double vel;

	Pendulum(const double, const double, const double, const double);
};

#endif // __PENDULUM_H_
