# JEC

Equivalence Checking of Superconducting RSFQ Logic Circuits

## build

The following libraries and headers need be installed:

- gmp: sudo apt-get install libgmp-dev
- readline
- flex
- bison
- opensmt 2.0.1
- libantlr3c 3.2/2.4
- CVC4 1.8

### build opensmt

The environment is linux

``` shell
git clone https://github.com/usi-verification-and-security/opensmt
cd opensmt
mkdir build && cd build
cmake -DBUILD_STATIC_LIBS:BOOL=ON -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_EXECUTABLES:BOOL=OFF ..
make
```

### build CaDiCaL

The environment is linux

The following command for compile:

``` shell
./configure -fPIC
make
cp src/ccadical.h ../include/CaDiCaL/
cp src/cadical.hpp ../include/CaDiCaL/
cp build/libcadical.a  ../lib/
```

## Building CVC4

``` shell
./contrib/get-antlr-3.4  # download and build ANTLR
./contrib/get-cadical  # download and build ANTLR
./configure.sh production --prefix=../ --static --no-static-binary --no-python-bindings --cadical   # use --prefix to specify a prefix (default: /usr/local)
                    # use --name=<PATH> for custom build directory
cd build   # default is ./build
make             # use -jN for parallel build with N threads
make check       # to run default set of tests
make install     # to install into the prefix specified above
```

## run

``` shell
./JEC ../test/golden/gf_1_bit_full_adder.v ../test/revise/rf_1_bit_full_adder.v ../test/output/output_1_bit_full_adder.txt
```
