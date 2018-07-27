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

struct compare_ch
{
	bool operator()(wchar_t a, wchar_t b)
	{
		return a == b;
	}
};

PyObject *parse_type_arg(std::wstring& wstr)
{
	using std::placeholders::_1;
	
	if (std::any_of(begin(wstr) + 1, end(wstr), std::bind(compare_ch(), _1, L'.')) ||
		std::any_of(begin(wstr), end(wstr), std::bind(compare_ch(), _1, L'.')) ||
		count_if(begin(wstr), end(wstr), std::bind(compare_ch(), _1, L'.')) > 1)
	{
		return PyUnicode_FromWideChar(wstr.c_str(), wstr.length());
	}

	for (auto it : wstr)
	{
		if (it < 0x30 || it > 0x39)
		{
			return PyUnicode_FromWideChar(wstr.c_str(), wstr.length());
		}
	}

	if (std::any_of(begin(wstr), end(wstr), [](wchar_t& ch) { return ch == L'.'; }))
	{
		return PyFloat_FromDouble(std::stold(wstr));
	}
	return PyLong_FromLong(std::stol(wstr));
}

using TPyObject = std::reference_wrapper<PyObject *>;

struct ParseArg
{
	TPyObject object;
	int it = 0;
	ParseArg(TPyObject _object) : object(_object)
	{
	}
	void operator()(std::wstring& wstr)
	{
		PyObject *obj = parse_type_arg(wstr);
		PyTuple_SetItem(object.get(), it, obj);
		it++;
	}
};

bool set_arguments(std::array<std::wstring, 10>& mass, size_t size)
{
	py_Args = PyTuple_New(size);
	std::for_each_n(begin(mass), size, ParseArg(std::ref(py_Args)));
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

	return py_Func != nullptr && PyCallable_Check(py_Func);
}

bool set_module(std::wstring& name)
{
	PyObject * _name = PyUnicode_FromWideChar(name.c_str(), name.length());
	py_Module = PyImport_Import(_name);
	Py_DECREF(_name);
	return py_Module != nullptr;
}

void run()
{
	PyObject *value = PyObject_CallObject(py_Func, py_Args);
	if (value != nullptr)
	{
		printf("Result of call: %ld\n", PyLong_AsLong(value));
		Py_DECREF(value);
	}
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
