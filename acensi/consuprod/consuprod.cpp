#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <boost/thread.hpp>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "Assembly.hpp"

namespace thr
{
  using namespace boost;
}

namespace
{
// template <typename Base>
  struct iterator_base// : Base
{
  template <typename T>
  bool operator==(T&& t) const
  {
    return (false);
  }

  // template <typename T>
  // T& operator=(T&& t);

  // std:: operator=(T&& t)
  // {}
};
}

namespace Layers
{
template <typename Super>
struct Producer : Super
{
private:
  struct iterator : std::iterator<std::output_iterator_tag, typename Super::Business::value_type>, iterator_base
  {
    //    typedef typename Super::Business::value_type value_type;

    iterator operator++(int)
    {
      iterator prev = *this;
      ++*this;
      return (prev);
    }

    iterator operator++()
    {
      return (*this);
    }

    typename Super::Business::value_type &operator*()
      ;
    // {
    //   return ();
    // }

    const typename Super::Business::value_type &operator*() const
      ;
    // {
    //   return ();
    // }
  };

public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {}

    bool insert(typename Super::Business::value_type data)
    {
      
    }

    iterator produce_begin()
    {}
  };

};

template <typename Super>
struct Consumer : Super
{
private:
  struct iterator : std::iterator<std::input_iterator_tag, typename Super::Business::value_type>, iterator_base
  {
    typedef typename Super::Business::value_type value_type;

    iterator operator++(int)
    {
      iterator prev = *this;
      ++*this;
      return (prev);
    }

    iterator operator++()
    {
      return (*this);
    }

    typename Super::Business::value_type &operator*();

    // {
    //   return ();
    // }
  };

public:
  struct Business : Super::Business
  {
    template <typename... T>
    Business(T&&... t) : Super::Business(t...)
    {

    }

    typename Super::Business::value_type pop()
    {
      
    }

    iterator consume_begin()
    {}

    iterator end()
    {}
  };

};
}

template <typename T>
struct Queue
{
  typedef std::shared_ptr<T> value_type;

protected:
  void insert(value_type data)
  {
    buffer_[r_ & (Size - 1)] = data;
    i_ = (i_ + 1) & (Size - 1);
  }

  value_type pop()
  {
    value_type ret;

    ret = buffer_[i_];
    //    buffer_[i_] = value_type();
    r_ = (r_ + 1) & (Size - 1);
    return (ret);
  }

private:
  static const unsigned Size = 1 << 3;
  unsigned	i_, r_;
  value_type	buffer_[Size];
};

namespace 
{
  struct Consumer
  {
    template <typename Q>
    void operator()(Q& q) const
    {
      {
	// std::vector<std::string> q;
      // std::copy(q.consume_begin(), q.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
      }
    }

  };

  struct Producer
  {
    template <typename Q>
    void operator()(Q& q) const
    {
      static const char* const filename = "toto.txt";
      std::ifstream ifile(filename);
      auto begin = q.produce_begin();

      std::for_each(std::istream_iterator<std::string>(ifile), std::istream_iterator<std::string>(), [&begin](const std::string &input)
		    {
		      typename Q::value_type p(new std::string(input));
		      *begin = p;
		    }
		    );
      if (!ifile.eof())
	std::cerr << "problem with file " << filename << std::endl;
    }

  };
}

int main()
{
  typedef typename Assembly<Queue<std::string>,
		   Layers::Producer,
		   Layers::Consumer>::Whole::Business Queue;
  Queue queue = Queue();

  // should we use boost::thread_group?
  std::vector<thr::thread> consumers;
  std::vector<thr::thread> producers;

  // consumers.push_back(thr::thread(Consumer(), queue));
  producers.push_back(thr::thread(Producer(), queue));
  consumers.push_back(thr::thread(Consumer(), queue));

  // consumers[0].join();
  for (auto &&t : producers)
    t.join();
  for (auto &&t : consumers)
    t.join();
}
