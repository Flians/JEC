# JEC

Equivalence Checking of Superconducting RSFQ Logic Circuits

## build

``` shell
mkdir build && cd build
cmake ..
make
```

## run

`
./JEC.exe ../test/golden/gf_1_bit_full_adder.v ../test/revise/rf_1_bit_full_adder.v ../output/output_1_bit_full_adder.txt
`
