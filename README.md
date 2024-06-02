# How to build OpenCV with Cuda on Jetson 
*_Currently tested on Jetson Orin NX 16GB with Jetpack 6.x_*  
_(Should work on other Debian/Ubuntu distros too including WSL)_
<details>

<summary>How to build OpenCV with Cuda on Jetson [1..4]</summary>

## 1. Install dependencies
```bash
sudo apt-get update
sudo apt-get upgrade -y
sudo apt-get install -y build-essential cmake git

# Make sure you have latest cmake
sudo apt-get install -y libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install -y python3.8-dev python3-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libdc1394-22-dev

# To support GTK2+OpenGL so you can use namedWindow functions 
sudo apt-get install libgtkglext1 libgtkglext1-dev 

# To support gstreamer
sudo apt install libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev

# No OpenGL support in OpenCV for GTK3+.
# Reference: https://github.com/opencv/opencv/issues/21592
# Port of gtkglext to GTK+ 3 (not tested)
# https://github.com/tdz/gtkglext

# Need to enable either QT or GTK for UI backend. 
# For OpenGL support use GTK2.

# QT + OPENGL support (fails - maybe because QT5 is old)
#sudo apt-get install qtbase5-dev qt5-qmake
#sudo apt-get install libqt5opengl5-dev libgl1-mesa-dev
```

```bash
# Note down `JETSON_CUDA_ARCH_BIN` for CMake command  
$ echo $JETSON_CUDA_ARCH_BIN
```

```bash
# Above command will show one of the following values
8.7 => Jetson AGX Orin, Jetson Orin NX, Jetson Orin Nano 
7.2 => Jetson AGX Xavier, Jetson Xavier NX 
6.2 => Jetson TX2 
5.3 => Jetson Nano 
```

## 2. Setup folder and get source from Github

```bash
# Create build root folder
mkdir ~/opencv_build && cd ~/opencv_build

# Clone OpenCV version 4.x branch 
# At the time of this documentation, its 4.10
git clone -b 4.x https://github.com/opencv/opencv.git
git clone -b 4.x https://github.com/opencv/opencv_contrib.git

# Create folder to compile
mkdir -p ~/opencv_build/opencv/build && cd ~/opencv_build/opencv/build

# Generate cmake files
# Use CUDA_ARCH_BIN version from the above information as per your device
cmake -D CMAKE_BUILD_TYPE=RELEASE \
      -D CMAKE_INSTALL_PREFIX=/usr/local \
      -D OPENCV_EXTRA_MODULES_PATH=~/opencv_build/opencv_contrib/modules \
      -D WITH_CUDA=ON \
      -D CUDA_ARCH_BIN=8.7 \
      -D CUDA_ARCH_PTX="" \
      -D OPENCV_DNN_CUDA=ON \
      -D WITH_CUDNN=ON \
      -D WITH_OPENGL=ON \
      -D OpenGL_GL_PREFERENCE=GLVND \
      -D WITH_GTK=ON \
      -D WITH_GTK_2_X=ON \
      -D WITH_QT=OFF \
      -D WITH_WAYLAND=OFF \
      -D CUDNN_INCLUDE_DIR=/usr/include \
      -D CUDNN_LIBRARY=/usr/lib/aarch64-linux-gnu/libcudnn.so \
      -D OPENCV_ENABLE_NONFREE=ON \
      -D OPENCV_GENERATE_PKGCONFIG=ON \
      -D WITH_NVCUVID=OFF \
      -D WITH_NVCUVENC=OFF \
      -D OPENCV_ENABLE_NONFREE=OFF \
      -D BUILD_opencv_rgbd=OFF \
      -D BUILD_EXAMPLES=OFF ..


# Once the above is completed, review the final output to make sure CUDA is enabled
```

## 3. Compile, Build and Install

```bash
# Compile in parellel using all the processor cores on the device
make -j$(nproc)

# Install system-wide
sudo make install
sudo ldconfig   
```

## 4. Test the OpenCV build using Python
```bash
# Use python command line to dump out buid info
python3 -c "import cv2 ; print(cv2.getBuildInformation())"

# You can also use jtop info page to verify.

# In case above python output does not align with cmake setup, use cuda-check sample to confirm
# After compile run
$ ./build/bin/cuda-check
```
</details>

## 5. Compile and run the application

```bash
# Compile and build the binary
$ cmake . -B build
$ cmake --build build

# Run the program
$ ./build/<executable_name>
```

### Samples included
```bash
# Draw Text on Default Camera (0)
$ ./build/bin/opencvr textcam

# Draw Image on Default Camera (0)
$ ./build/bin/opencvr imgcam

# Draw Shapes in a window
$ ./build/bin/opencvr shape

# Face detection on Default Camera (0)
$ ./build/bin/opencvr detect
```

### From Samples folder
```bash
# Cuda build information
$ ./build/bin/check-cuda

# Using Default Camera (0)
$ ./build/bin/segment-objects
```