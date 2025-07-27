

# File asio\_config.hpp.in

[**File List**](files.md) **>** [**core**](dir_6f77a39b07c019ccd7492ea87272f732.md) **>** [**asio\_config.hpp.in**](asio__config_8hpp_8in.md)

[Go to the documentation of this file](asio__config_8hpp_8in.md)


```C++
#pragma once
#cmakedefine01 QUITE_USES_BOOST

#if QUITE_USES_BOOST
#  include <boost/asio.hpp>
#  include <boost/system/errc.hpp>
#  include <boost/system/error_code.hpp>
#  include <boost/system/system_error.hpp>
#  define QUITE_ASIO_NAMESPACE boost::asio
#else
#  include <system_error>
#  include <asio.hpp>
#  define QUITE_ASIO_NAMESPACE asio
#endif

namespace quite {
#if QUITE_USES_BOOST
  namespace asio_impl = ::boost::asio;
  using error_code = ::boost::system::error_code;
  using error_condition = ::boost::system::error_condition;
  namespace errc = ::boost::system::errc;
  using system_error = ::boost::system::system_error;
#else
  namespace asio_impl = ::asio;
  using error_code = std::error_code;
  using error_condition = std::error_condition;
  using errc = std::errc;
  using system_error = std::system_error;
#endif
}
```


