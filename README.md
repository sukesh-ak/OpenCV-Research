# OpenCV Research 
_OpenCV samples during Research for AI_
## Compile using CMAKE
```
# On Linux - install g++ / cmake / gdb
sudo apt update && sudo apt install build-essential gdb cmake git

# Clone repo
git clone --recursive https://github.com/sukesh-ak/OpenCV-Research.git

# ******** On Jetson Jetpack 5.x+ (Tested on Jetson Orin NX) ***
$ sudo apt install ninja-build
$ export VCPKG_FORCE_SYSTEM_BINARIES=1
# *************************************************

# Run bootstrap 
./vcpkg/bootstrap.sh

# Install all dependencies (will take a while)
./vcpkg/vcpkg install

# Compile and build the binary
cmake . -B build
cmake --build build

# Run the program
./build/<executable_name>
```
 


## 3rd party Credits
 Library `cxxopts` - [Command line parser](https://github.com/jarro2783/cxxopts)
