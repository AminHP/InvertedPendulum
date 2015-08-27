#ifndef __WORLDMODEL_H_
#define __WORLDMODEL_H_

#include "Pendulum.h"
#include "Cart.h"

#include <tr1/memory>

enum MovementType
{
	MSTATIC,
	MLEFT,
	MRIGHT
};

class WorldModel
{
private:
	std::tr1::shared_ptr<Pendulum> mPendulum;
	std::tr1::shared_ptr<Cart> mCart;

	const double minRange, maxRange;
	const double gravity;
	const double cycleTime;

	const double friction_static;
	const double friction_kinetic;
	const double force;
	const double acc_air;

public:
	WorldModel();

	const double getRange() const;
	const Pendulum getPendulum() const;
	const Cart getCart() const;
	const double getCycleTime() const;

	void update(const MovementType);
};

#endif // __WORLDMODEL_H_
