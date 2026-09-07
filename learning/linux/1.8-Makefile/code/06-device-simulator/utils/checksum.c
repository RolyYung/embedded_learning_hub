#include "checksum.h"

unsigned int checksum_u8(const unsigned char data[], size_t length)
{
    unsigned int value = 0;
    size_t i;

    for (i = 0; i < length; ++i) {
        value = (value + data[i]) & 0xffU;
    }
    return value;
}
