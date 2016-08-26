
#include "GaussianDistribution.h"

namespace Filter
{

  class KalmanFilter
  {
  public:
    static void sense(GaussianDistribution &belief,
		      const GaussianDistribution &measurement);
    static void act(GaussianDistribution &belief,
		    const GaussianDistribution movement);
  };

}
