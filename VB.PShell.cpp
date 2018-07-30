#include "stdafx.h"

#include "parse.h"
#include "interpret.h"


#ifdef _UNICODE
int _tmain(int argc, _TCHAR ** argv)
#else
int main(int argc, char ** argv)
#endif // _UNICODE
{
	try
	{
		parse::SerializeParam<wchar_t**> _ser(argv, argc);
		initialize(_ser);
		if (set_module(_ser.get_name_module()) &&
			set_function(_ser.get_name_function()) &&
			set_arguments(_ser.get_params(), std::count_if(begin(_ser.get_params()), end(_ser.get_params()), [](std::wstring& wstr) { return wstr != L""; })))
		{
			std::thread t(run);
			t.join();
		}
	}
	catch (const parse::SerializeParamExcept& e)
	{
		fprintf(stderr, "Error parsing command argument.\n%s\n", e.what());
		return 0x100;
	}
	catch (const std::invalid_argument& e)
	{
		fprintf(stderr, "Error invalid argument.\n%s\n", e.what());
		return 0x110;
	}
	catch (...)
	{
		fprintf(stderr, "Unknown fatal error.\n");
		return 0x1000;
	}
	uninitilize();

	return 0;
}
