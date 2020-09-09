# JEC

Equivalence Checking of Superconducting RSFQ Logic Circuits

## build

The following libraries and headers need be installed:

- gmp: sudo apt-get install libgmp-dev
- readline
- flex
- bison
- opensmt

### build opensmt

The environment is linux

``` shell
git clone https://github.com/usi-verification-and-security/opensmt
cd opensmt
mkdir build && cd build
cmake -DBUILD_STATIC_LIBS:BOOL=ON -DBUILD_SHARED_LIBS:BOOL=OFF -DCMAKE_BUILD_TYPE=Release -DBUILD_EXECUTABLES:BOOL=OFF ..
make
```

The following command for compile:

``` shell
mkdir build && cd build
cmake ..
make
```

## run

``` shell
./JEC ../test/golden/gf_1_bit_full_adder.v ../test/revise/rf_1_bit_full_adder.v ../test/output/output_1_bit_full_adder.txt
```
