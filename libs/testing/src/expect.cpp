#include "quite/test/expect.hpp"

namespace quite::test
{

class RemoteObjectExpect : public IExpectBuilder
{
  public:
    RemoteObjectExpect(RemoteObject remote_object)
        : obj_{remote_object}
    {}

    bool to_have_screenshot() {

    };

  private:
    RemoteObject obj_;
};

std::unique_ptr<IExpectBuilder> expect(RemoteObject remote_object)
{
    return std::make_unique<RemoteObjectExpect>(remote_object);
}
} // namespace quite::test
