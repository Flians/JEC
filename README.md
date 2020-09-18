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
./JEC ../test/golden/gf_1_bit_full_adder.v ../test/revise/rf_1_bit_full_adder.v ../test/output/output_1_bit_full_adder.txt CVC4 i
```

## result

- CVC4

> Unincremental

``` bash
bar     0.38    0.10    4.24
c432    0.10    0.00    0.01
c499    0.05    0.00    0.01
c880    0.12    0.00    0.04
adder   21.82   0.02    0.08
c1908   0.10    0.00    0.03
c1355   0.05    0.00    0.01
c3540   0.27    0.01    0.53
decoder 0.04    0.00    0.00
c5315   0.65    0.02    0.18
c7552   0.64    0.02    0.23
```

> Incremental

``` bash
bar     0.39    0.10    0.30
c432    0.10    0.00    0.01
c499    0.05    0.00    0.02
c880    0.12    0.00    0.01
adder   21.84   0.02    0.17
c1908   0.10    0.00    0.02
c1355   0.05    0.00    0.02
c3540   0.26    0.01    0.67
decoder 0.04    0.00    0.01
c5315   0.67    0.02    0.08
c7552   0.64    0.02    0.07
```

- OPENSMT

> Unincremental

``` bash
bar 	0.41	0.11	3.74
c432	0.10	0.00	0.01
c499	0.05	0.00	0.01
c880	0.13	0.00	0.02
adder	22.67	0.02	0.04
c1908	0.10	0.00	0.03
c1355	0.05	0.00	0.01
c3540	0.27	0.01	0.71
decoder	0.04	0.00	0.00
c5315	0.68	0.02	0.19
c7552	0.67	0.02	0.19
```

> Incremental

``` bash
bar 	0.43	0.11	0.01
c432	0.11	0.00	0.01
c499	0.05	0.00	0.00
c880	0.13	0.00	0.00
adder	22.94	0.02	0.01
c1908	0.10	0.00	0.01
c1355	0.05	0.00	0.00
c3540	0.33	0.01	0.53
decoder	0.04	0.00	0.00
c5315	0.70	0.02	0.01
c7552	0.68	0.02	0.00
```

## build cec_abc

- readline: sudo apt-get install libreadline-dev

``` shell
gcc -Wall -g -c cec_abc.c -o cec_abc.o
g++ -g -o cec_abc cec_abc.o ../lib/libabc.a -lm -ldl -lreadline -lpthread
```

### run

``` shell
./cec_abc ./original/abc.rc ./original/rsfq.genlib ./
```