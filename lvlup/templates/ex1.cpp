#include <cassert>

#include "util.hpp"
#include "solution1.hpp"

template <typename T>
struct Foo
{};

int main()
{
  // Write a class Bar that extracts a T from a C<T> type, and typedef it into an internal public Type
  assert((SameType<Bar<Foo<int> >::Type, int>::value));
}
