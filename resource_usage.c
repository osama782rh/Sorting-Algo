#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif
#include "resource_usage.h"

double get_time() {
#ifdef _WIN32
    LARGE_INTEGER frequency;
    LARGE_INTEGER t;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&t);
    return (double)t.QuadPart / frequency.QuadPart;
#else
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + t.tv_usec / 1000000.0;
#endif
}

#ifdef _WIN32
void get_rusage_start(PROCESS_MEMORY_COUNTERS *mem_counters_start, FILETIME *kernelTime_start, FILETIME *userTime_start) {
    GetProcessMemoryInfo(GetCurrentProcess(), mem_counters_start, sizeof(*mem_counters_start));
    FILETIME createTime, exitTime;
    GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, kernelTime_start, userTime_start);
}

void get_rusage_end(PROCESS_MEMORY_COUNTERS *mem_counters_start, PROCESS_MEMORY_COUNTERS *mem_counters_end, FILETIME *kernelTime_start, FILETIME *userTime_start, FILETIME *kernelTime_end, FILETIME *userTime_end, SortResult *result) {
    GetProcessMemoryInfo(GetCurrentProcess(), mem_counters_end, sizeof(*mem_counters_end));
    FILETIME createTime, exitTime;
    GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, kernelTime_end, userTime_end);

    ULARGE_INTEGER kTime_start, uTime_start, kTime_end, uTime_end;
    kTime_start.LowPart = kernelTime_start->dwLowDateTime;
    kTime_start.HighPart = kernelTime_start->dwHighDateTime;
    uTime_start.LowPart = userTime_start->dwLowDateTime;
    uTime_start.HighPart = userTime_start->dwHighDateTime;
    kTime_end.LowPart = kernelTime_end->dwLowDateTime;
    kTime_end.HighPart = kernelTime_end->dwHighDateTime;
    uTime_end.LowPart = userTime_end->dwLowDateTime;
    uTime_end.HighPart = userTime_end->dwHighDateTime;

    result->user_cpu_time = (double)(uTime_end.QuadPart - uTime_start.QuadPart) / 10000000.0;
    result->sys_cpu_time = (double)(kTime_end.QuadPart - kTime_start.QuadPart) / 10000000.0;
    result->ram_usage = mem_counters_end->WorkingSetSize / 1024; // Conversion to KB
    result->invol_context_switches = 0;
    result->vol_context_switches = 0;
}
#else
void get_rusage_start(struct rusage *usage_start, long *rss_start) {
    getrusage(RUSAGE_SELF, usage_start);
    *rss_start = usage_start->ru_maxrss;
}

void get_rusage_end(struct rusage *usage_start, struct rusage *usage_end, long rss_start, SortResult *result) {
    getrusage(RUSAGE_SELF, usage_end);

    result->user_cpu_time = (usage_end->ru_utime.tv_sec - usage_start->ru_utime.tv_sec) + 
                            (usage_end->ru_utime.tv_usec - usage_start->ru_utime.tv_usec) / 1000000.0;
    result->sys_cpu_time = (usage_end->ru_stime.tv_sec - usage_start->ru_stime.tv_sec) + 
                           (usage_end->ru_stime.tv_usec - usage_start->ru_stime.tv_usec) / 1000000.0;
    result->ram_usage = usage_end->ru_maxrss - rss_start; // RAM usage in kilobytes
    result->invol_context_switches = usage_end->ru_nivcsw - usage_start->ru_nivcsw;
    result->vol_context_switches = usage_end->ru_nvcsw - usage_start->ru_nvcsw;
}
#endif

char* custom_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *dup = malloc(len);
    if (dup) {
        strcpy(dup, s);
    }
    return dup;
}

void test_sort_performance(void (*sort_func)(char *, int, int), const char *name, char *str, int size, SortResult *result) {
    char *copy = custom_strdup(str); 
    double start_time, end_time;

#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS mem_counters_start, mem_counters_end;
    FILETIME kernelTime_start, userTime_start, kernelTime_end, userTime_end;
    get_rusage_start(&mem_counters_start, &kernelTime_start, &userTime_start);
#else
    struct rusage usage_start, usage_end;
    long rss_start;
    get_rusage_start(&usage_start, &rss_start);
#endif

    start_time = get_time();

    sort_func(copy, 0, size - 1);

    end_time = get_time();

#ifdef _WIN32
    get_rusage_end(&mem_counters_start, &mem_counters_end, &kernelTime_start, &userTime_start, &kernelTime_end, &userTime_end, result);
#else
    get_rusage_end(&usage_start, &usage_end, rss_start, result);
#endif

    result->name = name;
    result->time_spent = end_time - start_time;

    free(copy);
}

void print_results(SortResult results[], int count) {
    printf("%-15s %-15s %-15s %-15s %-15s %-15s %-15s\n", 
           "Algorithm", "Time Spent (s)", "User CPU (s)", "Sys CPU (s)", "RAM Usage (KB)", "Invol CS", "Vol CS");
    for (int i = 0; i < count; i++) {
        printf("%-15s %-15.6f %-15.6f %-15.6f %-15zu %-15ld %-15ld\n", 
               results[i].name, results[i].time_spent, results[i].user_cpu_time, 
               results[i].sys_cpu_time, results[i].ram_usage, results[i].invol_context_switches, 
               results[i].vol_context_switches);
    }
}
