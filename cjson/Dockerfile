FROM debian:bookworm-slim
RUN apt-get update \
    && apt-get install -y \
        cmake \
        gcc \
        gcovr \
        libc6-dev \
        patch \
    && rm -rf /var/lib/apt/lists/*
COPY CMakeModules /CMakeModules