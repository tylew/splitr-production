#!/bin/bash

# Define the project directory
PROJECT_DIR="/path/to/my_c_project"

# Navigate to the project directory
cd $PROJECT_DIR

# Check if the project directory exists
if [ ! -d "$PROJECT_DIR" ]; then
    echo "Error: Project directory does not exist."
    exit 1
fi

# Pull the latest changes from the repository
echo "Pulling the latest changes from the Git repository..."
git pull origin main

# Check if git pull was successful
if [ $? -ne 0 ]; then
    echo "Failed to pull latest changes. Please check your Git configuration."
    exit 1
fi

# Build the project using the Makefile
echo "Building the project..."
make all

# Check if make was successful
if [ $? -ne 0 ]; then
    echo "Build failed. Please check the compilation errors."
    exit 1
fi

echo "Build completed successfully."
