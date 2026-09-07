#include "device.h"

void device_init(Device *device)
{
    device->state = DEVICE_READY;
    device->samples_processed = 0;
}

int device_start(Device *device)
{
    if (device->state != DEVICE_READY) {
        return -1;
    }
    device->state = DEVICE_RUNNING;
    return 0;
}

int device_process(Device *device, int sample)
{
    if (device->state != DEVICE_RUNNING || sample < 0) {
        return -1;
    }
    ++device->samples_processed;
    return sample * 2;
}

void device_stop(Device *device)
{
    device->state = DEVICE_OFF;
}

const char *device_state_name(DeviceState state)
{
    switch (state) {
    case DEVICE_OFF: return "OFF";
    case DEVICE_READY: return "READY";
    case DEVICE_RUNNING: return "RUNNING";
    default: return "UNKNOWN";
    }
}
