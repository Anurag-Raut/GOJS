# GOJS
GOJS is an interpreter built using C++ and CMake. It features a unique syntax that combines elements of Go and JavaScript. The interpreter uses an Abstract Syntax Tree (AST) tree-walk mechanism to evaluate and execute code.

## Table of Contents
- [Installation](#installation)  
- [Usage](#usage)  
- [Syntax](#syntax)  
- [Contact](#contact)

## Installation
Prerequisites
C++ compiler (C++11 or higher)
CMake (version 3.10 or higher)
### Building GOJS
**Clone the repository**:

```
git clone https://github.com/yourusername/GOJS.git
&&
cd GOJS
```
Create a build directory :

```
mkdir build
```

use cmake to build
```
cmake -B build -S .
```
Run CMake and build the project:


The gojs executable will be available in the build directory.

## Usage
To run a GOJS script, use the following command:


```
./build/compiler /path/to/file
```
second argument is the file which contains the code to be executed


## Syntax
GOJS combines elements of Go and JavaScript. Here are some examples to get you started:

### Variables

```
var x = 20
var y = "anurag"
```

### Functions
```
function add(a, b) {
    return a + b;
}

let result = add(5, 3);
```
**Control Flow**  
```
var x = 10
var y = 20 

if (x > y) {
    print("x is greater than y")
} else {
    print("x is not greater than y")
}
```

**Loops**
- For Loop
```
for (var i = 0; i < 10; i++) {
    print(i);
}
```

- While Loop
```
var i=0
while (i<10) {
    print(i)
    i=i+1
}
```

## Contact
For any questions or feedback, please contact anurag.raut.86@gmail.com.
