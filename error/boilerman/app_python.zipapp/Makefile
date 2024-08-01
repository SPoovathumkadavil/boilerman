
Makeflags += --silent

HOME_DIR = $(HOME)
LOC_FILE = $(HOME_DIR)/.loc.json

define ReadLoc
$(shell node -p '\
    const getVal = (key = "", obj = {}) => {
          const currKey = key.split(".")[0];
          const val = obj[currKey];
          if(typeof val !== "object") return val;
          const nextKey = key.split(".").slice(1).join(".");
          return getVal(nextKey, val);
    }; \
		if (require("fs").existsSync("$(LOC_FILE)")) { \
    	getVal(`$(1)`.replace(" ", ""), require("$(LOC_FILE)")); \
		} else { \
			"error"; \
		} \
')
endef

# project dirs
SRC_DIR = src
BIN_DIR = bin
DEP_DIR = dependencies
CONF_DIR = config

APP = app

# if install or uninstall is called, check if the directories exist
ifneq ($(filter install uninstall, $(MAKECMDGOALS)),)
$(if $(eq $(call ReadLoc, "bin"), "error"), $(error "Please run 'make loc' first to create a .loc.json file in the home directory"))
endif

# system-wide dirs
HOME_DIR = $(HOME)
PATH_BIN_DIR = $(call ReadLoc, "bin")
PATH_DEP_DIR = $(call ReadLoc, "dependencies")
PATH_CONF_DIR = $(call ReadLoc, "config")

PYTHON = python3
PYFLAGS = -p "/opt/homebrew/bin/python3"

.PHONY: build
build: clean
	echo "building $(APP)..."
	mkdir -p $(BIN_DIR)
	$(PYTHON) -m zipapp $(PYFLAGS) $(SRC_DIR) -o $(BIN_DIR)/$(APP)
	chmod +x $(BIN_DIR)/$(APP)
	echo "done."

.PHONY: init
init:
	echo "initializing project..."
	mkdir -p $(BIN_DIR)
	mkdir -p $(DEP_DIR)
	mkdir -p $(CONF_DIR)
	echo "done."

.PHONY: clean
clean:
	echo "cleaning local bin directory..."
	rm -rf $(BIN_DIR)
	echo "done."

.PHONY: install
install: uninstall
	echo "cnstalling $(APP)..."
	mkdir -p $(PATH_BIN_DIR)
	mkdir -p $(PATH_DEP_DIR)
	mkdir -p $(PATH_CONF_DIR)'
	echo "copying files..."
	cp -r $(BIN_DIR)/$(APP) $(PATH_BIN_DIR) 2>/dev/null || :
	cp -r $(DEP_DIR)/* $(PATH_DEP_DIR) 2>/dev/null || :
	cp -r $(CONF_DIR)/* $(PATH_CONF_DIR) 2>/dev/null || :
	rmdir $(PATH_DEP_DIR) 2>/dev/null || :
	rmdir $(PATH_CONF_DIR) 2>/dev/null || :
	echo "done."

.PHONY: uninstall
uninstall:
	echo "uninstalling $(APP)..."
	rm $(PATH_BIN_DIR)/$(APP)
	rm -rf $(PATH_DEP_DIR)
	rm -rf $(PATH_CONF_DIR)
	echo "done."

.PHONY: help
help:
	help:
		@echo "Usage: make [target]"
		@echo ""
		@echo "Targets:"
		@echo "  build       - Compile the project"
		@echo "  clean       - Clean all object files"
		@echo "  install     - Install the project"
		@echo "  uninstall   - Uninstall the project"
		@echo "  help        - Display this help message"
		@echo "  loc         - Downloads loc-maker cli and uses it to create a .loc.json file in the home directory"

.PHONY: loc
loc:
	echo "downloading loc-maker..."
	curl -O https://github.com/SPoovathumkadavil/loc-maker/releases/download/release/loc-maker
	chmod +x loc-maker
	echo "creating .loc.json file..."
	./loc-maker -n dependencies=$(HOME)/dev/.dependencies bin=$(HOME)/dev/.bin config=$(HOME)/dev/.config scripts=$(HOME)/dev/.scripts workspace=$(HOME)/dev/.workspace
	echo "cleaning up..."
	rm loc-maker
	echo "done."
