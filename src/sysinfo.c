#include "sysinfo.h"
#include <stdio.h>
#include <string.h>

static int read_loadavg(double *l1, double *l5, double *l15) {
  FILE *f = fopen("/proc/loadavg", "r");
  if (!f) return -1;
  int ok = fscanf(f, "%lf %lf %lf", l1, l5, l15);
  fclose(f);
  return (ok == 3) ? 0 : -1;
}

static int read_meminfo(long *total_kb, long *avail_kb) {
  FILE *f = fopen("/proc/meminfo", "r");
  if (!f) return -1;

  char key[64];
  long value = 0;
  char unit[32];

  *total_kb = -1;
  *avail_kb = -1;

  while (fscanf(f, "%63s %ld %31s", key, &value, unit) == 3) {
    if (strcmp(key, "MemTotal:") == 0) *total_kb = value;
    else if (strcmp(key, "MemAvailable:") == 0) *avail_kb = value;

    if (*total_kb > 0 && *avail_kb > 0) break;
  }

  fclose(f);
  return (*total_kb > 0 && *avail_kb > 0) ? 0 : -1;
}

int read_sysinfo(sysinfo_t *out) {
  if (!out) return -1;
  if (read_loadavg(&out->load1, &out->load5, &out->load15) != 0) return -1;
  if (read_meminfo(&out->mem_total_kb, &out->mem_available_kb) != 0) return -1;
  return 0;
}
