
Makeflags += --silent

# project dirs
SRC_DIR = src
BIN_DIR = bin
DEP_DIR = dependencies
CONF_DIR = config

APP = app

# system-wide dirs
HOME_DIR = $(HOME)
PATH_BIN_DIR = $(HOME_DIR)/Documents/dev/.bin
PATH_DEP_DIR = $(HOME_DIR)/Documents/dev/.dependencies/$(APP)
PATH_CONF_DIR = $(HOME_DIR)/Documents/dev/.config/$(APP)

PYTHON = python3
PYFLAGS = -p "/opt/homebrew/bin/python3"

.PHONY: build
build:
	echo "Building $(APP)..."
	mkdir -p $(BIN_DIR)
	$(PYTHON) -m zipapp $(PYFLAGS) $(SRC_DIR) -o $(BIN_DIR)/$(APP)
	chmod +x $(BIN_DIR)/$(APP)
	echo "Done."

.PHONY: install
install:
	echo "Installing $(APP)..."
	mkdir -p $(PATH_BIN_DIR)
	mkdir -p $(PATH_DEP_DIR)
	mkdir -p $(PATH_CONF_DIR)
	cp -r $(BIN_DIR)/$(APP) $(PATH_BIN_DIR) 2>/dev/null || :
	cp -r $(DEP_DIR)/* $(PATH_DEP_DIR) 2>/dev/null || :
	cp -r $(CONF_DIR)/* $(PATH_CONF_DIR) 2>/dev/null || :
	if [ -z "$(ls -A $(PATH_DEP_DIR))" ]; then rmdir $(PATH_DEP_DIR); fi
	if [ -z "$(ls -A $(PATH_CONF_DIR))" ]; then rmdir $(PATH_CONF_DIR); fi
	echo "Done."

.PHONY: uninstall
uninstall:
	echo "Uninstalling $(APP)..."
	rm $(PATH_BIN_DIR)/$(APP)
	rm -rf $(PATH_DEP_DIR)
	rm -rf $(PATH_CONF_DIR)
	echo "Done."
