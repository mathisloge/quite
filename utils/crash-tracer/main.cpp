#include <unistd.h>

#include <cstdio>
#include <iostream>

#include <cpptrace/cpptrace.hpp>

int main()
{
    cpptrace::object_trace trace;
    while (true)
    {
        cpptrace::safe_object_frame frame{};
        const std::size_t res = fread(&frame, sizeof(frame), 1, stdin);
        if (res == 0)
        {
            break;
        }
        if (res != 1)
        {
            std::cerr << "Oops, size mismatch " << res << " " << sizeof(frame) << std::endl;
            break;
        }
        trace.frames.push_back(frame.resolve());
    }
    trace.resolve().print();
}
