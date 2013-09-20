#ifndef UTILITY_HPP_
# define UTILITY_HPP_

template <typename Aspect>
struct AspectIsLast
{
  typedef char yes[1];
  typedef char no[2];

  template <typename C>
  static yes& test(typename C::Super *);

  template <typename>
  static no& test(...);

  static const bool result = sizeof(test<Aspect>(0)) == sizeof(yes);
};

template <typename Chain, template <typename, typename...> class Aspect>
struct GetAspect;

template <template <typename, typename...> class FirstAspect, template <typename, typename...> class Aspect, typename First, typename ...Args>
struct GetAspect<FirstAspect<First, Args...>, Aspect>
{
  typedef typename GetAspect<First, Aspect>::Type Type;
};

template <template <typename, typename...> class Aspect, typename First, typename... Args>
struct GetAspect<Aspect<First, Args...>, Aspect>
{
  typedef Aspect<First> Type;
};

template <typename Chain>
struct GetNextChain;

template <template <typename, typename...> class Aspect, typename First, typename... Args>
struct GetNextChain<Aspect<First, Args...> >
{
  typedef First Type;
};

template <typename Chain>
struct GetPrevChain
{
private:
  template <typename T, bool notChain = !std::is_same<Chain, T>::value, bool Dummy = false>
  struct Helper;

  template <bool Dummy>
  struct Helper<Chain, false, Dummy>
  {
    typedef Chain Type;
  };

  template <template <typename, typename...> class Prev, typename ...Args, bool Dummy>
  struct Helper<Prev<Chain, Args...>, true, Dummy>
  {
    typedef Prev<Chain, Args...> Type;
  };

  template <template <typename, typename...> class Prev, typename Next, typename ...Args, bool Dummy>
  struct Helper<Prev<Next, Args...>, true, Dummy>
  {
    typedef typename Helper<Next>::Type Type;
  };

public:
  typedef typename Helper<typename Chain::Whole>::Type Type;
};


// template <typename Chain>
// struct GetPrevChain<Chain>::Helper<Chain>
// {
//   typedef Chain Type;
// };


// template <typename>
// struct GetUpperAspect;

// template <template <typename, typename...> class Aspect, typename Super, typename ...Args>
// struct GetUpperAspect<Aspect<Super, Args...> >
// {
//   typedef typename GetAspect<typename Super::Whole, Aspect<Super, Args...> >::Type Type;
// };


#endif	// !UTILITY_HPP_
