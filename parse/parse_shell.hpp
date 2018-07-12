#include <string>
#include <array>
#include <vector>
#include <unordered_map>
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
	wstring& get() const
	{
		if (!shell_str.empty())
		{
			return shell_str;
		}

		for (wstring & str : shell)
		{
			shell_str += str;
			shell_str += '\n';
		}

		return shell_str;
	}
	wstring& operator[](const int _index) const
	{

	}
private:
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
class SerializeParam : public ShellParam<wchar_t**>
{
public:
	SerializeParam(_Type arg, int _count) : ShellParam<wchar_t**>::ShellParam(arg, _count)
	{
	}

	wstring& get_shell()
	{
		return get();
	}
private:
	unordered_map<wstring, wstring, hash<wstring>, equal_to> map_param;
};

} // parse
