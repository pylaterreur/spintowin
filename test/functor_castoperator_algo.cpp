
#include <iostream>

#include <iterator>
#include <vector>
#include <functional>
#include <algorithm>

namespace
{
  template <typename T>
  struct increment
  {
    increment(T start) : counter_(start)
    {}

    T operator()()
    {
      return (++counter_);
    }

    operator T()
    {
      return (++counter_);
    }

  private:
    T counter_;
  };
}

int main()
{
  typedef std::vector<int> Type;

  Type v(10);
  std::transform(v.begin(), v.end(), v.begin(), std::bind(std::plus<Type::value_type>(), std::placeholders::_1, increment<Type::value_type>(0)));
  std::copy(v.begin(), v.end(), std::ostream_iterator<Type::value_type>(std::cout, "\n"));
}
