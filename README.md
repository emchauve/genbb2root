# genbb2root

C++ and BASH interface to convert GENBB data into a TTree structure in ROOT format.

Compile me with:
```console
mkdir build
cd build
cmake ..
make
cd ..
```

Run me with:
```console
./genbb2root.sh [GENERATOR] [NBEVENTS]
```
with GENERATOR = k40, bi214, tl208, etc. (see definitions in conf/genbb-*.def)


Look into quick gamma+energy spectra with the ROOT demo script:
```console
root
root [0] .L scripts/energy_spectrum.cc
energy_spectrum("data/bi207.root");
```

.. image:: plots/bi207.png
