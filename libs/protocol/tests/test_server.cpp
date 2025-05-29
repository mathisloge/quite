#include <thread>
#include <boost/ut.hpp>
#include <quite/proto/probe/server.hpp>
using namespace boost::ut;
using namespace std::literals::string_view_literals;

static suite<"protocol server"> _ = [] { // NOLINT
    "shutdown instant"_test = [] { quite::proto::Server server{"unix:///tmp/grpc_probe.sock"}; };
    "shutdown delayed"_test = [] {
        quite::proto::Server server{"unix:///tmp/grpc_probe.sock"};
        std::this_thread::sleep_for(std::chrono::seconds(2));
    };
};
