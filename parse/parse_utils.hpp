#include <tuple>
#include <filesystem>


namespace parse::utils
{

template <class ... _Type>
auto concat(_Type& ... arg)
{
	return (arg + ...);
}

template <class ... _Type>
auto concat(const _Type& ... arg)
{
	return (arg + ...);
}

template <class _Type = std::wstring>
auto convert_to(_Type& arg)
{
	return arg;
}

template <class _Symbol, class ... _Type>
auto concat_s(_Symbol& symbol, _Type& ... arg)
{
	return (concat(arg, symbol) + ...);
}

template <class _Symbol, class ... _Type>
auto concat_s(const _Symbol& symbol, const _Type& ... arg)
{
	return (concat(arg, symbol) + ...);
}

template <class _Type, size_t N, class _Symbol>
inline auto concat_integral(std::array<_Type, N>& mass, _Symbol& symbol)
{
	std::wstring res;
	for_each(begin(mass), end(mass), [&](_Type& data) { res = concat(res, concat_s(symbol, convert_to(data))); });
	return res;
}

template <class _Type, class _Symbol>
inline auto concat_integral(std::vector<_Type>& mass, _Symbol& symbol)
{
	std::wstring res;
	for_each(begin(mass), end(mass), [&](_Type& data) { res = concat(res, concat_s(symbol, convert_to(data))); });
	return res;
}

struct equal_to
{
	bool operator()(const wstring& lhs, const wstring& rhs) const
	{
		return lhs == rhs;
	}
};

inline tuple<wstring, wstring> get_path_name(wstring_view wstr)
{
	using namespace std::experimental::filesystem;

	path _path = wstr.data();
	return std::make_tuple(_path.parent_path(), _path.filename());
}

}
