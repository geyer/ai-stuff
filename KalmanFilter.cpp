#include "KalmanFilter.h"

namespace Filter
{
  void KalmanFilter::sense(const GaussianDistribution &measurement)
  {
    belief.position = normalizedProduct(belief.position, measurement);
    static_assert(false, "Update velocity with position from measurement");
  }

  void KalmanFilter::act()
  {
    belief.position = conv(belief.position, belief.velocity);
  }

}
