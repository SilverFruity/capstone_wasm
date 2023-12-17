```
source "~/emsdk/emsdk_env.sh"
mkdir build && cd build
emcmake cmake .. 
cmake --build . --target capstone_js
npm install
grunt serve 
```