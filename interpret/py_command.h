#ifndef _PY_COMMAND_H_
#define _PY_COMMAND_H_

#include <string>


bool initialize(int, wchar_t**);

template <class _Type>
bool initialize(parse::SerializeParam<_Type>& serialize)
{
	return false;
}

template <>
bool initialize(parse::SerializeParam<wchar_t**>& serialize)
{
	try
	{

	}
	catch (const parse::SerializeParamExcept& e)
	{
		fprintf(stderr, "Error parsing command argument.\n%s\n", e.what());
		return false;
	}
	catch (const std::invalid_argument& e)
	{
		fprintf(stderr, "Error invalid argument.\n%s\n", e.what());
		return false;
	}
	catch (...)
	{
		return false;
	}
	return true;
}

bool uninitilize();


#endif // _PY_COMMAND_H_
