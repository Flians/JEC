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
>>> ./JEC -h
Please input parameters:
    -h: help;
    -b: the root directory which includes the godlen directory and the revise directory;
    -n: the batch, the default is 100;
    -p: print the netlist;
    -g: the path of golden file;
    -r: the path of revised file;
    -o: the path of output file;
    -m: merge the equivalent nodes;
    -d: clean DFF;
    -s: clean Splitter;
    -i: whether to solve iteratively;
    -e: the type fo SMT solver, including FSM, OPENSMT, CONE and CVC4;
For example, "./JEC -g <golden.v> -r <revised.v> -o <output> -e <FSM|OPENSMT|CONE|CVC4> <-i> <-m> <-s> <-d>".

# for single
./JEC -g ../test/rsfq/alu_1.v
./JEC -g ../test/golden/gf_c880.v -r ../test/revise/rf_c880.v -o ../test/output/output_c880.txt -e CONE -i -m -s
# for batch
./JEC -b ../test/rsfq -n 1
./JEC -b ../test/ -e OPENSMT -i -m -s -n 100
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

>>> ./JEC -b ../test/ -e OPENSMT -i -m -s -n 100
c1355    0.254904    0.065531    0.003054    517.000000    1.000000 1.000000
c1908    0.448836    0.131734    0.009504    662.000000    1.000000 1.000000
c3540    0.973107    0.744574    0.004138    2011.000000   1.000000 1.000000
c432     0.476922    0.205641    0.002768    1022.000000   1.000000 1.000000
c499     0.248019    0.063893    0.004189    470.000000    1.000000 1.000000
c5315    1.865864    3.578193    0.006542    4858.000000   1.000000 1.000000
c6288    3.153084    6.287911    0.007269    6791.000000   1.000000 1.000000
c7552    1.888898    2.280202    0.006460    3469.000000   1.000000 1.000000
c880     0.562984    0.218336    0.002928    952.000000    1.000000 1.000000
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

>>> ./JEC -b ../test/ -e OPENSMT -i -s -n 100
c1355    0.230055    0.008348    0.003171    0.000000    1.000000 1.000000
c1908    0.425142    0.014122    0.009205    0.000000    1.000000 1.000000
c3540    0.939690    0.046319    0.004415    0.000000    1.000000 1.000000
c432     0.435229    0.012235    0.002749    0.000000    1.000000 1.000000
c499     0.223367    0.007800    0.004498    0.000000    1.000000 1.000000
c5315    1.867916    0.071992    0.007723    0.000000    1.000000 1.000000
c6288    2.919651    0.140283    0.009194    0.000000    1.000000 1.000000
c7552    1.896951    0.076740    0.007389    0.000000    1.000000 1.000000
c880     0.516963    0.015771    0.003000    0.000000    1.000000 1.000000
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
>>> ./JEC -b ../test/ -e CONE -m -i -s -n 100
c1355   0.097537    0.036505    0.001336    517.000000    1.000000 1.000000
c1908   0.132868    0.042035    0.005858    662.000000    1.000000 1.000000
c3540   0.163128    0.129921    0.003626    2011.000000   1.000000 1.000000
c432    0.148514    0.057888    0.000568    1022.000000   1.000000 1.000000
c499    0.093194    0.033656    0.000490    470.000000    1.000000 1.000000
c5315   0.165576    0.286189    0.032747    4858.000000   1.000000 1.000000
c6288   0.387356    1.019838    0.003816    6791.000000   1.000000 1.000000
c7552   0.254810    0.237436    0.030155    3469.000000   1.000000 1.000000
c880    0.180317    0.063049    0.002717    952.000000    1.000000 1.000000
```

> Incremental + Unmerged

``` csv
>>> ./JEC -b ../test/ -e CONE -i -s -n 100
c1355   0.060807    0.006202    0.002156    0.000000    1.000000 1.000000
c1908   0.074082    0.009171    0.010013    0.000000    1.000000 1.000000
c3540   0.089705    0.033433    1.110921    0.000000    1.000000 1.000000
c432    0.086115    0.006849    0.000557    0.000000    1.000000 1.000000
c499    0.057583    0.006023    0.000478    0.000000    1.000000 1.000000
c5315   0.154835    0.049702    0.003746    0.000000    1.000000 1.000000
c6288   0.306190    0.117377    0.004395    0.000000    1.000000 1.000000
c7552   0.204267    0.049860    0.005083    0.000000    1.000000 1.000000
c880    0.099814    0.009256    0.000915    0.000000    1.000000 1.000000
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
