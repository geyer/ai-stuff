#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_

#include "GaussianDistribution.h"
#include <armadillo>

namespace Filter
{
  // 1D filter
  class KalmanFilter
  {
  public:
    KalmanFilter();
    void sense(const arma::Col<double> &measurement,        // 1D vector
	       const arma::Mat<double> &measurement_noise); // 1x1 matrix
    void predict(const arma::Col<double> &motion_vector);   // 2D vector
  private:
    struct State
    {
      arma::Col<double> estimate;    // position and velocity
      arma::Mat<double> uncertainty; // positive definite matrix
    };
    State belief;
  };

}

#endif
