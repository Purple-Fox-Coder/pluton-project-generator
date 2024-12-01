#!/bin/bash

PROGRAM_NAME="ppg"

SOURCE_FILE="ppg.cpp"
EXECUTABLE_PATH="/usr/bin/$PROGRAM_NAME"
INITIAL_TEMPLATES_DIR="./templates"
USER_TEMPLATES_DIR="$HOME/ppg/"

if ! command -v g++ &> /dev/null; then
  echo "g++ could not be found.  Please install g++ to proceed."
  exit 1
fi

if ! command -v make &> /dev/null; then
  echo "make could not be found.  Please install make to proceed."
  exit 1
fi

echo "compiling $SOURCE_FILE..."
make

if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting..."
    exit 1
fi

echo "Installing $PROGRAM_NAME to /usr/bin..."
sudo mv "./bin/$PROGRAM_NAME" "$EXECUTABLE_PATH"

sudo chmod +x "$EXECUTABLE_PATH"

if command -v "$PROGRAM_NAME" &> /dev/null; then
    echo "$PROGRAM_NAME installed successfully!"
else
    echo "Installation failed."
    exit 1
fi

if [ -d "$INITIAL_TEMPLATES_DIR" ]; then
  echo "Found templates folder, moving to $USER_TEMPLATES_DIR..."

  mkdir -p "$USER_TEMPLATES_DIR"

  mv "$INITIAL_TEMPLATES_DIR" "$USER_TEMPLATES_DIR"

  if [ $? -eq 0 ]; then
    echo "Templates moved to $USER_TEMPLATES_DIR successfully."
  else
    echo "Failed to move templates folder."
    exit 1
  fi
else
  echo "Templates folder not found, creating $USER_TEMPLATES_DIR..."

  mkdir -p "$USER_TEMPLATES_DIR/templates"

  if [ $? -eq 0 ]; then
    echo "Created $USER_TEMPLATES_DIR successfully."
  else
    echo "Failed to create templates folder."
    exit 1
  fi
fi

echo "Installation complete!  You may need to restart your terminal."
