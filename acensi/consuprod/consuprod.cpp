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

  // template <typename T>
  // T& operator=(T&& t);

  // std:: operator=(T&& t)
  // {}
};
}

#include "Assembly.hpp"
#include "Layers.hpp"
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
    void operator()(Q& q) const
    {
      {
	// std::vector<std::string> q;
	//	std::copy(q.consume_begin(), q.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
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
