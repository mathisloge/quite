function(fetch_dependencies)
    set(FMT_INSTALL OFF)
    set(FMT_TEST OFF)
    FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        64db979e38ec644b1798e41610b28c8d2c8a2739
        FIND_PACKAGE_ARGS
    )

    FetchContent_Declare(
        quill
        GIT_REPOSITORY https://github.com/odygrd/quill.git
        GIT_TAG        v9.0.0
        FIND_PACKAGE_ARGS
    )

    FetchContent_Declare(
        cmakerc
        GIT_REPOSITORY https://github.com/vector-of-bool/cmrc
        GIT_TAG        952ffddba731fc110bd50409e8d2b8a06abbd237
        FIND_PACKAGE_ARGS
    )

    FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt
        GIT_TAG        v3.15.0
        FIND_PACKAGE_ARGS
    )

    FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11
        GIT_TAG        v2.5.0
        FIND_PACKAGE_ARGS
    )

    set(STDEXEC_BUILD_TESTS OFF)
    set(STDEXEC_BUILD_EXAMPLES OFF)
    FetchContent_Declare(
        stdexec
        GIT_REPOSITORY https://github.com/NVIDIA/stdexec.git
        GIT_TAG        954159ad82386b3564ea4125d9f4b7a68ccb912c
        FIND_PACKAGE_ARGS
    )

    set(ASIO_GRPC_INSTALL ON)
    FetchContent_Declare(
        asio-grpc
        GIT_REPOSITORY https://github.com/Tradias/asio-grpc
        GIT_TAG        v3.4.3
        FIND_PACKAGE_ARGS
    )

    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG        v3.12.0
        FIND_PACKAGE_ARGS
    )

    FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb
        GIT_TAG        f0569113c93ad095470c54bf34a17b36646bbbb5
    )

    FetchContent_MakeAvailable(fmt quill cmakerc entt cli11 stdexec asio-grpc nlohmann_json)
endfunction()
