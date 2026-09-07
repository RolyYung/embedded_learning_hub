#include <assert.h>
#include <stdio.h>
#include "device.h"

int main(void)
{
    Device device;

    device_init(&device);
    assert(device.state == DEVICE_READY);
    assert(device_start(&device) == 0);
    assert(device_process(&device, 21) == 42);
    assert(device.samples_processed == 1);
    device_stop(&device);
    assert(device.state == DEVICE_OFF);
    puts("test_device: PASS");
    return 0;
}
