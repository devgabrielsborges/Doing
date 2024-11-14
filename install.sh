#!/bin/bash

# Get the directory path where install.sh is located, then append "/cmake-build-debug"
BIN_PATH="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/cmake-build-debug"

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
    echo "Unsupported shell. Please add $BIN_PATH manually to the PATH."
    exit 1
fi

# Add the path to PATH in the shell configuration file, if not already present
if ! grep -q "$BIN_PATH" "$CONFIG_FILE"; then
    if [ "$CONFIG_FILE" = "$HOME/.config/fish/config.fish" ]; then
        # Configuration for Fish
        echo "set -Ux PATH \$PATH $BIN_PATH" >> "$CONFIG_FILE"
    else
        # Configuration for Bash and Zsh
        echo "export PATH=\$PATH:$BIN_PATH" >> "$CONFIG_FILE"
    fi
    echo "Path $BIN_PATH added to $CONFIG_FILE."
else
    echo "Path $BIN_PATH is already present in $CONFIG_FILE."
fi

# Instruct the user to reload the shell
echo "To apply the changes, run: source $CONFIG_FILE or restart the terminal."

