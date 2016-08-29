
#include <vector>
#include <functional>

namespace Filter
{
  using Coordinates = double;
  using Orientation = double;
  using Landmarks = std::vector<Coordinates>;

  struct Particle
  {
    Coordinates position;
    Orientation orientation;
    double measurementNoise;
  };

  const static double PI = 3.14;

  class ParticleFilter
  {
  public:
    ParticleFilter(std::size_t numberOfParticles);

    void sense(const Landmarks &measurement, const Landmarks landmarks);
    void act(const std::function<Particle (const Particle&)> &movementFunction);

  private:
    void resample(const std::vector<double> &weights);

    std::vector<Particle> particles;
  };
}
