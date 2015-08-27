#include "State.h"

#include <cmath>
#include <sstream>

using namespace std;

State::State()
{
	pendulum_angle = 0;
	pendulum_vel   = 0;
	cart_vel       = 0;
	cart_pos       = 0;
}

State::State(const double pa, const double pv, const double cv, const double cp): pendulum_angle(pa), pendulum_vel(pv), cart_vel(cv), cart_pos(cp)
{
}

const string State::toStr() const
{
	stringstream ss;
	//ss << "pendulum_angle = " << pendulum_angle << "  pendulum_vel = " << pendulum_vel << "  cart_vel = " << cart_vel << "  cart_pos = " << cart_pos;
	ss << pendulum_angle << " " << pendulum_vel << " " << cart_vel << " " << cart_pos;
	return ss.str();
}

void State::operator =(const State &s)
{
	pendulum_angle = s.pendulum_angle;
	pendulum_vel   = s.pendulum_vel;
	cart_vel       = s.cart_vel;
	cart_pos       = s.cart_pos;
}

const bool State::operator <(const State &s) const
{
	return pendulum_angle < s.pendulum_angle || pendulum_vel < s.pendulum_vel || cart_vel < s.cart_vel || cart_pos < s.cart_pos;
}

const bool State::operator ==(const State &s) const
{
	return pendulum_angle == s.pendulum_angle;
}

ostream &operator <<(ostream &out, const State &s)
{
	out << s.toStr();
	return out;
}

istream &operator >>(istream &in, State &s)
{
	in >> s.pendulum_angle >> s.pendulum_vel >> s.cart_vel >> s.cart_pos;
	return in;
}
