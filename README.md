# JEC

Equivalence Checking of Superconducting RSFQ Logic Circuits

## build

``` bash
> $win: 
cd JEC
build.dat

> $linux:
cd JEC
build.sh
```

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

### Building CVC4

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

``` csv
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

``` csv
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

> Unincremental and unmerged

``` csv
c1355   0.083464        0.003938        0.005037        0.000000
c1908   0.179520        0.007845        0.027249        0.000000
c3540   0.538300        0.025394        0.420318        0.000000
c432    0.199589        0.007950        0.012735        0.000000
c499    0.083992        0.004031        0.007450        0.000000
c5315   2.097035        0.034960        0.109506        0.000000
c7552   1.626871        0.035265        0.178911        0.000000
c880    0.434941        0.009343        0.022446        0.000000
adder   42.254076       0.057698        0.013900        0.000000
bar     1.311121        0.067664        1.873933        0.000000
decoder 0.169107        0.008420        0.002394        0.000000
max     1.731050        0.088124        0.281712        0.000000
```

> Incremental
>> merged

``` csv
c1355    0.003526    0.000468    0.001526    81.000000
c1908    0.006713    0.000786    0.003635    45.000000
c3540    0.020503    0.002631    0.989613    221.000000
c432     0.006674    0.000768    0.010120    50.000000
c499     0.003147    0.000471    0.002906    48.000000
c5315    0.056950    0.003731    0.003445    422.000000
c7552    0.047722    0.003595    0.007119    457.000000
c880     0.013772    0.000865    0.004610    85.000000
adder    0.665196    0.003209    0.006847    384.000000
bar      0.049737    0.026597    0.010257    194.000000
decoder  0.006538    0.000989    0.000848    312.000000
divisor  292.284542  2.742952    1600.482963 386.000000
max      0.066275    0.013392    0.151436    1332.000000
sin      0.103533    0.013677    1.061095    9.000000

New
c1355   0.078609        0.005909        0.003459        94.000000
c1908   0.164156        0.013063        0.008364        78.000000
c3540   0.480967        0.045137        0.044518        410.000000
c432    0.175805        0.013680        0.010527        185.000000
c499    0.078776        0.005634        0.004683        90.000000
c5315   1.298088        0.290657        0.009472        2013.000000
c7552   1.117735        0.230538        0.008907        1952.000000
c880    0.357020        0.031802        0.004034        420.000000
adder   8.188435        5.044213        0.029578        17150.000000
bar     1.233186        0.207398        0.019740        2110.000000
decoder 0.160221        0.017369        0.003428        757.000000
max     1.566352        0.185871        0.189845        766.000000
sin     2.257909        0.453937        148.072237      1145.000000
```

>> unmerged

``` csv
c1355    0.004427    0.000225    0.001890    0.000000
c1908    0.007070    0.000534    0.007513    0.000000
c3540    0.021483    0.001384    1.132274    0.000000
c432     0.007427    0.000542    0.010093    0.000000
c499     0.003254    0.000257    0.003202    0.000000
c5315    0.063622    0.002456    0.004222    0.000000
c7552    0.053902    0.001816    0.007753    0.000000
c880     0.015555    0.000579    0.005249    0.000000
adder    0.749140    0.003091    0.007450    0.000000
bar      0.056037    0.003505    0.012688    0.000000
decoder  0.007077    0.000438    0.000996    0.000000
divisor  352.795162  3.309014    39.375632   0.000000
max      0.074498    0.004922    0.167783    0.000000
sin      0.109255    0.008405    2.377425    0.000000
```

- CONE

> Incremental + Merged

``` csv
c1355   0.081086        0.005887        0.254701        94.000000
c1908   0.163819        0.012437        0.231086        78.000000
c3540   0.480414        0.045358        0.455129        410.000000
c432    0.175784        0.013853        0.208034        185.000000
c499    0.078810        0.005516        0.248494        90.000000
c5315   1.291901        0.286930        1.390795        2013.000000
c7552   1.106534        0.229754        0.922880        1952.000000
c880    0.356629        0.032089        0.751191        420.000000
adder   8.182152        5.050013        3.166019        17150.000000
bar     1.231371        0.217590        1.272517        2110.000000
decoder 0.159741        0.017186        0.077793        757.000000
max     1.565038        0.189290        0.547330        766.000000
sin     2.246098        0.434367        6.473022        1145.000000
```

``` csv
c1355   0.265823    0.053814    0.139368    491.000000  1.000000  1.000000
c1908   0.471989    0.100850    0.123533    546.000000  1.000000  1.000000
c3540   1.040617    0.448766    0.349971    1437.000000 1.000000  1.000000
c432    0.486882    0.146382    0.121195    842.000000  1.000000  1.000000
c499    0.258990    0.050502    0.137533    472.000000  1.000000  1.000000
c5315   1.973831    2.372863    1.060367    3341.000000 1.000000  1.000000
c6288   2.995161    5.790667    140.998609  7065.000000 1.000000  1.000000
c7552   2.003655    1.436033    0.647185    2495.000000 1.000000  1.000000
c880    0.599256    0.160797    0.409966    796.000000  1.000000  1.000000
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

``` csv
c1355      0.012091    0.077142
c1908      0.004693    0.180226
c3540      0.013721    0.560867
c432       0.003969    0.040848
c499       0.003856    0.070894
c5315      0.019077    0.587466
c7552      0.018403    0.875334
c880       0.009771    0.278090
adder      0.010443    0.077313
bar        0.036429    1.339717
decoder    0.005418    0.007647
divisor    0.310117    12.486118
max        0.054789    1.027411
sin        0.061184    4.987837
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
