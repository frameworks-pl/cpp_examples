# Use the official Ubuntu image as the base image
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC

# Install required packages
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    git \
    lcov \
    g++ \
    gcc \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Install Google Test
#RUN apt-get update && \
#    apt-get install -y libgtest-dev && \
#    cd /usr/src/gtest && \
#    cmake CMakeLists.txt && \
#    make && \
#    cp *.a /usr/lib && \
#    rm -rf /var/lib/apt/lists/*