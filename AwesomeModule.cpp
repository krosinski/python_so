#include <iostream>

#include "AwesomeModule.h"
#include <python.h>

AwesomeModule::AwesomeModule() {
    std::cout << "init AwesomeModule" << std::endl;
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('')");
    PyObject* mod = PyString_FromString((char*)"awesome_module");
    appModule = PyImport_Import(mod);
}


AwesomeModule::~AwesomeModule() {
    Py_Finalize();
}

int AwesomeModule::pow(int a, int b) {
    std::cout << "AwesomeModule:pow" << std::endl;
    PyObject* sample_command = PyObject_GetAttrString(appModule, "pow");
    PyObject* a_val = PyInt_FromLong(a);
    PyObject* b_val = PyInt_FromLong(b);
    PyObject* tup = PyTuple_New(0);
    PyObject* data = PyDict_New();
    PyDict_SetItemString(data, "a", a_val);
    PyDict_SetItemString(data, "b", b_val);
    PyObject* res = PyObject_Call(sample_command, tup, data);
    long intRes;
    if (!PyInt_CheckExact(res)){
        std::cout << "Invalid awesome_module.pow() response" << std::endl;
        intRes = -1L;
    }
    else {
        intRes = PyInt_AsLong(res);
    }
    Py_DECREF(sample_command);
    Py_DECREF(a_val);
    Py_DECREF(b_val);
    Py_DECREF(tup);
    Py_DECREF(data);
    Py_DECREF(res);
    return intRes;
}
