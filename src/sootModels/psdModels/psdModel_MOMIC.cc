#include "psdModel_MOMIC.h"
#include "extern/binomial/binomial.h"

using namespace std;
using namespace soot;

////////////////////////////////////////////////////////////////////////////////

 psdModel_MOMIC::psdModel_MOMIC(sourceTermStruct* sourceTerms, int nVar, nucleationMech N, growthMech G, oxidationMech X, coagulationMech C)
         : psdModel(sourceTerms, nVar, N, G, X, C) {

     if (nVar < 1)
         throw runtime_error("Invalid number of soot moments requested");

//    this->nMom = nVar;

     // initialize sourceTerms soot variable
     for (int i=0; i<nMom; i++)
         sourceTerms->sootSourceTerms.push_back(0);

     // note nucleation mech in case PAH is needed
     this->nucleationMechanism = N;
     this->coagulationMechanism = C;
     
}

////////////////////////////////////////////////////////////////////////////////

void psdModel_MOMIC::getSourceTermsImplementation(state& state, sourceTermStruct *sourceTerms) const {

    const size_t N = downselectIfNeeded(state, state.sootVar);

    //---------- get chemical rates

    double Jnuc = nuc->getNucleationSootRate(state);
    double Kgrw = grw->getGrowthSootRate(state);
    double Koxi = oxi->getOxidationSootRate(state);

    //---------- nucleation terms

    vector<double> Mnuc(nMom, 0);

    double m_nuc = state.cMin * gasSpMW.at(gasSp::C) / Na;
    for (size_t i = 0; i < N; i++)
        Mnuc.at(i) = pow(m_nuc, i) * Jnuc;

    //---------- PAH condensation terms

    vector<double> Mcnd(nMom, 0);

    if (nucleationMechanism == nucleationMech::PAH) {
        for (size_t i = 1; i < N; i++)
            Mcnd.at(i) = MOMICCoagulationRate(state, (int) i) * nuc->DIMER.nDimer * nuc->DIMER.mDimer * i;
    }

    //---------- growth terms

    vector<double> Mgrw(nMom, 0);

    const double Acoef = M_PI * pow(abs( 6 / M_PI / rhoSoot), 2.0 / 3);
    for (size_t i = 1; i < N; i++)
        Mgrw.at(i) = Kgrw * Acoef * i * MOMIC(i - 1.0 / 3, state.sootVar);

    //---------- oxidation terms

    vector<double> Moxi(nMom, 0);

    for (size_t i = 1; i < N; i++)
        Moxi.at(i) = Koxi * Acoef *  i * MOMIC(i - 1.0 / 3, state.sootVar);

    //---------- coagulation terms

    vector<double> Mcoa(nMom, 0);

    if (coagulationMechanism != coagulationMech::NONE) {
        for (size_t i = 0; i < N; i++)
            Mcoa.at(i) = MOMICCoagulationRate(state, i);
    }

    //---------- combine to make soot source terms

    for (size_t i = 0; i < nMom; i++)
        sourceTerms->sootSourceTerms.at(i) = (Mnuc.at(i) + Mcnd.at(i) + Mgrw.at(i) + Moxi.at(i) + Mcoa.at(i)) / state.rhoGas;

    //---------- get gas source terms

    map<gasSp, double> nucGasSrc = nuc->getNucleationGasRates(state, Mnuc[1]).gasSourceTerms;
    map<gasSp, double> grwGasSrc = grw->getGrowthGasRates(state, Mgrw[1]).gasSourceTerms;
    map<gasSp, double> oxiGasSrc = oxi->getOxidationGasRates(state, Moxi[1]).gasSourceTerms;
    // coagulation does not contribute to gas sources/sinks

    for (auto const& x : sourceTerms->gasSourceTerms) {
        gasSp sp = x.first;
        if (sp != gasSp::C)
            sourceTerms->gasSourceTerms.at(sp) = nucGasSrc.at(sp) + grwGasSrc.at(sp) + oxiGasSrc.at(sp);
    }

}

////////////////////////////////////////////////////////////////////////////////

