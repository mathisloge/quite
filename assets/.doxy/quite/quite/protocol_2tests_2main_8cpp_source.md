

# File main.cpp

[**File List**](files.md) **>** [**libs**](dir_6719ab1f1f7655efc2fa43f7eb574fd1.md) **>** [**protocol**](dir_256d27db1e44b9b04d67f4c92d3fc698.md) **>** [**tests**](dir_0600a918fa506c296d39916ce5da6191.md) **>** [**main.cpp**](protocol_2tests_2main_8cpp.md)

[Go to the documentation of this file](protocol_2tests_2main_8cpp.md)


```C++
#include <boost/ut.hpp>
#include <quite/setup_logger.hpp>

int main(int argc, char *argv[])
{
    quite::setup_logger();
    return static_cast<int>(
        boost::ut::cfg<>.run({.report_errors = true, .argc = argc, .argv = const_cast<const char **>(argv)}));
}
```


