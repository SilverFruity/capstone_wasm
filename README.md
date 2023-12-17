Usage:

```javascript
CS_ARCH_X86 = 3;
CS_ARCH_ARM = 0;
CS_ARCH_AARCH64 = 1;

CS_MODE_64 = 8;
CS_MODE_ARM = 0;
CS_MODE_32 = 4;

var funcPtr = Module.addFunction(function(instruction, error) {
    console.log(UTF8ToString(instruction));
}, 'vii');
var buffer = [0x55, 0x48, 0x8b, 0x05, 0xb8, 0x13, 0x00, 0x00]
var buffer_ptr = Module._malloc(buffer.length);
Module.writeArrayToMemory(buffer, buffer_ptr);
Module._disassemble(0x10, buffer_ptr, buffer.length, CS_ARCH_X86, CS_MODE_64, funcPtr);
Module._free(buffer_ptr);
```

Example:

![pic](./example.jpeg)



Build and Run:

support test on MacOS

cmake version 3.27.1

emcc 3.1.51

```shell
source "~/emsdk/emsdk_env.sh"
mkdir build && cd build
emcmake cmake ..
cmake --build . --target capstone_js
npm install
grunt serve
```
