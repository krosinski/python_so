#include <python.h>

class AwesomeModule {
    private:
        PyObject* appModule;

    public:
        AwesomeModule();
        ~AwesomeModule();
        int pow(int a, int b);
};
