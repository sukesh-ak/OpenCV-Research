# Simple CLI - CPP Template for VS Code
#### Compile
```
g++ *.cpp -o cmdargs
```
or use CMAKE
```
# On Linux - install g++ / cmake / gdb
sudo apt update && sudo apt install build-essential gdb  
sudo apt update && sudo apt install cmake

mkdir build && cd build && cmake .. && cmake --build .
```

#### Usage
```
./cmdargs -t "hello" -d true -n 10 -f hhh.txt -f aaa.txt
╔═╗╦╔╦╗╔═╗╦  ╔═╗  ╔═╗╦  ╦
╚═╗║║║║╠═╝║  ║╣   ║  ║  ║
╚═╝╩╩ ╩╩  ╩═╝╚═╝  ╚═╝╩═╝╩
debug: 1
textvalue: hello
number: 10
Files
        hhh.txt
        aaa.txt


./cmdargs -h
╔═╗╦╔╦╗╔═╗╦  ╔═╗  ╔═╗╦  ╦
╚═╗║║║║╠═╝║  ║╣   ║  ║  ║
╚═╝╩╩ ╩╩  ╩═╝╚═╝  ╚═╝╩═╝╩
CLI with arguments
Usage:
  cmdargs [OPTION...]

  -t, --textvalue arg  Param text value
  -d, --debug          Enable debugging
  -n, --number arg     Param number (default: 11)
  -f, --file FILE      File
  -h, --help           Print usage

```

#### Credits cxxopts library
[Command line parser](https://github.com/jarro2783/cxxopts)