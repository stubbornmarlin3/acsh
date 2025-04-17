CC = gcc
CFLAGS = -Iinclude -Wall -Werror
LDFLAGS =

INSTALL_DIR = /usr/local/bin

SRC_DIR = src
BUILD_DIR = build
INCL_DIR = include

HFILES = $(wildcard $(INCL_DIR)/*.h)
CFILES = $(wildcard $(SRC_DIR)/*.c)
OFILES = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR) acsh

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

acsh: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f acsh

install: all
	cp acsh $(INSTALL_DIR)
	echo $(INSTALL_DIR)/acsh >> /etc/shells

