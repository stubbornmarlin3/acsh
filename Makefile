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

SED_INPLACE = $(shell uname | grep -q Darwin && echo "sed -i ''" || echo "sed -i")

all: $(BUILD_DIR) acsh

$(BUILD_DIR): 
	mkdir -p $(BUILD_DIR)

acsh: $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HFILES)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean install uninstall

clean:
	@rm -rf $(BUILD_DIR)
	@rm -f acsh
	@echo "Cleaned up files!"

install: all
	@cp acsh $(INSTALL_DIR)
	@grep -xF "$(INSTALL_DIR)/acsh" /etc/shells || (echo $(INSTALL_DIR)/acsh >> /etc/shells)
	@echo "Installed! : $(INSTALL_DIR)/acsh"

uninstall:
	@rm -f $(INSTALL_DIR)/acsh
	@$(SED_INPLACE) '\#$(INSTALL_DIR)/acsh#d' /etc/shells
	@echo "Uninstalled!"

