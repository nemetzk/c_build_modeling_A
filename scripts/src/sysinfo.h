#pragma once
#include <stddef.h>

typedef struct {
  double load1, load5, load15;
  long mem_total_kb;
  long mem_available_kb;
} sysinfo_t;

int read_sysinfo(sysinfo_t *out);
