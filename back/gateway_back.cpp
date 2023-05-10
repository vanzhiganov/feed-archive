#include <boost/python.hpp>

extern char const* get_latest(std::string feedId);
// extern char const* get_latest(char const* feedId);

BOOST_PYTHON_MODULE(gateway_back)
{
  using namespace boost::python;
  def("get_latest", get_latest);
}