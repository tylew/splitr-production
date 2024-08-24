# Use a base image with cross-compilation tools and gcc
FROM balenalib/raspberry-pi-debian:latest

# Install development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    gcc-arm-linux-gnueabihf \
    libc6-dev \
    libbluetooth-dev \
    bluetooth \
    bluez \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /my_c_project

# Copy your source and header files into the Docker image
COPY src/* /my_c_project/src/
COPY include/* /my_c_project/include/

# Set the default command to compile the code
CMD ["make", "all"]
