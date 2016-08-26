#include "KalmanFilter.h"

namespace Filter
{
  static void KalmanFilter::sense(GaussianDistribution &belief,
				  const GaussianDistribution &measurement)
  {
    belief = normalizedProduct(belief, measurement);
  }

  static void KalmanFilter::act(GaussianDistribution &belief,
				const GaussianDistribution movement)
  {
    belief = conv(belief, movement);
  }

}
