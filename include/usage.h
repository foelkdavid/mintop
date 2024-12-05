#ifndef USAGE_H
#define USAGE_H

float getCpuUsage();
int getCpuTemp();
float * getLoadAvg();
float getRamUsage();
float getMemoryUsage();
int * getDiskUsage(const char * path);

#endif
