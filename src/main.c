#include <stdio.h>
#include "../include/usage.h"

int main() {
    float cpuUsage = getCpuUsage();
    int cpuTemp = getCpuTemp();
    float memoryUsage = getMemoryUsage();
    float * loadAvg = getLoadAvg();
    int * diskUsage = getDiskUsage("/");
    printf("{\n");
    printf("  \"cpu_usage_percent\": %.2f,\n", cpuUsage);
    printf("  \"cpu_temp_celsius\": %i,\n", cpuTemp);
    printf("  \"ram_usage_percent\": %.2f,\n", memoryUsage);
    printf("  \"load_average\": {\n");
    printf("    \"1min_percent\": %.2f,\n", loadAvg[0]);
    printf("    \"5min_percent\": %.2f,\n", loadAvg[1]);
    printf("    \"15min_percent\": %.2f\n", loadAvg[2]);
    printf("  \"disk\": {\n");
    printf("    \"rootfs_total_gb\": %i,\n", diskUsage[0]);
    printf("    \"rootfs_used_gb\": %i,\n", diskUsage[1]);
    printf("    \"rootfs_usage_percent\": %i\n", diskUsage[2]);
    printf("  }\n");
    printf("}\n");

    return 0;
}

