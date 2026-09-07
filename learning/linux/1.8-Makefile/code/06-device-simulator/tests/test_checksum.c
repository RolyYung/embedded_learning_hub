#include <assert.h>
#include <stdio.h>
#include "checksum.h"

int main(void)
{
    const unsigned char data[] = {1, 2, 3, 250};

    assert(checksum_u8(data, sizeof(data)) == 0U);
    assert(checksum_u8(data, 0) == 0U);
    puts("test_checksum: PASS");
    return 0;
}
