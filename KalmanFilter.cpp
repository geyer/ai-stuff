#include "KalmanFilter.h"

namespace Filter
{
  KalmanFilter::KalmanFilter()
    : belief { arma::vec(2, arma::fill::zeros), arma::mat(2, 2, arma::fill::eye) }
  {
    belief.uncertainty *= 5.0;	// initial variance
  }

  // state transition matrix
  const static auto F = arma::mat { {1, 1},
				    {0, 1} };
  // measurment function
  const static auto H = arma::mat { {1, 0} };
  // identity matrix
  const static auto I = arma::mat(2, 2, arma::fill::eye);

  void KalmanFilter::sense(const arma::Col<double> &measurement,
			   const arma::Mat<double> &measurement_noise)
  {
    const auto &z = measurement;
    const auto &R = measurement_noise;
    auto &x = belief.estimate;
    auto &P = belief.uncertainty;

    const auto y = z - H * x;
    const auto S = H * P * trans(H) + R;
    const auto K = P * trans(H) * inv_sympd(S);
    x = x + K * y;
    P = (I - K * H) * P;
  }

  void KalmanFilter::predict(const arma::Col<double> &motion_vector)
  {
    auto &x = belief.estimate;
    const auto &u = motion_vector;
    x = F * x + motion_vector;

    auto &P = belief.uncertainty;
    P = F * P * trans(F);
  }

}
