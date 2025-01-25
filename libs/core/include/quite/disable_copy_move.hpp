#pragma once

#define QUITE_DISABLE_COPY(ClassName)                                                                                  \
    ClassName(const ClassName &) = delete;                                                                             \
    ClassName &operator=(const ClassName &) = delete;

#define QUITE_DISABLE_COPY_MOVE(ClassName)                                                                             \
    QUITE_DISABLE_COPY(ClassName)                                                                                      \
    ClassName(ClassName &&) = delete;                                                                                  \
    ClassName &operator=(ClassName &&) = delete;
