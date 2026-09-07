#include <stdio.h>
#include "checksum.h"
#include "device.h"

int main(void)
{
    const unsigned char packet[] = {0x10, 0x20, 0x30, 0x40};
    const int samples[] = {10, 20, 30};
    Device device;
    unsigned int i;

    device_init(&device);
    printf("设备状态: %s\n", device_state_name(device.state));
    if (device_start(&device) != 0) {
        return 1;
    }
    for (i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i) {
        printf("样本 %d -> %d\n", samples[i], device_process(&device, samples[i]));
    }
    printf("校验和: 0x%02X\n", checksum_u8(packet, sizeof(packet)));
    device_stop(&device);
    printf("已处理: %u, 状态: %s\n",
           device.samples_processed, device_state_name(device.state));
    return 0;
}
