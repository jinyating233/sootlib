#include "sootModels/sootChemistry/coagulationModels/coagulationModel_FRENK.h"
#include "constants.h"

using namespace std;
using namespace soot;

double coagulationModel_FRENK::getCoagulationSootRate(const state& state,
                                                      double m1,
                                                      double m2) const {

    if (m1 == 0 || m2 == 0)
        return 0;

    double Dp1 = pow(6 * abs(m1) / M_PI / rhoSoot, 1.0 / 3);
    double Dp2 = pow(6 * abs(m2) / M_PI / rhoSoot, 1.0 / 3);

    //------------ free molecular rate
    double m12 = abs(m1 * m2 / (m1 + m2));
    double beta_12_FM = eps_c * sqrt(M_PI * kb * state.T * 0.5 / m12) * pow(Dp1 + Dp2, 2);  // Eq. 10.18

    //------------ continuum rate
    double Kn1 = 2 * state.getGasMeanFreePath() / Dp1;
    double Kn2 = 2 * state.getGasMeanFreePath() / Dp2;

    double Cc1 = 1 + Kn1 * (1.257 + 0.4 * exp(-1.1 / Kn1));   // Seinfeld p. 372 eq. 9.34. This is for air at 298 K, 1 atm
    double Cc2 = 1 + Kn2 * (1.257 + 0.4 * exp(-1.1 / Kn2));   // for D<<mfp_g, Cc = 1 + 1.657*Kn; Seinfeld p. 380: 10% error at Kn=1, 0% at Kn=0.01, 100

    double beta_12_C = 2 * kb * state.T / (3 * state.muGas) * (Cc1 / Dp1 + Cc2 / Dp1) * (Dp1 + Dp2);

    //------------ return harmonic mean
    return beta_12_FM * beta_12_C / (beta_12_FM + beta_12_C);

}
