#!/bin/bash

# Colors for output
BLUE='\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
PURPLE='\033[0;35m'
NC='\033[0m'
BOLD='\033[1m'

# Clear screen
clear

# Print header
echo -e "${BLUE}${BOLD}╔════════════════════════════════════════════════════════════╗${NC}"
echo -e "${BLUE}${BOLD}║                                                            ║${NC}"
echo -e "${BLUE}${BOLD}║             Time Travelling File System (TTFS)             ║${NC}"
echo -e "${BLUE}${BOLD}║                                                            ║${NC}"
echo -e "${BLUE}${BOLD}╠════════════════════════════════════════════════════════════╣${NC}"
echo -e "${BLUE}${BOLD}║${NC} Author: Naman Goyal                    Entry: 2024EE30913  ${BLUE}${BOLD}║${NC}"
echo -e "${BLUE}${BOLD}║${NC} Course: COL106 - Data Structures       Semester: Fall 2025 ${BLUE}${BOLD}║${NC}"
echo -e "${BLUE}${BOLD}╚════════════════════════════════════════════════════════════╝${NC}"
echo

# Function to compile
compile() {
    echo -e "${YELLOW}Compiling Time Travelling File System...${NC}"
    mkdir -p build
    g++ -std=c++17 main.cpp -o build/tfs -Wall -Wextra -pedantic -O2
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Compilation successful!${NC}"
        return 0
    else
        echo -e "${RED}Compilation failed!${NC}"
        return 1
    fi
}

# Function to run
run() {
    if [ -f build/tfs ]; then
        echo -e "${YELLOW}Running TTFS...${NC}"
        echo
        ./build/tfs
    else
        echo -e "${RED}Error: Executable not found. Please compile first.${NC}"
        return 1
    fi
}

# Main menu
while true; do
    echo
    echo -e "${PURPLE}${BOLD}Please select an option:${NC}"
    echo -e "${PURPLE}1)${NC} Compile and Run"
    echo -e "${PURPLE}2)${NC} Compile Only"
    echo -e "${PURPLE}3)${NC} Run Existing Version"
    echo -e "${PURPLE}4)${NC} Read Documentation"
    echo -e "${PURPLE}5)${NC} Exit"
    echo
    read -p "Enter your choice (1-5): " choice
    echo

    case $choice in
        1)
            compile && run
            ;;
        2)
            compile
            ;;
        3)
            echo -e "${YELLOW}Available versions:${NC}"
            ls -1 Version_History/
            echo
            read -p "Enter version name to run: " version
            if [ -f "Version_History/$version" ]; then
                echo -e "${GREEN}Running version: $version${NC}"
                "./Version_History/$version"
            else
                echo -e "${RED}Error: Version not found${NC}"
            fi
            ;;
        4)
            # For now, opening main.cpp as placeholder for documentation
            if [ -x "$(command -v code)" ]; then
                code main.cpp
            else
                echo -e "${RED}Error: VS Code not found. Opening with default editor.${NC}"
                open main.cpp
            fi
            ;;
        5)
            echo -e "${GREEN}Thank you for using TTFS!${NC}"
            exit 0
            ;;
        *)
            echo -e "${RED}Invalid option. Please try again.${NC}"
            ;;
    esac
done