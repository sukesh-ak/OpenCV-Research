# OpenCV Research 
_OpenCV samples during Research for AI_
## Compile using CMAKE
```
# On Linux - install g++ / cmake / gdb
sudo apt update && sudo apt install build-essential gdb cmake git

# Check cmake to make sure, its version is above 2.5
$ cmake --version

# Upgrade to the latest one
$ sudo apt remove cmake -y
$ pip install cmake --upgrade

#  Required for gstreamer?
$ sudo apt install nasm

# Clone repo
git clone --recursive https://github.com/sukesh-ak/OpenCV-Research.git

# ******** On Jetson Jetpack 5.x+ (Tested on Jetson Orin NX) ***
$ sudo apt install ninja-build
$ export VCPKG_FORCE_SYSTEM_BINARIES=1

# Add the following to library path for CuDNN
LD_LIBRARY_PATH=/usr/lib/aarch64
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
> [!IMPORTANT] 
> ```bash
> # Patch information for vcpkg
> -- CUDNN_LIBRARY: CUDNN_LIBRARY-NOTFOUND
> Add `/usr/lib/aarch64-linux-gnu/` to the following file `vcpkg/ports/cudnn/portfile.cmake` in the following line 

```
find_library(CUDNN_LIBRARY NAMES cudnn cudnn8 cudnn7
  HINTS ${CUDA_TOOLKIT_ROOT} $ENV{CUDA_PATH} $ENV{CUDA_TOOLKIT_ROOT_DIR} $ENV{cudnn} $ENV{CUDNN} $ENV{CUDNN_ROOT_DIR} $ENV{CUDA_PATH}/../../../NVIDIA/CUDNN/v9.0 /usr/lib/x86_64-linux-gnu/ /usr/include/aarch64-linux-gnu/ /usr/lib/aarch64-linux-gnu/ /usr/ 
  PATH_SUFFIXES lib lib64 cuda/lib cuda/lib64 lib/x64 cuda/lib/x64 lib/12.3/x64)

# Then increase the version number in `ports/cudnn/vcpkg.json` for `port-version`
# Same thing in `versions/baseline.json`
```


## 3rd party Credits
 Library `cxxopts` - [Command line parser](https://github.com/jarro2783/cxxopts)
