#include <string>
#include <array>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <functional>


namespace parse
{

using namespace std;

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
		for_each(shell.begin(), shell.end(), [&](wstring_view str) { shell_str += str; shell_str += ' '; });
	}
	int count;
	wstring shell_str;
	vector<wstring> shell;
};

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
			wstring res = parse::utils::concat_s(L"\n", path_exe, name_exe, wstring(L"\tPath Python:"), 
				parse::utils::concat_integral(path_module, L"\n"),
				name_module, name_function, 
				parse::utils::concat_integral<wstring, 10, wchar_t const [2]>(params, L"\t"));
			throw SerializeParamExcept(get(), res);
		}
		for_each(begin(path_python), end(path_python), [&](const wstring& _path) { path_module.push_back(parse::utils::concat(path_exe, _path)); });
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
				tie(path_exe, name_exe) = parse::utils::get_path_name(wstr);
			}
			else
			{
				static int _command = -1;
				if (wstr.size() == 2 && wstr[0] == L'-')
				{
					_command = find(keys.begin(), keys.end(), wstr) - keys.begin();
					continue;
				}
				switch (_command)
				{
				case (0) :
					{
						auto[_1, _2] = parse::utils::get_path_name(wstr);
						name_module = _2;
						path_module.push_back(_1);
						_command = -1;
					}
					break;
				case (1) :
					name_function = wstr;
					_command = -1;
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
