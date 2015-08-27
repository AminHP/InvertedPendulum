#include "WorldModel.h"

#include <iostream>
#include <cmath>

using namespace std;
using namespace tr1;

WorldModel::WorldModel(): minRange(-2), maxRange(2), gravity(9.80665f), cycleTime(0.001f), 
		friction_static(0.5f), friction_kinetic(0.3f), force(1000.0f), acc_air(0.6f)
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

void WorldModel::update(const MovementType mt)
{
	/// X-axis   (Force on cart)

	double f_motion = 0;
	double N = (mPendulum->mass + mCart->mass) * gravity;

	if (mt != MSTATIC)
	{
		if (mt == MLEFT)
			f_motion -= force;
		else
			f_motion += force;
	}

	if (mCart->vel == 0.0f)
	{
		if (mt != MSTATIC)
		{
			if (mt == MLEFT)
				f_motion += friction_static * N;
			else if (mt == MRIGHT)
				f_motion -= friction_static * N;
		}
	}
	else
	{
		double fk = friction_kinetic * N;
		double ak = fk / (mPendulum->mass + mCart->mass);
		double vk = ak * cycleTime;

		if (mCart->vel < 0.0f)
		{
			double v = mCart->vel + vk;
			bool setForce = 1;
			if (mt == MSTATIC)
				if (v > 0)
				{
					mCart->vel = 0;
					setForce = 0;
				}

			if (setForce)
				f_motion += fk;
		}
		else if (mCart->vel > 0.0f)
		{
			double v = mCart->vel - vk;
			bool setForce = 1;
			if (mt == MSTATIC)
				if (v < 0)
				{
					mCart->vel = 0;
					setForce = 0;
				}

			if (setForce)
				f_motion -= fk;
		}
	}

	double fx = f_motion + (mPendulum->mass * gravity) * cos(mPendulum->angle);

	mCart->vel += (fx / (mPendulum->mass + mCart->mass)) * cycleTime;
	mCart->pos += mCart->vel * cycleTime;

	if (mCart->pos > maxRange)
	{
		mCart->pos = maxRange;
		mCart->vel = 0;
	}
	if (mCart->pos < minRange)
	{
		mCart->pos = minRange;
		mCart->vel = 0;
	}

	/// Y-axis   (Force on pendulum)

	f_motion /= (mPendulum->mass + mCart->mass) * mPendulum->mass;

	double fy = f_motion * sin(mPendulum->angle) - (gravity * mPendulum->mass) * cos(mPendulum->angle);
	double ay = fy / mPendulum->mass;
	mPendulum->vel += ay * cycleTime;

	/// Air Friction
	if (mPendulum->vel > 0)
		mPendulum->vel -= acc_air * cycleTime;
	if (mPendulum->vel < 0)
		mPendulum->vel += acc_air * cycleTime;

	double dy = mPendulum->vel * cycleTime;
	double d_angle = dy / mPendulum->length;

	while (mPendulum->angle < 0)
		mPendulum->angle += 2.0f * M_PI;

	mPendulum->angle += d_angle;
}
