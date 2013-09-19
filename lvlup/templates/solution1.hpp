#ifndef SOLUTION1_HPP_
# define SOLUTION1_HPP_

template <typename T>
struct Bar
{};

template <template <typename> class C, typename T>
struct Bar<C<T> >
{
  typedef T Type;
};

#endif
