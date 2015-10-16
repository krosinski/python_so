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
    pid = 0;
    std::cout << "Sychronizer initialized" << std::endl;
}


AwesomeModule::~AwesomeModule() {
    std::cout << "deinit AwesomeModule" << std::endl;
    Py_Finalize();
}

int AwesomeModule::runFunc(const char* name) {
    PyObject* initFunc = PyObject_GetAttrString(appModule, name);
    PyObject* res = PyObject_CallFunction(initFunc, NULL);
    long intRes;
    if (!PyInt_CheckExact(res)){
        std::cout << "Invalid AwesomeModule." << name << "() response" << std::endl;
        intRes = -1L;
    }
    else {
        intRes = PyInt_AsLong(res);
    }
    Py_DECREF(res);
    Py_DECREF(initFunc);
    return (int)intRes;
}

int AwesomeModule::start() {
    std::cout << "Starting AwesomeModule" << std::endl;
    int res = runFunc("start");
    if (res < 0)
        return res;
    pid = res;
    std::cout << "AwesomeModule started" << std::endl;
    return pid;
}

int AwesomeModule::stop() {
    std::cout << "Stopping AwesomeModule" << std::endl;
    return runFunc("stop");
}

int AwesomeModule::sampleCommand(int param1, const char* param2) {
    if (pid <= 0)
        return 0;
    PyObject* sample_command = PyObject_GetAttrString(appModule, "sample_command");
    PyObject* param1_val = PyInt_FromLong(param1);
    PyObject* param2_val = PyString_FromString(param2);
    PyObject* tup = PyTuple_New(0);
    PyObject* data = PyDict_New();
    PyDict_SetItemString(data, "param1", param1_val);
    PyDict_SetItemString(data, "param2", param2_val);

    PyObject_Call(sample_command, tup, data);

    Py_DECREF(sample_command);
    Py_DECREF(param1_val);
    Py_DECREF(param2_val);
    Py_DECREF(tup);
    Py_DECREF(data);
    return 1;
}
