#ifndef __CART_H_
#define __CART_H_

struct Cart
{
	const double mass;
	double pos;
	double vel;

	Cart(const double, const double, const double);
};

#endif // __CART_H_
