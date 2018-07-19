#include <string>
#include <array>
#include <vector>
#include <tuple>
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

	int get_count()
	{
		return count;
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

tuple<wstring, wstring> get_path_name(wstring_view wstr)
{
	path _path = wstr.data();
	return std::make_tuple(_path.parent_path(), _path.filename());
}

const array<wstring, 3> keys = { L"-m", L"-f", L"-a" };

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
		if (!serialize())
		{
			throw SerializeParamExcept(get(), path_exe);
		}
	}

	wstring& get_shell() 
	{
		return get();
	}
protected:
	bool serialize()
	{
		for (int i = 0, _size = get_count(); i < _size; i++)
		{
			wstring wstr = get(i);
			if (i == 0) 
			{
				tie(path_exe, name_exe) = get_path_name(wstr);
			}
			else
			{
				static int _command;
				if (wstr.size() == 2 && wstr[0] == L'-')
				{
					_command = find(keys.begin(), keys.end(), wstr) - keys.begin();
					continue;
				}
				switch (_command)
				{
				case (0) :
					{
						path _path = wstr;
						name_module = _path.filename();
						path_module.push_back(_path.root_path());
					}
					break;
				case (1) :
					name_function = wstr;
					break;
				case (2) :
					{
						array<wstring, 10>::iterator it = find(params.begin(), params.end(), L"");
						if (it == params.end())
						{
							return false;
						}
						*it = wstr;
					}
					break;
				default :
					return false;
				}
			}
		}
		return true;
	}
private:
	wstring path_exe;
	vector<wstring> path_module;
	wstring name_exe;
	wstring name_module;
	wstring name_function;
	array<wstring, 10> params = { L"", L"", L"", L"", L"", L"", L"", L"", L"", L"" };
};

} // parse
