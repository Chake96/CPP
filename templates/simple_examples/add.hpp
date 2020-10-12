template<typename A, typename B>
auto add(const A& a, const B& b)->decltype(a+b){
	return a+b;
}


