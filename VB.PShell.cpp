#include "stdafx.h"

#include "interpret.h"
#include "parse.h"


std::wstring DisplayPathInfo(std::experimental::filesystem::path &path)
{
	std::wostringstream wos;
	int i = 0;
	wos << L"Displaying path info for: " << path << std::endl;
	for (std::experimental::filesystem::path::iterator itr = path.begin(); itr != path.end(); ++itr)
	{
		wos << L"path part: " << i++ << L" = " << *itr << std::endl;
	}

	wos << L"root_name() = " << path.root_name() << std::endl
		<< L"root_path() = " << path.root_path() << std::endl
		<< L"relative_path() = " << path.relative_path() << std::endl
		<< L"parent_path() = " << path.parent_path() << std::endl
		<< L"filename() = " << path.filename() << std::endl
		<< L"stem() = " << path.stem() << std::endl
		<< L"extension() = " << path.extension() << std::endl;

	return wos.str();
}

using namespace std;

int main(int argc, char ** argv)
{
	parse::ShellParam<wchar_t**> _shell(argv, argc);
	//wcout << _shell.get() << endl;
	parse::SerializeParam<char**> _ser(argv, argc);
	wcout << _ser.get_shell() << endl;
	// parse::ShellParam<wchar_t**> _shell(argv, argc);
	/*
	wchar_t *program = Py_DecodeLocale(argv[0], NULL);
	if (program == NULL) {
	fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
	exit(1);
	}
	Py_SetProgramName(program);
	Py_Initialize();
	PyRun_SimpleString("from time import time,ctime\n"
	"print('Today is', ctime(time()))\n");
	if (Py_FinalizeEx() < 0) {
	exit(120);
	}
	PyMem_RawFree(program);
	

	// fprintf(stderr, "%s\n", Py_Set);

	PyObject *pName, *pModule, *pFunc;
	PyObject *pArgs, *pValue;
	int i;

	std::experimental::filesystem::path path_python = argv[0];

	std::wstring _path = path_python.parent_path();
	_path += L";";
	_path += path_python.parent_path();
	_path += L"\\Python36-32\\Lib\\;";
	_path += path_python.parent_path();
	_path += L"\\Python36-32\\DLLs\\";

	std::wcout << DisplayPathInfo(path_python) << std::endl;

	//if (argc < 3) 
	//{
	//	fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
	//	return 1;
	//}

	Py_SetPath(_path.c_str());
	Py_Initialize();
	fprintf(stderr, "%s\n", Py_GetCompiler());
	fprintf(stderr, "%ws\n", Py_GetPath());
	fprintf(stderr, "%ws\n", Py_GetPythonHome());
	pName = PyUnicode_DecodeFSDefault(argv[1]);
	// pName = PyUnicode_FromString(ptr);
	// Error checking of pName left out 

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL)
	{
		pFunc = PyObject_GetAttrString(pModule, argv[2]);
		// pFunc is a new reference 

		if (pFunc && PyCallable_Check(pFunc))
		{
			pArgs = PyTuple_New(argc - 3);
			for (i = 0; i < argc - 3; ++i) {
				pValue = PyLong_FromLong(atoi(argv[i + 3]));
				if (!pValue)
				{
					Py_DECREF(pArgs);
					Py_DECREF(pModule);
					fprintf(stderr, "Cannot convert argument\n");
					return 1;
				}
				//  pValue reference stolen here:
				PyTuple_SetItem(pArgs, i, pValue);
			}
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL)
			{
				printf("Result of call: %ld\n", PyLong_AsLong(pValue));
				Py_DECREF(pValue);
			}
			else
			{
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				system("pause");
				return 1;
			}
		}
		else
		{
			if (PyErr_Occurred())
			{
				PyErr_Print();
			}
			fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else
	{
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
		system("pause");
		return 1;
	}
	if (Py_FinalizeEx() < 0)
	{
		system("pause");
		return 120;
	}
*/
	return 0;
}
