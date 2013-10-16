rm *.o
rm *.so*
gcc -Wall -fPIC -c *.c
gcc -shared -Wl,-soname,librs232.so.1 -o librs232.so.1.0   *.o
