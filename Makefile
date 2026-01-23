APP := pilot-c-tui
BUILD_DIR := build
SRC_DIR := src
INC_DIR := include
SCRIPTS := scripts

CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2 -g
CFLAGS += -I$(INC_DIR)
CFLAGS += -IThirdParty/uthash
LDFLAGS :=
LDLIBS :=

NCURSES_CFLAGS := $(shell pkg-config --cflags ncurses 2>/dev/null)
NCURSES_LIBS   := $(shell pkg-config --libs ncurses 2>/dev/null)

CFLAGS += $(NCURSES_CFLAGS)
LDLIBS += $(NCURSES_LIBS)

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

BIN := $(BUILD_DIR)/$(APP)

.PHONY: all clean prebuild postbuild run

all: prebuild $(BIN) postbuild

prebuild:
	@$(SCRIPTS)/prebuild.sh

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

postbuild: $(BIN)
	@$(SCRIPTS)/postbuild.sh "$(BIN)"

run: all
	@$(BIN)

clean:
	rm -rf $(BUILD_DIR) $(INC_DIR)/version.h
