#include "process_application.hpp"
#include <iostream>
#include <spdlog/spdlog.h>
#include <uvw/pipe.h>
#include <uvw/process.h>

namespace quite
{
ProcessApplication::ProcessApplication(const std::string &path_to_application)
{
    auto loop = uvw::loop::get_default();
    uvw::process_handle::disable_stdio_inheritance(); // todo call in an init function

    process_ = loop->resource<uvw::process_handle>();
    out_pipe_ = loop->resource<uvw::pipe_handle>();

    process_->on<uvw::exit_event>([](const auto& event, const auto& handle) {
        spdlog::error("Process exited");
    });


    process_->stdio(*out_pipe_,
                    uvw::process_handle::stdio_flags::CREATE_PIPE | uvw::process_handle::stdio_flags::WRITABLE_PIPE |
                        uvw::process_handle::stdio_flags::READABLE_PIPE);
    process_->stdio(uvw::std_in, uvw::process_handle::stdio_flags::IGNORE_STREAM);
    process_->stdio(uvw::std_err, uvw::process_handle::stdio_flags::IGNORE_STREAM);
    process_->stdio(uvw::std_out, uvw::process_handle::stdio_flags::INHERIT_FD);

    out_pipe_->on<uvw::data_event>(
        [](const uvw::data_event &data, const uvw::pipe_handle &pipe) { std::cout << "Got data_event" << std::endl; });
    out_pipe_->on<uvw::listen_event>(
        [](const auto &data, const uvw::pipe_handle &pipe) { std::cout << "Got listen_event" << std::endl; });
    out_pipe_->on<uvw::write_event>(
        [](const auto &data, const uvw::pipe_handle &pipe) { std::cout << "Got write_event" << std::endl; });

    process_->spawn(path_to_application.c_str(), {});
}

ProcessApplication::~ProcessApplication() {
    out_pipe_->close();
    process_->close();
}
} // namespace quite
