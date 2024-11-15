#!/bin/bash

# Output directory for the binary
BUILD_DIR="cmake-build-debug"

# Full path to the binary
BIN_PATH_CMAKE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/$BUILD_DIR"
BIN_PATH_GCC="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Check if cmake is installed
if command -v cmake &> /dev/null; then
    echo "CMake found, compiling with CMake..."

    # Create the build directory if needed
    mkdir -p "$BUILD_DIR"
    cd "$BUILD_DIR"

    # Run CMake to generate the project files and build the Doing target
    cmake .. 
    cmake --build . --target ~/.Doing

    cd ..
else
    echo "CMake not found, compiling with GCC..."

    # Compile directly with GCC
    gcc -o ~/.Doing src/main.c src/crud_functions.c -lsqlite3
fi

echo "Compilation completed!"

# Name of the shell configuration file
CONFIG_FILE=""

# Detect the user's shell
if [ -n "$ZSH_VERSION" ]; then
    CONFIG_FILE="$HOME/.zshrc"
elif [ -n "$BASH_VERSION" ]; then
    CONFIG_FILE="$HOME/.bashrc"
elif [ -n "$FISH_VERSION" ]; then
    CONFIG_FILE="$HOME/.config/fish/config.fish"
else
    echo "Unsupported shell. Please add $BIN_PATH_CMAKE and $BIN_PATH_GCC manually to the PATH."
    exit 1
fi

# Add the path to PATH in the shell configuration file, if not already present
if ! grep -q "$BIN_PATH" "$CONFIG_FILE"; then
    if [ "$CONFIG_FILE" = "$HOME/.config/fish/config.fish" ]; then
        # Configuration for Fish
        echo "set -Ux PATH \$PATH $BIN_PATH_CMAKE" >> "$CONFIG_FILE"
        echo "set -Ux PATH \$PATH $BIN_PATH_GCC" >> "$CONFIG_FILE"
    else
        # Configuration for Bash and Zsh
        echo "export PATH=\$PATH:$BIN_PATH_CMAKE" >> "$CONFIG_FILE"
        echo "export PATH=\$PATH:$BIN_PATH_GCC" >> "$CONFIG_FILE"
    fi
    echo "Path $BIN_PATH_CMAKE and $BIN_PATH_GCC added to $CONFIG_FILE."
else
    echo "Path $BIN_PATH_CMAKE and $BIN_PATH_GCC are already present in $CONFIG_FILE."
fi

# Instruct the user to reload the shell
echo "To apply the changes, run: source $CONFIG_FILE or restart the terminal."


