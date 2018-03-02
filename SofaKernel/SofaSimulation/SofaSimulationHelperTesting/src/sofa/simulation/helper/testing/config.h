#ifndef SOFA_SOFASIMULATIONHELPERTESTING
#define SOFA_SOFASIMULATIONHELPERTESTING

#include <sofa/config/sharedlibrary_defines.h>

#ifdef SOFA_BUILD_SOFASIMULATIONHELPERTESTING
#define SOFA_TARGET SofaSimulationHelperTesting
#define SOFA_SOFASIMULATIONHELPERTESTING_API SOFA_EXPORT_DYNAMIC_LIBRARY
#else
#define SOFA_SOFASIMULATIONHELPERTESTING_API SOFA_IMPORT_DYNAMIC_LIBRARY
#endif

#endif //

