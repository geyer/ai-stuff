#include "GaussianDistribution.h"
#include <cmath>

namespace Filter
{
  GaussianDistribution normalizedProduct(const GaussianDistribution &lhs,
					 const GaussianDistribution &rhs)
  {
    GaussianDistribution result;
    const auto &s1 = lhs.standardDeviation;
    const auto &s2 = rhs.standardDeviation;

    auto square = [] (double x) { return std::pow(x, 2); };
    auto denominator = (square(s1) + square(s2));
    result.mean = ((square(s2) * lhs.mean + square(s1) * rhs.mean) /
		   denominator);
    result.standardDeviation = std::sqrt( (square(s1) * square(s2)) /
					  denominator );

    return result;
  }

  GaussianDistribution conv(const GaussianDistribution &lhs,
			    const GaussianDistribution &rhs)
  {
    GaussianDistribution result;
    auto square = [] (double x) { return std::pow(x, 2); };

    result.mean = lhs.mean + rhs.mean;
    result.standardDeviation =
      std::sqrt(square(lhs.standardDeviation) + square(rhs.standardDeviation));

    return result;
  }
}
