CC = gcc
CFLAGS = -Iinclude -Wall -Werror
LDFLAGS =

SRC_DIR = src
BUILD_DIR = build

CFILES = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) acsh

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

acsh: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f acsh