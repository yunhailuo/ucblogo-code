FROM ghcr.io/webassembly/wasi-sdk
RUN apt-get update \
    && apt-get install -y autoconf-archive binaryen curl git \
    && curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y \
    && . "$HOME/.cargo/env" \
    && cargo install wapm-to-webc --version=6.0.0-rc1
