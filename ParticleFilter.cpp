#include "ParticleFilter.h"
#include <random>

namespace Filter
{
  double measurementProbability(const Particle& p, const Landmarks &measurement);

  ParticleFilter::ParticleFilter(std::size_t n)
    : particles(n)
  {
    auto generator = std::default_random_engine ();
    auto position_distribution =
      std::uniform_real_distribution<double> { -1.0, 1.0 };
    auto orientation_distribution =
      std::uniform_real_distribution<double> { 0.0, 2 * PI };

    auto particleGenerator =
      [&position_distribution, &orientation_distribution, &generator]()
      {
	return Particle { position_distribution(generator),
			  orientation_distribution(generator) };
      };

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
    auto weightFunction = [&measurement] (const Particle &p)
      { return measurementProbability(p, measurement); };

    std::transform(std::cbegin(particles), std::cend(particles),
		   std::begin(weights), weightFunction);

    // resample

  }
}