size_t  psdModel_MOMIC::downselectIfNeeded(state& state, vector<double>& M) {

    // CHECK: M0 <= 0.0

     if (M[0] <= 0)
		return 0;

    // CHECK: M1 <= 0.0

    if (M[1] <= 0.0) {
        double M0 = 1.0;
        double sigL = 3.0;
        double mavg = 1.0E-21;
        M[1] = M0 * mavg * exp(0.5 * pow(sigL,2.0));     // estimate an M1 value based on M0 and lognormal distribution
        state.sootVar.at(1) = M.at(1);
    }

    // CHECK: all remaining moments <= 0.0

	size_t N = M.size();
	bool zeros = false;

	do {

	    zeros = false;                                      // reset flag

        for (int i=0; i<N; i++)
            if (M[i] <= 0.0) { zeros = true; N = N - 1; }   // if value <= 0.0 found, throw flag and downselect by one

	} while (N > 2 && zeros);                               // will not downselect below 2 moments

	return N;
}

////////////////////////////////////////////////////////////////////////////////


double  psdModel_MOMIC::f_grid(int x, int y, const vector<double>& M)
{
	// repeated values of MOMIC calculation
	const double M_Xn12  = MOMIC(x - 1.0  / 2, M);
	const double M_Yp16  = MOMIC(y + 1.0  / 6, M);
	const double M_Xn16  = MOMIC(x - 1.0  / 6, M);
	const double M_Yn16  = MOMIC(y - 1.0  / 6, M);
	const double M_Xp16  = MOMIC(x + 1.0  / 6, M);
	const double M_Yn12  = MOMIC(y - 1.0  / 2, M);
	const double M_Yp76  = MOMIC(y + 7.0  / 6, M);
	const double M_Yp56  = MOMIC(y + 5.0  / 6, M);
	const double M_Yp12  = MOMIC(y + 1.0  / 2, M);
	const double M_Xp12  = MOMIC(x + 1.0  / 2, M);
	const double M_Xp56  = MOMIC(x + 5.0  / 6, M);
	const double M_Xp76  = MOMIC(x + 7.0  / 6, M);
	const double M_Yp136 = MOMIC(y + 13.0 / 6, M);
	const double M_Yp116 = MOMIC(y + 11.0 / 6, M);
	const double M_Yp32  = MOMIC(y + 3.0  / 2, M);
	const double M_Xp32  = MOMIC(x + 3.0  / 2, M);
	const double M_Xp116 = MOMIC(x + 11.0 / 6, M);
	const double M_Xp136 = MOMIC(x + 13.0 / 6, M);
    const double M_Yp196 = MOMIC(y + 19.0 / 6, M);
    const double M_Yp176 = MOMIC(y + 17.0 / 6, M);
    const double M_Yp52  = MOMIC(y + 5.0  / 2, M);
    const double M_Xp52  = MOMIC(x + 5.0  / 2, M);
    const double M_Xp176 = MOMIC(x + 17.0 / 6, M);
    const double M_Xp196 = MOMIC(x + 19.0 / 6, M);

	const double f1_0 = M_Xn12 * M_Yp16 + 2 * M_Xn16 * M_Yn16 + M_Xp16 * M_Yn12;
	const double f1_1 = M_Xn12 * M_Yp76 + 2 * M_Xn16 * M_Yp56 + M_Xp16 * M_Yp12 +
                        M_Xp12 * M_Yp16 + 2 * M_Xp56 * M_Yn16 + M_Xp76 * M_Yn12;

	vector<double> temp_x;
	vector<double> temp_y;
	double value;

	if (y >= 4) {
		temp_x = {0, 1};
		temp_y = {log10(f1_0), log10(f1_1)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);
		return pow(10, value);
	}

	double f1_2 = M_Xn12 * M_Yp136 + 2 * M_Xn16 * M_Yp116 + M_Xp16 * M_Yp32 + 2 * M_Xp12  * M_Yp76 +
              4 * M_Xp56 * M_Yp56  + 2 * M_Xp76 * M_Yp12  + M_Xp32 * M_Yp16 + 2 * M_Xp116 * M_Yn16 + M_Xp136 * M_Yn12;

	if (y >= 3) {
		temp_x = {0, 1, 2};
		temp_y = {log10(f1_0), log10(f1_1), log10(f1_2)};

		value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

		return pow(10, value);
	}

    double f1_3 = M_Xn12 * M_Yp196 + 2 * M_Xn16 * M_Yp176 +    M_Xp16 * M_Yp52 + 3 * M_Xp12 * M_Yp136 +
              6 * M_Xp56 * M_Yp116 + 3 * M_Xp76 * M_Yp32 + 3 * M_Xp32 * M_Yp76 + 6 * M_Xp116 * M_Yp56 +
              3 * M_Xp136 * M_Yp12 +     M_Xp52 * M_Yp16 + 2 * M_Xp176 * M_Yn16 +    M_Xp196 * M_Yn12;

	temp_x = {0, 1, 2, 3};
	temp_y = {log10(f1_0), log10(f1_1), log10(f1_2), log10(f1_3)};

	value = lagrangeInterp(1.0 / 2, temp_x, temp_y);

	return pow(10, value);
}

