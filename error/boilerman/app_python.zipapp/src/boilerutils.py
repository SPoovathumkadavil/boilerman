import os
import json

def get_home_dir():
    return os.path.expanduser("~")


APP_NAME = "app"

HOME_DIR = get_home_dir()
LOC_FILE = os.path.join(HOME_DIR, ".loc.json")
DEP_DIR = "dependencies"
CONF_DIR = "config"
if os.path.exists(LOC_FILE):
    with open(LOC_FILE, "r") as f:
        loc = json.load(f)
        DEP_DIR = loc.get("dependencies", DEP_DIR)
        CONF_DIR = loc.get("config", CONF_DIR)
else:
    print("No .loc.json file found in home directory. Using test values.")
