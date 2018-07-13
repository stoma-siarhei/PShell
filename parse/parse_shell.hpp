#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <string_view>
#include <filesystem>


namespace parse
{

using namespace std;
using namespace std::experimental::filesystem;

template <class _Type>
class ShellParam
{
	ShellParam()
	{
	}
};

template <class _Type>
class ShellParam<_Type**>
{
public:
	ShellParam(wchar_t** _ptr, int _count) : count(_count)
	{
		for (int i = 0; i < count; i++, _ptr++)
		{
			shell.push_back(wstring(*_ptr));
		}
	}

	ShellParam(char** _ptr, int _count) : count(_count)
	{
		for (int i = 0; i < count; i++, _ptr++)
		{
			string str(*_ptr);
			shell.push_back(wstring(str.begin(), str.end()));
		}
	}
protected:
	wstring& get()
	{
		if (shell_str.empty())
		{
			concat();
		}

		return shell_str;
	}

	const wstring get(const int _index) const
	{
		return shell[_index];
	}
private:
	void concat()
	{
		for_each(shell.begin(), shell.end(), [&](wstring_view str) { shell_str += str; shell_str += '\n'; });
	}
	int count;
	wstring shell_str;
	vector<wstring> shell;
};

struct equal_to
{
	bool operator()(const wstring& lhs, const wstring& rhs) const
	{
		return lhs == rhs;
	}
};

const array<wstring, 3> keys = { L"-m", L"-f", L"-arg" };

template <class _Type>
#ifdef _UNICODE
class SerializeParam : public ShellParam<wchar_t**>
#else
class SerializeParam : public ShellParam<char**>
#endif // _UNICODE
{
public:
#ifdef _UNICODE
	SerializeParam(_Type arg, int _count) : ShellParam<wchar_t**>::ShellParam(arg, _count)
#else
	SerializeParam(_Type arg, int _count) : ShellParam<char**>::ShellParam(arg, _count)
#endif // _UNICODE
	{
	}

	wstring& get_shell() 
	{
		return get();
	}
private:
	wstring path_exe;
	wstring path_module;
	wstring name_module;
	wstring name_function;
	array<wstring, 10> params;
};

} // parse
