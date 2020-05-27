# JEC

Equivalence Checking of Superconducting RSFQ Logic Circuits

## build

The following libraries and headers need be installed:

- gmp
- readline
- flex
- bison

The following command for compile:

``` shell
mkdir build && cd build
cmake ..
make
```

## run

``` shell
./JEC ../test/golden/gf_1_bit_full_adder.v ../test/revise/rf_1_bit_full_adder.v ../output/output_1_bit_full_adder.txt
```
