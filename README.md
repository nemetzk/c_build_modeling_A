# c_build_modeling_A

pilot-c-tui/
├── Makefile
├── src/
│   ├── main.c
│   ├── sysinfo.c
│   └── sysinfo.h
├── include/
│   └── version.h        (GENERÁLT prebuild-ből)
└── scripts/
    ├── prebuild.sh

## Frontend demo

A simple sticky-board frontend demo is available under `web/`.

Open it directly in a browser:

```bash
xdg-open web/index.html
```

Or serve the project root and open `http://localhost:8000/web/index.html`:

```bash
python3 -m http.server 8000
```
