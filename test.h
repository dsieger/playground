#if defined _MSC_VER
#include <windows.h>
#include <psapi.h>
#endif

double square(double x);

double twice(double x);

#if defined _MSC_VER
size_t getSize();
#endif
