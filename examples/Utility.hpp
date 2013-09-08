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

template <typename Chain, typename Aspect, bool IsFinal = AspectIsLast<Aspect>::result >
struct GetAspect
{
  typedef typename GetAspect<typename Chain::Super, Aspect>::Type Type;
};

template <typename Chain, typename Aspect>
struct GetAspect<Chain, Aspect, false>
{
  typedef typename GetAspect<typename Chain::Super, Aspect>::Type Type;
};

template <typename SameAspect, bool IsFinal>
struct GetAspect<SameAspect, SameAspect, IsFinal>
{
  typedef SameAspect Type;
};

template <typename Aspect, bool IsFinal>
struct GetAspect<Aspect, typename Aspect::Super, IsFinal>
{
  typedef Aspect Type;
};

template <typename>
struct GetUpperAspect;

template <template <typename> class Aspect, typename Super>
struct GetUpperAspect<Aspect<Super> >
{
  typedef GetAspect<typename Super::Whole, Aspect<Super> > Type;
};


#endif	// !UTILITY_HPP_
