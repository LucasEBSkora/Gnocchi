#include "LocationProvider.h"

namespace Gnocchi
{

  LocationProvider::LocationProvider(std::string filename) : fileName{filename}, m_location_col{0} {}

  void LocationProvider::increaseLocationCol(unsigned int loc)
  {
    m_location_col += loc;
  }

  unsigned int LocationProvider::getLocationCol() const
  {
    return m_location_col;
  }

  std::string *LocationProvider::getFileName()
  {
    return &fileName;
  }

  void LocationProvider::setFileName(std::string filename) {
    fileName = filename;
  }

  void LocationProvider::reset() {
    m_location_col = 0;
  }

}