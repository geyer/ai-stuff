#include "ParticleFilter.h"
#include <random>
#include <numeric>

namespace Filter
{
  class ParticleGenerator
  {
  public:
    Particle operator() ()
    {
      auto position_distribution =
	std::uniform_real_distribution<double> { -1.0, 1.0 };
      auto orientation_distribution =
	std::uniform_real_distribution<double> { 0.0, 2 * PI };

      return Particle { position_distribution(generator),
	  orientation_distribution(generator) };
    }

  private:
    std::default_random_engine generator;
  };

  Orientation inverse(const Orientation &o)
  {
    return 1 / o;
  }

  double measurementProbability(const Particle& p, const Landmarks &measurement,
				const Landmarks &landmarks)
  {
    // prediction for a single landmark
    auto prediction = [&p] (Coordinates landmarkPosition,
			    Coordinates landmarkMeasurement)
      {
	auto relativePosition = landmarkPosition - p.position;
	auto expectedCoordinates = inverse(p.orientation) * relativePosition;
	auto noise = p.measurementNoise;
	auto distribution = [&expectedCoordinates, &noise]
	(Coordinates c)
	{ return std::exp (-std::pow(c - expectedCoordinates, 2) / noise); };

	return distribution(landmarkMeasurement);
      };

    // set probability the distribution value at the measurement.
    auto prob =
      std::inner_product(std::begin(measurement), std::end(measurement),
			 std::begin(landmarks),
			 1.0,
			 std::plus<double>(), prediction);
    return prob;
  }

  ParticleFilter::ParticleFilter(std::size_t n)
    : particles(n)
  {
    auto particleGenerator = ParticleGenerator();

    std::generate (particles.begin(), particles.end(), particleGenerator);
  }

  void ParticleFilter::act(const std::function<Particle (const Particle &)> &movementFunction)
  {
    std::transform (particles.begin(), particles.end(), particles.begin(),
		    movementFunction);
  }

  void ParticleFilter::sense(const Landmarks &measurement,
			     const Landmarks &landmarks)
  {
    // calculate weights
    auto weights = std::vector<double> {};
    auto weightFunction = [&measurement, &landmarks] (const Particle &p)
      { return measurementProbability(p, measurement, landmarks); };

    std::transform(std::cbegin(particles), std::cend(particles),
		   std::begin(weights), weightFunction);

    // resample

  }
}
