#ifndef ANALYZER_H
#define ANALYZER_H

typedef struct {
    unsigned int info_count;
    unsigned int warning_count;
    unsigned int error_count;
} LogSummary;

LogSummary analyze_lines(const char *const lines[], unsigned int count);

#endif
