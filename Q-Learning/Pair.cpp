#include "Pair.h"

#include <sstream>

using namespace std;

Pair::Pair()
{
}

Pair::Pair(const State s, const Action a): state(s), act(a)
{
}

const string Pair::toStr() const
{
	stringstream ss;
	//ss << state << "  " << act;
	ss << state << " " << act;
	return ss.str();
}

void Pair::operator =(const Pair &p)
{
	state = p.state;
	act   = p.act;
}

const bool Pair::operator <(const Pair &p) const
{
	return state < p.state || act < p.act;
}

const bool Pair::operator ==(const Pair &p) const
{
	return (state == p.state) && (act == p.act);
}

ostream &operator <<(ostream &out, const Pair &p)
{
	out << p.toStr();
	return out;
}

istream &operator >>(istream &in, Pair &p)
{
	in >> p.state >> p.act;
	return in;
}
