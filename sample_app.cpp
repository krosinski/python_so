#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "AwesomeModule.h"

int main(int argc, char* argv[]){
    if (argc > 2) {
        AwesomeModule* mod = new AwesomeModule;
        int a = atoi(argv[1]);
        int b = atoi(argv[2]);
        int res = mod->pow(a, b);
        std::cout << "Pow res: " << res << std::endl;
        free(mod);
    }
}
