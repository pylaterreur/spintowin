#include <vector>
#include <iostream>
#include <memory>
#include <string>
#include <boost/thread.hpp>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <atomic>

namespace
{
  struct iterator_base// : Base
{
  template <typename T>
  bool operator==(T&& t) const
  {
    return (false);
  }

  template <typename T>
  bool operator!=(T&& t) const
  {
    return (!(*this == std::forward<T>(t)));
  }



  // template <typename T>
  // T& operator=(T&& t);

  // std:: operator=(T&& t)
  // {}
};
}

#include "Assembly.hpp"
#include "Layers/Consumer.hpp"
#include "Layers/Producer.hpp"
#include "Layers/Control.hpp"
#include "Queue.hpp"

namespace thr
{
  using namespace boost;
}

namespace 
{
  struct Consumer
  {
    template <typename Q>
    void operator()(Q* const q) const
    {
      // std::vector<std::string> q;
      std::copy(std::move(q->consume_begin()), q->end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    }

  };

  struct Producer
  {
    const char* const filename_;

    // Producer(Producer&&) = default;

    Producer(const Producer& copy) : filename_(copy.filename_)
    {}

    Producer(const char * const filename = "toto.txt") : filename_(filename)
    {}

    template <typename Q>
    void operator()(Q* const q) const
    {
      std::ifstream ifile(filename_);
      auto begin = std::back_inserter(*q);

      std::for_each(std::istream_iterator<std::string>(ifile), std::istream_iterator<std::string>(), [&begin](const std::string &input)
		    {
		      typename Q::value_type p(new std::string(input));
		      *begin = p;
		    }
		    );
      if (!ifile.eof())
	std::cerr << "problem with file " << filename_ << std::endl;
    }

  };
}

int main()
{
  typedef typename Assembly<Queue<std::string>,
		   Layers::Control,
		   Layers::Producer,
		   Layers::Consumer>::Whole::Business Queue;
  Queue queue = Queue();

  // should we use boost::thread_group?
  std::vector<thr::thread> consumers;
  std::vector<thr::thread> producers;

  // consumers.push_back(thr::thread(Consumer(), &queue));
  producers.push_back(thr::thread(Producer(), &queue));
  consumers.push_back(thr::thread(Consumer(), &queue));

  // consumers[0].join();
  for (auto &&t : producers)
    t.join();
  for (auto &&t : consumers)
    t.join();
}
