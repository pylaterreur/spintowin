#ifndef EMPTY_HPP_
# define EMPTY_HPP_

struct Empty
{};

template <template <typename> class Aspect>
struct AssemblyEmpty
{
  typedef Empty Business;
  typedef Aspect<AssemblyEmpty> Whole;
};

#endif	// !EMPTY_HPP_
