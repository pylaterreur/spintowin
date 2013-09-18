#ifndef LAYERS_CONTROL_HPP_
# define LAYERS_CONTROL_HPP_

# include <boost/atomic.hpp>

namespace Layers
{
template <typename Super>
struct Control : Super
{
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...),  r_(Super::Business::Size - 1), i_(0)
    {
      for (auto &&p : reader_end_)
	p = 0;
      for (auto && p : Super::Business::buffer_)
	{
	  //	  p = new std::string("lol");
	}
    }

  protected:
    int reader_end_[Super::Business::Size];
    unsigned min_r_;
    boost::atomic<unsigned> r_;
    boost::atomic<unsigned> i_;
    // boost::atomic<unsigned> _;

    unsigned increment_reader()
    {
      // wait if r_ + 1
      unsigned r = ++r_ % Super::Business::Size;
      while (min_i_ == r)
	{
	  unsigned i = i_;

	  
	}
    }

  private:
    template <typename T>
    static T increment_counter(T&& t)
    {
      return ((t + 1) % Super::Business::Size);
    }
  };
};
}

#endif
