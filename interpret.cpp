#include "stdafx.h"
#include "interpret.h"


static PyObject *py_Module, *py_Func, *py_Args, *py_Value;


#pragma optimize ("", off)
bool initialize(parse::SerializeParam<wchar_t**>& serialize)
{
	std::wstring py_path = parse::utils::concat_integral(serialize.get_path_module(), L";");

	Py_SetPath(py_path.c_str());
	Py_Initialize();

	return true;
}

// PyObject *parse_type_arg

bool set_arguments(std::array<std::wstring, 10>& mass, size_t size)
{
	py_Args = PyTuple_New(size);
	std::for_each_n(begin(mass), size, [&](std::wstring& wstr) { std::wcout << wstr << std::endl; });
	return true;
}

bool set_function(std::wstring& name)
{
	if (py_Module == nullptr)
	{
		return false;
	}

	std::string str(begin(name), end(name));
	py_Func = PyObject_GetAttrString(py_Module, str.c_str());

	return py_Func != nullptr;// && PyCallable_Check(py_Func);
}

bool set_module(std::wstring& name)
{
	std::string str(begin(name), end(name));
	PyObject * _name = PyUnicode_FromString(str.c_str());
	py_Module = PyImport_Import(_name);
	Py_DECREF(_name);
	return py_Module != nullptr;
}

bool uninitilize()
{
	if (py_Func != nullptr)
	{
		Py_XDECREF(py_Func);
	}
	if (py_Module != nullptr)
	{
		Py_DECREF(py_Module);
	}
	if (py_Args != nullptr)
	{
		Py_DECREF(py_Args);
	}
	if (py_Value != nullptr)
	{
		Py_DECREF(py_Value);
	}
	Py_FinalizeEx();

	return true;
}
