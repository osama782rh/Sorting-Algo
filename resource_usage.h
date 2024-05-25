#ifndef RESOURCE_USAGE_H
#define RESOURCE_USAGE_H

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif

typedef struct {
    const char *name;
    double time_spent;
    double user_cpu_time;
    double sys_cpu_time;
    size_t ram_usage;
    long invol_context_switches;
    long vol_context_switches;
} SortResult;

double get_time();

#ifdef _WIN32
void get_rusage_start(PROCESS_MEMORY_COUNTERS *mem_counters_start, FILETIME *kernelTime_start, FILETIME *userTime_start);
void get_rusage_end(PROCESS_MEMORY_COUNTERS *mem_counters_start, PROCESS_MEMORY_COUNTERS *mem_counters_end, FILETIME *kernelTime_start, FILETIME *userTime_start, FILETIME *kernelTime_end, FILETIME *userTime_end, SortResult *result);
#else
void get_rusage_start(struct rusage *usage_start, long *rss_start);
void get_rusage_end(struct rusage *usage_start, struct rusage *usage_end, long rss_start, SortResult *result);
#endif

char* custom_strdup(const char *s);
void test_sort_performance(void (*sort_func)(char *, int, int), const char *name, char *str, int size, SortResult *result);
void print_results(SortResult results[], int count);

#endif // RESOURCE_USAGE_H
