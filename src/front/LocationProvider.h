#pragma once

#include <string>

namespace Gnocchi {
using namespace std;

class LocationProvider {
public:
  LocationProvider(string filename);

  // Used internally by Scanner YY_USER_ACTION to update location indicator
  void increaseLocationCol(unsigned int inc);

  // Used to get last Scanner location. Used in error messages.
  unsigned int getLocationCol() const;

  string *getFileName();

  void setFileName(string filename);

  void reset();

private:
  string fileName;
  unsigned int m_location_col;
};
} // namespace Gnocchi