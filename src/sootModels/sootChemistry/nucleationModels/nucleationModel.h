#ifndef NUCLEATIONMODEL_H
#define NUCLEATIONMODEL_H

#include "src/state.h"
#include "src/constants.h"

namespace soot {

    class nucleationModel {

    //////////////// DATA MEMBERS /////////////////////

    public:

        dimerStruct DIMER = dimerStruct();      // used for PAH nucleation only

        std::map<gasSp, double>   nucleationRxnRatios;
        std::map<pahSp, double>   nucleationPahRxnRates;

    //////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual double getNucleationSootRate(state &state) = 0;

        sourceTermStruct getNucleationGasRates(const state& state, const double &N1) const;  //TODO override for PAH nucleation

//        virtual void    getNucleationPahRates(state& state) const = 0;

    //////////////// CONSTRUCTOR FUNCTIONS ////////////

    public:

        nucleationModel();
        virtual ~nucleationModel() = default;

    };
}

#endif //NUCLEATIONMODEL_H