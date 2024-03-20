#ifndef __LOCATION_PROVIDER_H__
#define __LOCATION_PROVIDER_H__

#include <string>

namespace Gnocchi {
  class LocationProvider {
    public:

    LocationProvider(std::string filename);

        // Used internally by Scanner YY_USER_ACTION to update location indicator
    void increaseLocationCol(unsigned int loc);
    
    // Used to get last Scanner location. Used in error messages.
    unsigned int getLocationCol() const ;

    std::string* getFileName();
    void setFileName(std::string filename);
    void reset();
    private:
    std::string fileName;
    unsigned int m_location_col;
  };
}

#endif