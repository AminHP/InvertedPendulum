#include "Action.h"

#include <sstream>

using namespace std;

Action::Action()
{
	act = DO_NOTHING;
}

Action::Action(const int a)
{
	if (a == 0)
		act = DO_NOTHING;
	else if (a == 1)
		act = DO_LEFT_FORCE;
	else if (a == 2)
		act = DO_RIGHT_FORCE;
}

Action::Action(const ActionType a): act(a)
{
}

const string Action::toStr() const
{
	/*string s = "act = ";
	if (act == DO_NOTHING)
		s += "DO_NOTHING";
	else if (act == DO_LEFT_FORCE)
		s += "DO_LEFT_FORCE";
	else if (act == DO_RIGHT_FORCE)
		s += "DO_RIGHT_FORCE";*/

	string s = "";
	if (act == DO_NOTHING)
		s += "0";
	else if (act == DO_LEFT_FORCE)
		s += "1";
	else if (act == DO_RIGHT_FORCE)
		s += "2";

	return s;
}

void Action::operator =(const Action &a)
{
	act = a.act;
}

const bool Action::operator <(const Action &a) const
{
	return act < a.act;
}

const bool Action::operator ==(const Action &a) const
{
	return act == a.act;
}

ostream &operator <<(ostream &out, const Action &a)
{
	out << a.toStr();
	return out;
}

istream &operator >>(istream &in, Action &a)
{
	int tmp;
	in >> tmp;
	a = Action(tmp);
	return in;
}
