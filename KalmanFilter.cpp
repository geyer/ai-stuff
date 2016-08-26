#include "KalmanFilter.h"

namespace Filter
{
  void KalmanFilter::sense(GaussianDistribution &belief,
				  const GaussianDistribution &measurement)
  {
    belief = normalizedProduct(belief, measurement);
  }

  void KalmanFilter::act(GaussianDistribution &belief,
				const GaussianDistribution movement)
  {
    belief = conv(belief, movement);
  }

}
