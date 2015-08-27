#include "RandomGenerator.h"

RandomGenerator::RandomGenerator()
{
	generator.seed(std::time(0)); // seed with the current time
}

RandomGenerator *RandomGenerator::instance()
{
	static RandomGenerator *rg = new RandomGenerator();
	return rg;
}

const int RandomGenerator::getInt(const int rangeMin, const int rangeMax)
{
	NumberDistributionInt distribution(rangeMin, rangeMax);
	GeneratorInt numberGenerator(generator, distribution);
	return numberGenerator();
}

const float RandomGenerator::getReal(const float rangeMin, const float rangeMax)
{
	NumberDistributionReal distribution(rangeMin, rangeMax);
	GeneratorReal numberGenerator(generator, distribution);
	return numberGenerator();
}
