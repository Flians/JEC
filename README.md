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
./JEC ../test/golden/gf_1_bit_full_adder.v ../test/revise/rf_1_bit_full_adder.v ../test/output/output_1_bit_full_adder.txt CVC4 i m
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

```
c1355	0.032391	0.002938	0.003823
c1908	0.064298	0.003844	0.007971
c3540	0.173921	0.017646	1.046851
c432	0.068722	0.003669	0.012460
c499	0.031671	0.002428	0.005496
c5315	0.588358	0.023962	0.010317
c7552	0.504539	0.024896	0.015135
c880	0.147289	0.005736	0.008040
adder	9.792344	0.027278	0.014727
bar	0.428488	0.138081	0.017539
decoder	0.061272	0.006766	0.003367
max	0.556582	0.102062	0.167301
sin	0.860964	0.078774	1.596082
```

not merge_nodes_between_networks
```
c1355	0.031124	0.001794	0.003165
c1908	0.063807	0.002915	0.007636
c3540	0.170388	0.009616	0.876562
c432	0.068157	0.003285	0.013524
c499	0.030934	0.001568	0.005183
c5315	0.583182	0.012398	0.009385
c7552	0.472465	0.012229	0.012341
c880	0.139325	0.004052	0.008046
adder	9.533382	0.021432	0.013770
bar	0.419969	0.030865	0.019187
decoder	0.058626	0.002787	0.003324
max	0.541871	0.036414	0.140678
sin	0.832733	0.056626	2.830026
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

### run

``` shell
./cec_abc ./original/abc.rc ./original/rsfq.genlib ./
```

The result <parse, cec>:
```
c1355   0.003846        0.040957
c1908   0.005273        0.145739
c3540   0.012986        0.442472
c432    0.003875        0.045970
c499    0.003295        0.072421
c5315   0.017121        0.517517
c7552   0.019709        0.779324
c880    0.005614        0.258527
adder   0.010502        0.088273
bar     0.047912        1.119685
decoder 0.006263        0.008762    Networks are equivalent after structural hashing
divisor 0.265793        9.963715
log2    0.310544        28.498065
max     0.065809        0.965807
multiplier      0.253371        10.325793
sin     0.075339        4.056654
```