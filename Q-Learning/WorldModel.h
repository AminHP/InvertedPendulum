#ifndef __WORLDMODEL_H_
#define __WORLDMODEL_H_

#include "Pendulum.h"
#include "Cart.h"
#include "State.h"
#include "Action.h"

#include <tr1/memory>

class WorldModel
{
private:
	std::tr1::shared_ptr<Pendulum> mPendulum;
	std::tr1::shared_ptr<Cart> mCart;

	const double minRange;
	const double maxRange;
	const double gravity;
	const double cycleTime;

	const double friction_static;
	const double friction_kinetic;
	const double force;
	const double acc_air;

	const double minCartVel;
	const double maxCartVel;
	const double minPendulumVel;
	const double maxPendulumVel;

public:
	WorldModel();

	const double getRange() const;
	const Pendulum getPendulum() const;
	const Cart getCart() const;
	const double getCycleTime() const;

	const State computeState(const State &, const Action &);
	void update(const Action);
	void update(const State);

	const double getMinRange() const;
	const double getMaxRange() const;
	const double getMinCartVel() const;
	const double getMaxCartVel() const;
	const double getMinPendulumVel() const;
	const double getMaxPendulumVel() const;

	const State normalizeState(const State) const;
};

#endif // __WORLDMODEL_H_
