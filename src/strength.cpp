#include "strength.hpp"
using std::tan;
using std::exp;
using std::min;
/*


*/
double getMaxShear(const double& p, const double& c, const double& phi)
{
	return c + p * tan(phi);
}

double getShear(const double& p, const double& c, const double& phi, const double& j, const double& k)
{
	auto tm = getMaxShear(p, c, phi);
	auto ts = 1.0 - exp(-j/k);
	return tm * ts;
}

double getStaticShear(const double& p, const double& mu, const double& j, const double& k)
{
	auto ts = 1.0 - exp(j/k);
	auto t_out = p * mu * ts;
	return t_out;
}

double getHarnischShear(const double& p, const double& mu, const double& c, const double& phi, const double& j, const double& k)
{
	auto ts = 1.0 - exp(-j/k);
	auto t1 = c * p * tan(phi);
	auto t2 = mu * p;
	auto t_out = min(t1, t2) * ts;
	return t_out;
}

double getJustinShear(const double& p, const double& mu, const double& c, const double& phi, const double& j, const double& k const double& kappa)
{
	auto ts = 1- exp(-j/k);
	auto t1 = c * p * tan(phi);
	auto t2 = mu * p;
	auto t_out = (kappa * t1 + (1 - kappa) * t2 ) * ts;
	return t_out;
}