////////////////////////////////////////////////////////////////////////////////

double psdModel_MOMIC::MOMICCoagulationRate(const state& state, size_t r){

    // M1 = 0.0 for coagulation by definition
	if (r == 1)
		return 0;

    //---------- Knudsen number calculation

	const double mu_1 = state.sootVar[1] / state.sootVar[2];
	const double d_g = pow(6 * kb * state.T / state.P / M_PI, 1.0 / 3);
	const double d_p = pow(6 * mu_1 / rhoSoot / M_PI, 1.0 / 3);
	const double lambda_g = kb * state.T / (pow(2, 0.5) * M_PI * pow(d_g, 2) * state.P);
	const double Kn = lambda_g / d_p;

    //---------- continuum regime
    
    double Rate_C;

    const double K_C = 2 * kb * state.T / (3 * state.muGas);
    const double K_Cprime = 1.257 * lambda_g * pow(M_PI * rhoSoot / 6, 1.0 / 3);

	if (r == 0) {
		Rate_C = -K_C * ( pow(state.sootVar[0], 2) + MOMIC(1.0 / 3, state.sootVar) * MOMIC(-1.0 / 3, state.sootVar) + 
                         K_Cprime * ( 3 * MOMIC(-1.0 / 3, state.sootVar) * state.sootVar[0] + 
                                         MOMIC( 2.0 / 3, state.sootVar) * MOMIC(1.0 / 3, state.sootVar) ) );
	}
	else {
		Rate_C = 0;
		for (size_t k = 0; k < r; k++) {
			if (k <= r - k)
				Rate_C += binomial_coefficient(r, k) * ( 2 * state.sootVar[k] * state.sootVar[r-k] + 
                          MOMIC(k + 1.0 / 3, state.sootVar) * MOMIC(r -  k - 1.0 / 3, state.sootVar) +
                          MOMIC(k - 1.0 / 3, state.sootVar) * MOMIC(r -  k + 1.0 / 3, state.sootVar) +
                          2 * K_Cprime * ( 2 * MOMIC(k - 1.0 / 3, state.sootVar) * state.sootVar[r-k] + 
                                           state.sootVar[k] * MOMIC(r -  k - 1.0 / 3, state.sootVar) +
                                           MOMIC(k - 2.0 / 3, state.sootVar) * MOMIC(r - k + 1.0 / 3, state.sootVar) ) );
		}
		Rate_C *= 0.5 * K_C;
	}

    //---------- free-molecular regime
    
	double Rate_F;
	
	const double K_f = 2.2 * pow(3 / (4 * M_PI * rhoSoot), 2.0 / 3) * pow(8 * M_PI * kb * state.T, 1.0 / 2);

	if (r == 0) {
		Rate_F = -0.5 * K_f * f_grid(0, 0, state.sootVar);
	}
	else {
		Rate_F = 0;
		for (size_t k = 1; k < r; k++) {
			if (k <= r - k)
				Rate_F += binomial_coefficient(r, k) * f_grid(k, r - k, state.sootVar);
		}
		Rate_F *= 0.5 * K_f;
	}

    //---------- return weighted average
    
	return Rate_F / (1.0 + 1 / Kn) + Rate_C / (1 + Kn);
	
}

////////////////////////////////////////////////////////////////////////////////

double psdModel_MOMIC::lagrangeInterp(double x_i, const vector<double>& x, const vector<double>& y)
{
	double y_i = 0;

	double L;
	for (size_t j = 0; j < x.size(); j++) {
		L = 1;
		for (size_t m = 0; m < x.size(); m++) {
			if (m != j) {
				L *= (x_i - x.at(m)) / (x.at(j) - x.at(m));
			}
		}
		y_i += y.at(j) * L;
	}

	return y_i;
}

////////////////////////////////////////////////////////////////////////////////

double psdModel_MOMIC::MOMIC(double p, const vector<double>& M)
{
	if (p == 0)
		return M.at(0);

	size_t size = M.size();
	if (p < 0 && M.size() != 2)
		size = 3;

	vector<double> log_mu(size, 0);
	vector<double> x(size, 0);

	for (size_t i = 0; i < size; i++) {
		log_mu.at(i) = log10(M.at(i) / M.at(0));
		x.at(i) =  i;
	}

	const double log_mu_p = lagrangeInterp(p, x, log_mu);

	return pow(10, log_mu_p) * M.at(0);
}