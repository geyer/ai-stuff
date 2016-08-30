#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_

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

#endif
