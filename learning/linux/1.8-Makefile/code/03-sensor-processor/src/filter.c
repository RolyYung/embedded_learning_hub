#include "filter.h"

double filter_average(const double values[], size_t count)
{
    double sum = 0.0;
    size_t i;

    for (i = 0; i < count; ++i) {
        sum += values[i];
    }
    return count == 0 ? 0.0 : sum / (double)count;
}
