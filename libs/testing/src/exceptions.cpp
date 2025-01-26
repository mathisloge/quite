#include "quite/test/exceptions.hpp"
namespace quite::test
{
RemoteException::RemoteException(const Error &error)
    : std::runtime_error{error.message}
{}
} // namespace quite::test
