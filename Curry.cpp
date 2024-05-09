#include "functional"

template <typename... Args, typename Ret>
auto curry(const std::function<Ret(Args...)>& func);

template <typename Arg, typename... Args, typename Ret>
auto curryMulti(std::function<Ret(Arg, Args...)> func_)
{
	return [func = std::move(func_)](Arg arg)
	{
		std::function<Ret(Args...)> curried = [func,arg](Args... args)
		{
			return func(arg,std::forward<Args>(args)...);
		};
		return curry(std::move(curried));
	};
}

template <typename... Args, typename Ret>
auto curry(std::function<Ret(Args...)> func)
{
	if constexpr(sizeof...(Args) == 1)
	{
		return func;
	}
	else
	{
		return curryMulti(std::move(func));
	}
}