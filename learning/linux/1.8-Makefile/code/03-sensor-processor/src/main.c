#include "display.h"
#include "filter.h"
#include "sensor.h"

int main(void)
{
    double samples[16];
    size_t count = sensor_read_samples(samples, 16);

    display_result(filter_average(samples, count), (unsigned int)count);
    return 0;
}
