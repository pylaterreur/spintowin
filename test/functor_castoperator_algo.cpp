
#include <iostream>

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
  using namespace std::placeholders;

  std::vector<int> v(10);
  std::transform(v.begin(), v.end(), v.begin(), std::bind(std::plus<int>(), _1, increment<int>(0)));
  std::for_each(v.begin(), v.end(), [](int i){ std::cout << i << std::endl; });
}
