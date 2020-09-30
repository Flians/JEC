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
# for one
./JEC ../test/golden/gf_c880.v ../test/revise/rf_c880.v ../test/output/output_c880.txt CONE i m
# for batch
./JEC ../test/ OPENSMT i m
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
c1355	0.003526	0.000468	0.001526	81.000000
c1908	0.006713	0.000786	0.003635	45.000000
c3540	0.020503	0.002631	0.989613	221.000000
c432	0.006674	0.000768	0.010120	50.000000
c499	0.003147	0.000471	0.002906	48.000000
c5315	0.056950	0.003731	0.003445	422.000000
c7552	0.047722	0.003595	0.007119	457.000000
c880	0.013772	0.000865	0.004610	85.000000
adder	0.665196	0.003209	0.006847	384.000000
bar	0.049737	0.026597	0.010257	194.000000
decoder	0.006538	0.000989	0.000848	312.000000
divisor	292.284542	2.742952	1600.482963	386.000000
max	0.066275	0.013392	0.151436	1332.000000
sin	0.103533	0.013677	1.061095	9.000000
```

not merge_nodes_between_networks
```
c1355	0.004427	0.000225	0.001890	0.000000
c1908	0.007070	0.000534	0.007513	0.000000
c3540	0.021483	0.001384	1.132274	0.000000
c432	0.007427	0.000542	0.010093	0.000000
c499	0.003254	0.000257	0.003202	0.000000
c5315	0.063622	0.002456	0.004222	0.000000
c7552	0.053902	0.001816	0.007753	0.000000
c880	0.015555	0.000579	0.005249	0.000000
adder	0.749140	0.003091	0.007450	0.000000
bar	0.056037	0.003505	0.012688	0.000000
decoder	0.007077	0.000438	0.000996	0.000000
divisor	352.795162	3.309014	39.375632	0.000000
max	0.074498	0.004922	0.167783	0.000000
sin	0.109255	0.008405	2.377425	0.000000
```

## build cec_abc

- readline: sudo apt-get install libreadline-dev

``` shell
gcc -Wall -g -c cec_abc.c -o cec_abc.o
g++ -g -o cec_abc cec_abc.o ../lib/libabc.a -lm -ldl -lreadline -lpthread
```

The command for cec in abc:
``` abc
read_library rsfq.genlib
r -m golden.v
r -m revise.v
cec golden.v revise.v
```

### run using abc

``` shell
./cec_abc ./original/abc.rc ./original/rsfq.genlib ./
```

The result <parse, cec>:
```
c1355	0.012091	0.077142
c1908	0.004693	0.180226
c3540	0.013721	0.560867
c432	0.003969	0.040848
c499	0.003856	0.070894
c5315	0.019077	0.587466
c7552	0.018403	0.875334
c880	0.009771	0.278090
adder	0.010443	0.077313
bar	0.036429	1.339717
decoder	0.005418	0.007647
divisor	0.310117	12.486118
max	0.054789	1.027411
sin	0.061184	4.987837
```

## Analyze performance

``` CMake
    # Analyze performance
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
```

``` bash
./build/JEC ./test/golden/gf_c880.v ./test/revise/rf_c880.v ./test/output/output_c880.txt CONE i m
gprof ./build/JEC gmon.out > profile.txt
```
