#include <iostream>
#include "AwesomeModule.h"
#include <unistd.h>

int main(int argc, char* argv[]){
    AwesomeModule* mod = new AwesomeModule;
    mod->start();
    mod->sampleCommand(123, "heelo!!!!111");
    mod->stop();
    free(mod);
}
