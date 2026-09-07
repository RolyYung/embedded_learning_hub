#include "sensor.h"

size_t sensor_read_samples(double buffer[], size_t capacity)
{
    static const double samples[] = {23.5, 24.1, 23.8, 24.0, 23.6};
    size_t count = sizeof(samples) / sizeof(samples[0]);
    size_t i;

    if (count > capacity) {
        count = capacity;
    }
    for (i = 0; i < count; ++i) {
        buffer[i] = samples[i];
    }
    return count;
}
