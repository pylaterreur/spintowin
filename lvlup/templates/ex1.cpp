#include <cassert>

#include "util.hpp"
#include "solution1.hpp"

template <typename T>
struct Foo
{};

int main()
{
  assert((SameType<Bar<Foo<int> >::Type, int>::value));
}
