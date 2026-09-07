#ifndef DEVICE_H
#define DEVICE_H

typedef enum {
    DEVICE_OFF,
    DEVICE_READY,
    DEVICE_RUNNING
} DeviceState;

typedef struct {
    DeviceState state;
    unsigned int samples_processed;
} Device;

void device_init(Device *device);
int device_start(Device *device);
int device_process(Device *device, int sample);
void device_stop(Device *device);
const char *device_state_name(DeviceState state);

#endif
