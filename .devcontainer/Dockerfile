FROM fedora:latest
ARG USERNAME=quiteuser
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN dnf -y install sudo awk doxygen gcc git cmake ninja-build gdb pre-commit mkdocs mkdocs-material python3-mypy python3-pytest python3-devel clang-tools-extra qt6-qtbase-devel qt6-qtbase-private-devel qt6-qtdeclarative-devel protobuf-devel pybind11-devel boost-devel grpc-devel && \
    dnf -y clean all

RUN groupadd --gid $USER_GID $USERNAME && \
    useradd --uid $USER_UID --gid $USER_GID -m $USERNAME && \
    echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

RUN pip install mkdoxy
