#include "../include/usage.h"
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <unistd.h>
#include <stdio.h>

#define CPU_TEMP_PATH "/sys/class/thermal/thermal_zone0/temp"

float getCpuUsage() {
    FILE* file;
    unsigned long user, nice, system, idle, iowait, irq, softirq, steal;
    unsigned long prevUser, prevNice, prevSystem, prevIdle;
    unsigned long total, prevTotal;
    float cpuUsage;

    // open /proc/stat
    file = fopen("/proc/stat", "r");
    if (!file) {
        perror("Failed to open /proc/stat");
        return -1.0f;
    }

    // get first line (total usage)
    fscanf(file, "cpu %lu %lu %lu %lu %lu %lu %lu %lu",
           &prevUser, &prevNice, &prevSystem, &prevIdle,
           &iowait, &irq, &softirq, &steal);
    fclose(file);

    // sleep to calc diff between measurements
    usleep(250000);

    // Open /proc/stat again to read updated stats
    file = fopen("/proc/stat", "r");
    if (!file) {
        perror("Failed to open /proc/stat");
        return -1.0f;
    }

    // read first line (total usage) again
    fscanf(file, "cpu %lu %lu %lu %lu %lu %lu %lu %lu",
           &user, &nice, &system, &idle,
           &iowait, &irq, &softirq, &steal);
    fclose(file);

    // calc totals
    prevTotal = prevUser + prevNice + prevSystem + prevIdle + iowait + irq + softirq + steal;
    total = user + nice + system + idle + iowait + irq + softirq + steal;

    // calc diffs
    unsigned long totalDiff = total - prevTotal;
    unsigned long idleDiff = idle - prevIdle;

    // calc percentages
    cpuUsage = 100.0f / (float)totalDiff * (float)(totalDiff - idleDiff);

    return cpuUsage;
}



float* getLoadAvg() {
    static float loadAvg[3];
    struct sysinfo sysInfo;

    if (sysinfo(&sysInfo) == 0) {
        loadAvg[0] = (float)sysInfo.loads[0] / 65536.0f;
        loadAvg[1] = (float)sysInfo.loads[1] / 65536.0f;
        loadAvg[2] = (float)sysInfo.loads[2] / 65536.0f;
    } else {
        loadAvg[0] = loadAvg[1] = loadAvg[2] = -1.0f;
    }

    return loadAvg;
}


float getMemoryUsage() {
    static float percentUsed;
    struct sysinfo sysInfo;
    if (sysinfo(&sysInfo) == 0) {
        unsigned long totalRAM = sysInfo.totalram; // Total RAM in MB
        unsigned long freeRAM = sysInfo.freeram;   // Free RAM in MB
        unsigned long bufferRAM = sysInfo.bufferram;
        unsigned long availRAM = (totalRAM - freeRAM - bufferRAM);
        percentUsed = 100.0 / totalRAM * availRAM;
        return percentUsed;
    } else {
        percentUsed = -1.0f;
    }
    return percentUsed;
}


int * getDiskUsage(const char *path) {
    static int diskUsage[3];
    struct statvfs stat;
    if (statvfs(path, &stat) == 0) {


        unsigned long long totalBytes = stat.f_blocks * stat.f_frsize;
        unsigned long long freeBytes = (stat.f_bfree * stat.f_frsize);
        unsigned long usedBytes = totalBytes - freeBytes;

        int totalGB = totalBytes / (1024 * 1024 * 1024);
        int usedGB = usedBytes / (1024 *1024 * 1024);
        int percentUsed = (100 * usedBytes) / totalBytes;

        diskUsage[0] = totalGB;
        diskUsage[1] = usedGB;
        diskUsage[2] = percentUsed;

        //printf("  %.2f%%\n", percentUsed);
    } else {
        diskUsage[0] = diskUsage[1] = diskUsage[2] = -1;
    }
    return diskUsage;
}


int getCpuTemp() {
    FILE *fp;
    int tempMilliCelsius;


    fp = fopen(CPU_TEMP_PATH, "r");
    if (fp == NULL) {
        return -1;
    }

    // Read the temperature (in millidegrees Celsius)
    if (fscanf(fp, "%d", &tempMilliCelsius) != 1) {
        fclose(fp);
        return -1;
    }
    fclose(fp);

    // Convert millidegrees Celsius to degrees Celsius
    return tempMilliCelsius / 1000;
}











