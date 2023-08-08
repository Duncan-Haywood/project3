#!/bin/bash

# Compile the program
g++ -std=c++17 main.cpp -o grocery

# Check for compile errors
if [ $? -ne 0 ]; then
    echo "Error compiling program"
    exit 1
fi

# Run the program
./grocery

# Check for runtime errors
if [ $? -ne 0 ]; then
    echo "Error running program"
    exit 1
fi

# Cleanup
rm grocery

echo "Program executed successfully"