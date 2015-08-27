#include "WorldModel.h"

#include <iostream>
#include <cmath>

using namespace std;
using namespace tr1;

WorldModel::WorldModel(): minRange(-2), maxRange(2), gravity(9.80665f), cycleTime(0.001f), 
		friction_static(0.5f), friction_kinetic(0.3f), force(10000.0f), acc_air(0.6f), 
		minCartVel(-4.0f), maxCartVel(4.0f), minPendulumVel(-2.0f * M_PI), maxPendulumVel(2.0f * M_PI)
{
	mPendulum = shared_ptr<Pendulum> (new Pendulum(0.20f, M_PI_4, 1.000f, 0));
	mCart     = shared_ptr<Cart>     (new Cart(50.0f, 0, 0));
}

const double WorldModel::getRange() const
{
	return fabs(maxRange - minRange);
}

const Pendulum WorldModel::getPendulum() const
{
	return *mPendulum;
}

const Cart WorldModel::getCart() const
{
	return *mCart;
}

const double WorldModel::getCycleTime() const
{
	return cycleTime;
}

const State WorldModel::computeState(const State &s, const Action &a)
{
	State newState = s;

	/// X-axis   (Force on cart)

	double f_motion = 0;
	double N = (mPendulum->mass + mCart->mass) * gravity;

	if (a.act != DO_NOTHING)
	{
		if (a.act == DO_LEFT_FORCE)
			f_motion -= force;
		else
			f_motion += force;
	}

	if (newState.cart_vel == 0.0f)
	{
		if (a.act != DO_NOTHING)
		{
			if (a.act == DO_LEFT_FORCE)
				f_motion += friction_static * N;
			else if (a.act == DO_RIGHT_FORCE)
				f_motion -= friction_static * N;
		}
	}
	else
	{
		double fk = friction_kinetic * N;
		double ak = fk / (mPendulum->mass + mCart->mass);
		double vk = ak * cycleTime;

		if (newState.cart_vel < 0.0f)
		{
			double v = newState.cart_vel + vk;
			bool setForce = 1;
			if (a.act == DO_NOTHING)
				if (v > 0)
				{
					newState.cart_vel = 0;
					setForce = 0;
				}

			if (setForce)
				f_motion += fk;
		}
		else if (newState.cart_vel > 0.0f)
		{
			double v = newState.cart_vel - vk;
			bool setForce = 1;
			if (a.act == DO_NOTHING)
				if (v < 0)
				{
					newState.cart_vel = 0;
					setForce = 0;
				}

			if (setForce)
				f_motion -= fk;
		}
	}

	double fx = f_motion + (mPendulum->mass * gravity) * cos(newState.pendulum_angle);

	newState.cart_vel += (fx / (mPendulum->mass + mCart->mass)) * cycleTime;
	newState.cart_pos += newState.cart_vel * cycleTime;

	if (newState.cart_pos > maxRange)
	{
		newState.cart_pos = maxRange;
		newState.cart_vel = 0;
	}
	if (newState.cart_pos < minRange)
	{
		newState.cart_pos = minRange;
		newState.cart_vel = 0;
	}

	if (newState.cart_vel > maxCartVel)
		newState.cart_vel = maxCartVel;
	if (newState.cart_vel < minCartVel)
		newState.cart_vel = minCartVel;

	/// Y-axis   (Force on pendulum)

	f_motion /= (mPendulum->mass + mCart->mass) * mPendulum->mass;

	double fy = f_motion * sin(newState.pendulum_angle) - (gravity * mPendulum->mass) * cos(newState.pendulum_angle);
	double ay = fy / mPendulum->mass;
	newState.pendulum_vel += ay * cycleTime;

	if (newState.pendulum_vel > maxPendulumVel)
		newState.pendulum_vel = maxPendulumVel;
	if (newState.pendulum_vel < minPendulumVel)
		newState.pendulum_vel = minPendulumVel;

	/// Air Friction
	if (newState.pendulum_vel > 0)
		newState.pendulum_vel -= acc_air * cycleTime;
	if (newState.pendulum_vel < 0)
		newState.pendulum_vel += acc_air * cycleTime;

	double dy = newState.pendulum_vel * cycleTime;
	double d_angle = dy / mPendulum->length;

	while (newState.pendulum_angle < 0)
		newState.pendulum_angle += 2.0f * M_PI;

	newState.pendulum_angle += d_angle;

	while (newState.pendulum_angle > M_PI)
		newState.pendulum_angle -= 2.0f * M_PI;

	return newState;
}

void WorldModel::update(const Action act)
{
	State s(mPendulum->angle, mPendulum->vel, mCart->vel, mCart->pos);
	Action a = act;

	State newState   = computeState(s, a);

	mPendulum->angle = newState.pendulum_angle;
	mPendulum->vel   = newState.pendulum_vel;
	mCart->vel       = newState.cart_vel;
	mCart->pos       = newState.cart_pos;
}

void WorldModel::update(const State s)
{
	mPendulum->angle = s.pendulum_angle;
	mPendulum->vel   = s.pendulum_vel;
	mCart->vel       = s.cart_vel;
	mCart->pos       = s.cart_pos;
}

const double WorldModel::getMinRange() const
{
	return minRange;
}

const double WorldModel::getMaxRange() const
{
	return maxRange;
}

const double WorldModel::getMinCartVel() const
{
	return minCartVel;
}

const double WorldModel::getMaxCartVel() const
{
	return maxCartVel;
}

const double WorldModel::getMinPendulumVel() const
{
	return minPendulumVel;
}

const double WorldModel::getMaxPendulumVel() const
{
	return maxPendulumVel;
}

const State WorldModel::normalizeState(const State s) const
{
	int pendulum_angle = 0;
	int pendulum_vel   = 0;
	int cart_vel       = 0;
	int cart_pos       = 0;

	pendulum_angle = (s.pendulum_angle * (180.0f / M_PI)) / 10;
	pendulum_vel   = (s.pendulum_vel   * (180.0f / M_PI)) / 10;
	cart_vel       = s.cart_vel;

	if (s.cart_pos < -1.0f)
		cart_pos = 0;
	else if (s.cart_pos >= -1.0f && s.cart_pos <= 1.0f)
		cart_pos = 1;
	else
		cart_pos = 2;

	return State(pendulum_angle, pendulum_vel, cart_vel, cart_pos);
}
