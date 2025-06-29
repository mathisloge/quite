#include <boost/ut.hpp>
using namespace boost::ut;
int main(int argc, const char **argv)
{
    boost::ut::detail::cfg::parse_arg_with_fallback(argc, argv);
}
