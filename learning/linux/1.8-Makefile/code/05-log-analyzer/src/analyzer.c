#include <string.h>
#include "analyzer.h"

LogSummary analyze_lines(const char *const lines[], unsigned int count)
{
    LogSummary summary = {0, 0, 0};
    unsigned int i;

    for (i = 0; i < count; ++i) {
        if (strstr(lines[i], "ERROR") != NULL) {
            ++summary.error_count;
        } else if (strstr(lines[i], "WARN") != NULL) {
            ++summary.warning_count;
        } else {
            ++summary.info_count;
        }
    }
    return summary;
}
