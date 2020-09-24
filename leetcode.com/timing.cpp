//a c++14 function timer, plans to expand to include testing of timer, and more timer types

#include <chrono>
#include <utility>
using namespace std::chrono;

template <typename F, typename... Args>
auto time_func(F&& f, Args&&... as) -> long{
    auto start = high_resolution_clock::now();
	f(std::forward<Args>(as)...);  // call the callback
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(stop - start).count();
	return duration;

}

