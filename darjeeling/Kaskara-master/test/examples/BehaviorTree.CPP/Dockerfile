FROM ubuntu:22.04

RUN apt-get update \
 && apt-get install -y \
      build-essential \
      cmake \
      git \
      bear

ARG GIT_REVISION=095358f769b0232ae11874ae26a7e1968b3f837c
ARG GIT_URL=https://github.com/BehaviorTree/BehaviorTree.CPP
RUN git clone "${GIT_URL}" /workspace \
 && cd /workspace \
 && git checkout "${GIT_REVISION}"

WORKDIR /workspace

RUN mkdir build \
 && cd build \
 && cmake .. \
 && cd .. \
 && bear -- make -C build
