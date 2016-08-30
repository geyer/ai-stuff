#ifndef _GAUSSIAN_DISTRIBUTION_H_
#define _GAUSSIAN_DISTRIBUTION_H_

namespace Filter
{
  struct GaussianDistribution
  {
    double mean;
    double standardDeviation;
  };

    GaussianDistribution normalizedProduct(const GaussianDistribution &lhs,
					   const GaussianDistribution &rhs);

    GaussianDistribution conv(const GaussianDistribution &lhs,
			      const GaussianDistribution &rhs);
}

#endif
