#ifndef STATE_H
#define STATE_H

#include "constants.h"

namespace soot {

    class state {

        //////////////// DATA MEMBERS /////////////////////

        public:

            std::map<gasSp, double>      gasFractions;
            std::map<pahSp, double>      pahFractions;
            std::vector<double>          sootVar;

            std::vector<double>          absc;
            std::vector<double>          wts;

            double T = 0;
            double P = 0;
            double rhoGas = 0;
            double MWGas = 0;
            double muGas = 0;
            double cMin = 100;          ///< soot min num carbon atoms

        //////////////// MEMBER FUNCTIONS /////////////////

        public:

            /** Sets the thermodynamic state based on user input
             *
             *      Only point of contact between users and the state class. User provides
             *      relevant data to be assigned to sootlib's internal state variables.
             *
             *      @param T_           temperature (K)
             *      @param P_           pressure (Pa)
             *      @param rhoGas_      density of gas mixture (kg/m3)
             *      @param MWGas_       gas mixture molecular weight (kg/kmol)
             *      @param yGas_        gas species mass fractions [H, H2, O, O2, OH, H2O, CO, C2H2]
             *      @param yPAH_        PAH species mass fractions [C10H8, C12H8, C12H10, C14H10, C16H10, C18H10]
             *      @param sootVar_     soot variable (moments or section values) values
             *      @param cMin_        minimum number of carbon atoms in a soot particle
             *
             *      IMPORTANT: gas and PAH species mass fractions MUST be provided in the order specified
             *      above within the yGas and yPAH vectors. Values must be non-negative. If a species is
             *      not represented or not present, DO NOT leave it out; instead, enter a mass fraction
             *      value of zero. If the user mechanism contains more than one species with the same
             *      molecular formula (C16H10 is a common culprit), enter the sum of the mass fractions
             *      for the applicable species. Any additional species information is not used by sootlib
             *      and will be ignored.
             */
            void setState(double T_, double P_, double rhoGas_, double muGas_, double MWGas_,
                          std::vector<double> yGas_, std::vector<double> yPAH_, std::vector<double> sootVar_, double cMin_ = 100);

            double getGasSpC(gasSp sp)  const { return rhoGas * gasFractions.at(sp) / gasSpMW.at(sp); };
            double getGasSpP(gasSp sp)  const { return gasFractions.at(sp) * MWGas / gasSpMW.at(sp) * P; };

            double getGasMeanFreePath() const { return muGas / rhoGas * sqrt(M_PI * MWGas / (2.0 * Rg * T)); };

            double get_pahSpC(pahSp sp) const { return rhoGas * pahFractions.at(sp) / pahSpMW.at(sp); };
            double get_pahSpP(pahSp sp) const { return pahFractions.at(sp) * MWGas / pahSpMW.at(sp) * P; };
            double get_pahSpN(pahSp sp) const { return rhoGas * pahFractions.at(sp) / pahSpMW.at(sp) * Na; };

            ////////////////////////////////////////////////////////////////////////////////
            /*! getParticleCollisionRate function
             *
             *      Returns the value of the collision rate function beta in m3/#*s. See
             *      Frenklach & Wang (1994) "Detailed mechanism and modeling of soot particle
             *      formation" in Soot Formation in Combustion, pp. 165-192.
             *
             *      @param m1               \input      first particle size (kg)
             *      @param m2               \input      second particle size (kg)
             *
             */
            double getParticleCollisionRate(double m1, double m2) const;

        //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

         state();                    // initializes variable and sets default values for maps
        ~state() = default;

    };
}

#endif //STATE_H