# Simple CLI - CPP Template for VS Code
#### Compile
```
g++ *.cpp -o cmdargs
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

#### Grab cxxopts library
```
git submodule add https://github.com/jarro2783/cxxopts extern/cxxopts
```
