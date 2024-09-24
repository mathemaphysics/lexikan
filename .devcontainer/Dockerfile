FROM alpine:latest

ARG DEVUSER devuser
ARG DEVUID 1000
ARG DEVGID 1000

RUN apk add \
        g++ \
        gcc \
        gfortran \
        make \
        cmake \
        pkgconfig \
        git \
        lapack-dev \
        lua-dev \
        boost-dev \
        spdlog-dev \
        readline-dev \
        openssh \
        doxygen \
        sudo

RUN adduser --uid ${DEVUID} --disabled-password --gecos "" ${DEVUSER} \
    && echo "${DEVUSER} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${DEVUSER}
USER ${DEVUSER}