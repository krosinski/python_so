#include <python.h>

class AwesomeModule {
    private:
        int pid;
        PyObject* appModule;
        int runFunc(const char* name);

    public:
        AwesomeModule();
        ~AwesomeModule();
        int start();
        int stop();
        int sampleCommand(int a, const char* b);
};
