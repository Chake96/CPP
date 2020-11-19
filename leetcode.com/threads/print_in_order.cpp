#include <bits/stdc++.h>

class Foo{
	public:
		std::mutex mut;
		std::condition_variable cv;
		std::atomic<int> count{3};
		Foo() {
			this->count = 3;
		}

		void first() {
			std::unique_lock<std::mutex> lg(this->mut);
			this->cv.wait(lg, [this]{return count == 3;});
			// printFirst() outputs "first". Do not change or remove this line.
			this->count = 2;
			printFirst();
			this->cv.notify_all();
		}

		void second() {
			std::unique_lock<std::mutex> lg(this->mut);
			this->cv.wait(lg, [this]{return count == 2;});
			// printSecond() outputs "second". Do not change or remove this line.
			printSecond();
			this->count = 1;
			this->cv.notify_all();
		}

		void third() {
			std::unique_lock<std::mutex> lk(this->mut);
			this->cv.wait(lk, [this]{return count == 1;});
			// printThird() outputs "third". Do not change or remove this line.
			printThird();
			this->count = 0;
			this->cv.notify_all();
		}

		void printFirst(){
			std::puts("first");
		}

		void printSecond(){
			std::puts("second");
		}

		void printThird(){
			std::puts("third");
		}

};



int main(){
	Foo* foo = new Foo();
	std::thread t3(&Foo::third, foo);
	std::thread t2(&Foo::second, foo);

	std::thread t1(&Foo::first, foo);
	if(t1.joinable()){
		t1.join();
	}
	if(t2.joinable()){
		t2.join();
	}

	if (t3.joinable()){
		t3.join();
	}

}	
