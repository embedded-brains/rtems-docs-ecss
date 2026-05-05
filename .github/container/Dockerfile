# SPDX-License-Identifier: BSD-2-Clause

# Copyright (C) 2026 embedded brains GmbH & Co. KG

FROM ubuntu:24.04
COPY --from=ghcr.io/astral-sh/uv:0.11.9 /uv /uvx /bin/
COPY pyproject.toml uv.lock .
RUN <<EOF
set -eu
DEBIAN_FRONTEND=noninteractive TZ=Europe/Berlin apt-get -y update
DEBIAN_FRONTEND=noninteractive TZ=Europe/Berlin apt-get -qq install -y \
    binutils-multiarch \
    bison \
    build-essential \
    bzip2 \
    clang-tools \
    cmake \
    cppcheck \
    curl \
    expect \
    flex \
    g++ \
    gawk \
    gcc \
    git \
    git-lfs \
    gnutls-dev \
    graphviz \
    latexmk \
    libpython3-dev \
    libssl-dev \
    lzop \
    make \
    pdftk \
    pkg-config \
    python3 \
    python3-dev \
    python3-dateutil \
    python3-pip \
    python3-pykwalify \
    python3-setuptools \
    python3-venv \
    python3-yaml \
    python-dev-is-python3 \
    python-is-python3 \
    texinfo \
    texlive \
    texlive-fonts-extra \
    texlive-latex-extra \
    unzip \
    xz-utils
rm -rf /var/lib/apt/lists/*
cat >/etc/texmf/texmf.d/99local.cnf <<EOF_TEXMF
main_memory = 12000000
extra_mem_bot = 12000000
font_mem_size = 12000000
pool_size = 12000000
buf_size = 12000000
EOF_TEXMF
update-texmf
texhash
curl -fL -o doxygen-1.17.0.src.tar.gz https://github.com/doxygen/doxygen/releases/download/Release_1_17_0/doxygen-1.17.0.src.tar.gz
cat >files.sha256 <<EOF_SHA256
f05934ddce884a121981d94c16f274a12bfc7829e48943a7f9455bb255b0be40  /bin/uv
0a7c207b8eaf65d90c041a2c935628f0090e2977ddeb199e49dc74c09e1d7989  /bin/uvx
fa4c3dd78785abc11ccc992bc9c01e7a8c3120fe14b8a8dfd7cefa7014530814  doxygen-1.17.0.src.tar.gz
EOF_SHA256
sha256sum -c files.sha256
rm files.sha256
tar -xf doxygen-1.17.0.src.tar.gz
cmake -S doxygen-1.17.0 -B doxygen-1.17.0 -G "Unix Makefiles"
make -j $(nproc) -C doxygen-1.17.0
make -j $(nproc) -C doxygen-1.17.0 install
rm -rf doxygen-1.17.0 doxygen-1.17.0.src.tar.gz
doxygen --version
git config --global user.email "you@example.com"
git config --global user.name "Your Name"
uv sync --all-groups --cache-dir=/.cache/uv
EOF
