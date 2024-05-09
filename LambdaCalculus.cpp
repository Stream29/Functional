#include <iostream>
#include <functional>

struct Lambda
{
	std::function<Lambda(Lambda)> func;

	Lambda(){}

	Lambda(auto func_):
			func(func_)
	{}

	Lambda operator()(Lambda l) const
	{
		return func(std::move(l));
	}
};


int main()
{
	Lambda base = [](Lambda arg){return arg;};
	Lambda test = [](Lambda arg){std::puts("test");return arg;};
	auto toInt = [=](Lambda n){int counter = 0;n([&](Lambda l){counter ++;return l;})(base);return counter;};

	Lambda zero = []([[maybe_unused]]Lambda f){return [](Lambda x){return x;};};
	Lambda successor = [](Lambda n){return [=](Lambda f){return [=](Lambda x){return f(n(f)(x));};};};

	Lambda one = successor(zero);
	Lambda two = successor(one);
	Lambda add = [=](Lambda a){return [=](Lambda b){return a(successor)(b);};};
	Lambda three = add(one)(two);

	Lambda multiply = [=](Lambda a){return [=](Lambda b){return [=](Lambda f){return a(b(f));};};};
	Lambda six = multiply(two)(three);

	Lambda pow = [=](Lambda x){return [=](Lambda n){return n(multiply(x))(one);};};
	// pow = lambda abf.a(mul b)(one)

	std::cout << toInt(pow(three)(three)) << std::endl;
	return 0;
}