#include <memory>
#include <boost/thread.hpp>
#include <iostream>
#include <boost/chrono.hpp>

namespace thr
{
  using namespace boost;
}

static boost::shared_mutex m, m2;
static int data = 0;

template <typename T>
static void print(const T&t)
{
  boost::unique_lock<boost::shared_mutex> l(m2);  
  std::cout << t << std::endl;
}

static void writer()
{
  while (true)
    {
      {
	boost::unique_lock<boost::shared_mutex> l(m);
	++data;
      }
      thr::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }
}

static void reader()
{
  int copy;
  while (true)
    {
      {
	boost::shared_lock<boost::shared_mutex> l(m);
	copy = data;
      }
      print(copy);
      boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
    }
}

int main()
{
  std::vector<thr::thread> aT;
  for (int i = 0; i < 2; ++i)
    aT.emplace_back(&reader);
  for (int i = 0; i < 1; ++i)
    aT.emplace_back(&writer);
  for (auto && t : aT)
    t.join();
}
