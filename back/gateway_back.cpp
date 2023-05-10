#include <boost/python.hpp>
using namespace boost::python;

extern char const* get_latest(char const* feedId);

BOOST_PYTHON_MODULE(gateway_back)
{
  def("get_latest", get_latest);
}