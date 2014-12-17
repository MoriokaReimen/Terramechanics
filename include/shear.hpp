#include <cmath>
double getShearStrength(const double& p, const double& c, const double& phi);
double getShear(const double& p, const double& c, const double& phi, const double& j, const double&
                k);
double getStaticShear(const double& p, const double& mu, const double& j, const double& k);
double getHarnischShear(const double& p, const double& mu, const double& c, const double& phi, const
                        double& j, const double& k);
double getJustinShear(const double& p, const double& mu, const double& c, const double& phi, const
                      double& j, const double& k, const double& kappa);
