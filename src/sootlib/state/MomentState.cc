#include "MomentState.h"

using namespace soot;
using namespace std;

size_t MomentState::getNumMoments() const {
    return moments.size();
}
void MomentState::resetMoments(size_t numMoments) {
    moments = vector<double>(numMoments, 0);
}
double MomentState::getMoment(size_t i) const {
    return moments.at(i);
}
void MomentState::setMoment(size_t i, double value) {
    moments.at(i) = value;
}
vector<double>& MomentState::getMoments() {
    return moments;
}
const vector<double>& MomentState::getMomentsConst() const {
    return moments;
}
