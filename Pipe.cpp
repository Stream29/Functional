#include <functional>

template<typename Arg1,typename Ret1,typename Arg2,typename Ret2>
std::function<Ret2(Arg1)> pipe(std::function<Ret1(Arg1)> f1_,std::function<Ret2(Arg2)> f2_)
{
	return [f1 = std::move(f1_),f2 = std::move(f2_)]
	(Arg1 arg1)
	{
		return f2(f1(arg1));
	};
}

template<typename Arg1,typename Ret1,typename... Func>
auto pipe(std::function<Ret1(Arg1)> func1,std::function<Func>... func)
{
	return pipe(std::move(func1),pipe(func...));
}
