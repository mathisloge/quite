

# File runnable\_exe.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**manager**](dir_b048ed2415d89a3588bcd07e27f16f41.md) **>** [**tests**](dir_0da81ac3ea6d1987f7ba9a902aa51f1c.md) **>** [**runnable\_exe.cpp**](runnable__exe_8cpp.md)

[Go to the documentation of this file](runnable__exe_8cpp.md)


```C++
#include <cstdlib>
#include <CLI/App.hpp>

int main(int argc, char **argv)
{
    CLI::App app{"A simple test program"};
    argv = app.ensure_utf8(argv);

    int exit_code{EXIT_SUCCESS};
    app.add_option("--exit-code", exit_code, "The exit code to return")->envname("TEST_EXIT_CODE");

    CLI11_PARSE(app, argc, argv);

    return exit_code;
}
```


