#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "sysinfo.h"
#include "version.h"

static long clamp_long(long v, long lo, long hi) {
  if (v < lo) return lo;
  if (v > hi) return hi;
  return v;
}

static void draw_ui(const sysinfo_t *si, int refresh_ms) {
  erase();

  mvprintw(0, 0, "%s | build: %s | git: %s", APP_NAME, BUILD_TIMESTAMP_UTC, GIT_HASH);
  mvhline(1, 0, ACS_HLINE, COLS);

  mvprintw(3, 2, "Load avg:  %.2f  %.2f  %.2f", si->load1, si->load5, si->load15);

  long used_kb = si->mem_total_kb - si->mem_available_kb;
  long used_pct = (si->mem_total_kb > 0) ? (used_kb * 100 / si->mem_total_kb) : 0;
  used_pct = clamp_long(used_pct, 0, 100);

  mvprintw(5, 2, "Mem: total %ld MB | used %ld MB (%ld%%) | avail %ld MB",
           si->mem_total_kb / 1024,
           used_kb / 1024,
           used_pct,
           si->mem_available_kb / 1024);

  mvprintw(7, 2, "Keys: q=quit | r=toggle refresh (250ms/1000ms)");
  mvprintw(8, 2, "Refresh: %d ms", refresh_ms);

  refresh();
}

int main(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  curs_set(0);

  int refresh_ms = 1000;

  while (1) {
    sysinfo_t si;
    if (read_sysinfo(&si) != 0) {
      erase();
      mvprintw(0, 0, "Failed to read /proc. Are you on Linux?");
      mvprintw(2, 0, "Press q to quit.");
      refresh();
    } else {
      draw_ui(&si, refresh_ms);
    }

    int ch = getch();
    if (ch == 'q' || ch == 'Q') break;
    if (ch == 'r' || ch == 'R') refresh_ms = (refresh_ms == 1000) ? 250 : 1000;

    usleep((useconds_t)refresh_ms * 1000);
  }

  endwin();
  return 0;
}
