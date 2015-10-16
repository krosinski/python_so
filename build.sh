rm sample_app.bin app.log AwesomeModule.so* *pyc 2>/dev/null
clang++ -Ipy27_bin/include/python2.7/ -Lpy27_bin/lib/ py27_bin/lib/libpython2.7.a AwesomeModule.cpp -shared -o AwesomeModule.so.1.0
clang++ -Ipy27_bin/include/python2.7/  sample_app.cpp -o sample_app.bin AwesomeModule.so.1.0
