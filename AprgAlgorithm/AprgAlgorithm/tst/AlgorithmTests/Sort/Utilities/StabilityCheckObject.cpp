#include "StabilityCheckObject.hpp"

using namespace std;

namespace alba {

namespace algorithm {

StabilityCheckObject::StabilityCheckObject() : m_visiblePart(0), m_notVisiblePart(0) {}

StabilityCheckObject::StabilityCheckObject(char const visiblePart, int const notVisiblePart)
    : m_visiblePart(visiblePart), m_notVisiblePart(notVisiblePart) {}

StabilityCheckObject::StabilityCheckObject(int const value)
    : m_visiblePart(static_cast<char>(value)), m_notVisiblePart(0) {}

bool StabilityCheckObject::operator==(StabilityCheckObject const& object) const {
    return m_visiblePart == object.m_visiblePart;
}

bool StabilityCheckObject::operator!=(StabilityCheckObject const& object) const { return !operator==(object); }

bool StabilityCheckObject::operator<(StabilityCheckObject const& object) const {
    return m_visiblePart < object.m_visiblePart;
}

StabilityCheckObject::operator int() const { return m_visiblePart; }

StabilityCheckObject StabilityCheckObject::operator+(StabilityCheckObject const& second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart + second.m_visiblePart), 0);
}

StabilityCheckObject StabilityCheckObject::operator-(StabilityCheckObject const& second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart - second.m_visiblePart), 0);
}

StabilityCheckObject StabilityCheckObject::operator*(StabilityCheckObject const& second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart * second.m_visiblePart), 0);
}

StabilityCheckObject StabilityCheckObject::operator/(StabilityCheckObject const& second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart / second.m_visiblePart), 0);
}

StabilityCheckObject StabilityCheckObject::operator+(int const second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart + second), m_notVisiblePart);
}
StabilityCheckObject StabilityCheckObject::operator-(int const second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart - second), m_notVisiblePart);
}

StabilityCheckObject StabilityCheckObject::operator*(int const second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart * second), m_notVisiblePart);
}

StabilityCheckObject StabilityCheckObject::operator/(int const second) const {
    return StabilityCheckObject(static_cast<char>(m_visiblePart / second), m_notVisiblePart);
}

double StabilityCheckObject::operator*(double const multiplier) const { return m_visiblePart * multiplier; }

char StabilityCheckObject::getVisiblePart() const { return m_visiblePart; }
int StabilityCheckObject::getNotVisiblePart() const { return m_notVisiblePart; }

double operator/(double const dividend, StabilityCheckObject const& divisor) {    return dividend / divisor.m_visiblePart;
}

bool areObjectsEqualOnVisibleAndNotVisiblePart(
    StabilityCheckObject const& object1, StabilityCheckObject const& object2) {
    return object1.m_visiblePart == object2.m_visiblePart && object1.m_notVisiblePart == object2.m_notVisiblePart;
}

ostream& operator<<(ostream& out, StabilityCheckObject const& object) {
    out << "(" << object.m_visiblePart << object.m_notVisiblePart << ")";
    return out;
}

}  // namespace algorithm

}  // namespace alba
