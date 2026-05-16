# Run CPP apps

```sh
g++ main.cpp -o main
./main
```

# Run Pybind 

## Installing Dependencies

```sh
sudo apt install python3-pybind11
sudo apt update
sudo apt install python3-dev
sudo apt install python3.12-dev

```

## To compile the CPP App
```sh
c++ -O3 -Wall -shared -std=c++17 -fPIC $(python3 -m pybind11 --includes) moving_avg_to_py.cpp -o cppma$(python3-config --extension-suffix)
```


## Breaking down on Cpp App Compilation of Pybind

### c++

- This invokes the C++ compiler.
- Usually: `g++` or `clang++` depending on your system.

### -03

- Optimization Level 3
- Tells compiler: "Optimize aggressively for performance"
- Enables:

  - loop unrolling
  - vectorization
  - inlining
  - dead code elimination
  - constant propagation


| Flag | Meaning |
| :--- | :---: |
| -00 | No Optimization |
| -01 | Basic Optimization |
| -02 | Balanced Optimization |
| -03 | Aggressive Optimization |

- Quant/HFT systems almost always use: ```-O3```

### -Wall

- Enable compiler warnings. Very important in C++.

- Catches:

  - unused variables
  - type mismatches
  - suspicious logic
  - implicit conversions

- Does NOT mean: "all warnings" just a common set.

### -shared

- Build a shared library instead of executable binary
- Without this you would get something like ```a.out```
- With this you get ```cppma.so```
- Shared libraries are loaded dynamically by Python.

### -std=c++17

- Use:
  - C++17 standard

- Enables modern C++ features:

  - structured bindings
  - constexpr improvements
  - optional
  - filesystem
  - better templates

- pybind11 expects modern C++.


### -fPIC

- Position Independent Code.
- Required for shared libraries
- Allows code to load into arbitrary memory addresses.
- Critical for ```.so``` files.
- Without this linker errors happen.


### $(python3 -m pybind11 --includes)

- This is shell substitution.
- The shell executes:

```sh
python3 -m pybind11 --includes
```
and injects the result.

- Usually expands to:

```sh
-I/usr/include/python3.12
-I/home/user/.local/.../pybind11/include
```

- Why Needed?

  - Compiler must know where headers exist.
  - Specifically:

    - Python.h
    - pybind11.h

- `-I` Means: "Include directory"

- Example:

  - `-I/usr/include/python3.12` tells compiler Search here for header files

### main.cpp

- Your Source File

### -o

- Output file flag 
- Without it compiler defaults to `a.out`

### cppma$(python3-config --extension-suffix)

- This creates correct Python extension filename

```sh
python3-config --extension-suffix
```

- returns something like `.cpython-312-x86_64-linux-gnu.so`
- Final filename becomes `cppma.cpython-312-x86_64-linux-gnu.so`

- Why Important?

  - Python expects extension modules to follow ABI naming conventions.

  - This suffix encodes:

    - Python version
    - architecture
    - ABI compatibility