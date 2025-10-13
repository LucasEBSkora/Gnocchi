#include "LocationProvider.h"

namespace Gnocchi {

LocationProvider::LocationProvider(string filename)
    : fileName{filename}, m_location_col{0} {}

void LocationProvider::increaseLocationCol(unsigned int inc) {
  m_location_col += inc;
}

unsigned int LocationProvider::getLocationCol() const { return m_location_col; }

string *LocationProvider::getFileName() { return &fileName; }

void LocationProvider::setFileName(string filename) { fileName = filename; }

void LocationProvider::reset() { m_location_col = 0; }

} // namespace Gnocchi