#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_

#include "GaussianDistribution.h"

namespace Filter
{

  class KalmanFilter
  {
  public:
    void sense(const GaussianDistribution &measurement);
    void act(); // should take time as an argument
  private:
    struct State
    {
      GaussianDistribution position;
      GaussianDistribution velocity;
      static_assert(false, "Use 2n-dimensional distribution for position and velocity");
    };
    State belief;
  };

}

#endif
