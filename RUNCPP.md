g++ main.cpp -o main

./main





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
c++ -O3 -Wall -shared -std=c++17 -fPIC \
-I/usr/include/python3.12 \
-I/home/hebbar/Documents/sharath/Github/HFT/.venv/lib/python3.12/site-packages/pybind11/include \
moving_average.cpp \
-o cppma$(python3-config --extension-suffix)
```