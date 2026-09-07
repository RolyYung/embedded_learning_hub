#include <stdio.h>
#include "analyzer.h"

#ifndef BUILD_MODE
#define BUILD_MODE "unspecified"
#endif

int main(void)
{
    const char *lines[] = {
        "INFO boot completed",
        "WARN battery voltage is low",
        "ERROR sensor timeout",
        "INFO retry started",
        "ERROR sensor timeout"
    };
    LogSummary result = analyze_lines(lines, 5);

    printf("构建模式: %s\n", BUILD_MODE);
    printf("INFO=%u WARN=%u ERROR=%u\n",
           result.info_count, result.warning_count, result.error_count);
#ifdef ENABLE_TRACE
    puts("TRACE: 日志分析流程已启用");
#endif
    return 0;
}
