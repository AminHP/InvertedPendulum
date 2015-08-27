#ifndef __RANDOM_GENERATOR_H_
#define __RANDOM_GENERATOR_H_

#include <boost/random.hpp>
 
#include <iostream>
#include <ctime>

class RandomGenerator
{
private:
	RandomGenerator();

	typedef boost::uniform_int<> NumberDistributionInt;
	typedef boost::uniform_real<> NumberDistributionReal;
	typedef boost::mt19937 RandomNumberGenerator;
	typedef boost::variate_generator<RandomNumberGenerator&, NumberDistributionInt> GeneratorInt;
	typedef boost::variate_generator<RandomNumberGenerator&, NumberDistributionReal> GeneratorReal;

	RandomNumberGenerator generator;

public:
	static RandomGenerator *instance();

	const int getInt(const int, const int);
	const float getReal(const float, const float);
};

#endif // __RANDOM_GENERATOR_H_
