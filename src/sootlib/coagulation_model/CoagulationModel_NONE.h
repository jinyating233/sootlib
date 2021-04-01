#ifndef COAGULATIONMODEL_NONE_H
#define COAGULATIONMODEL_NONE_H

#include "sootlib/coagulation_model/CoagulationModel.h"

namespace soot {
class CoagulationModel_NONE : public CoagulationModel {
public:
    [[nodiscard]] double getCoagulationRate(const InputState& state, double m1, double m2) const override {
        return 0;
    }
    [[nodiscard]] CoagulationMechanism getMechanism() const override {
        return CoagulationMechanism::NONE;
    }

    ~CoagulationModel_NONE() override = default;
};
}

#endif //COAGULATIONMODEL_NONE_H
