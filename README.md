# hinapi

A template repo to build Node.js native addons **without node-gyp**! Switch to any of your favorite general-prupose build tools. [And there's a blog post](https://kkocdko.site/post/202303261531)

Tested on these platform, see [actions](https://github.com/kkocdko/hinapi/actions):

- Linux: `gcc 12.2.1 + gnu make 4.3`, `gcc 12.2.1 + ninja 1.11.1`.

- Windows: `msvc cl 19.34.31938 x64 + nmake`, `msvc cl 19.35.32216.1 x64 + ninja 1.11.1`, `gcc 12.2.0 + mingw-w64 10.0.0 + ninja 1.11.1`.

- macOS: `clang / llvm 14.0.0`.

## Usage

Optional: [CMake](https://cmake.org) and [Ninja](https://github.com/ninja-build/ninja).

```sh
cmake -B build -G Ninja && cmake --build build
node src/main.js
```

On Linux, without any build tools, put [node-addon-api](https://github.com/nodejs/node-addon-api) and [node-api-headers](https://github.com/nodejs/node-api-headers) into `./third_party`, then:

```sh
mkdir -p build
g++ src/hinapi.cc -o build/hinapi.node \
  -I third_party/node-addon-api \
  -I third_party/node-api-headers/include \
  -shared -fPIC
node src/main.js
```

## Thanks

https://blog.logrocket.com/solving-common-issues-node-gyp/

https://github.com/evanw/esbuild/blob/v0.17.12/lib/npm/node-platform.ts

https://stackoverflow.com/a/74779719/11338291

https://stackoverflow.com/a/17602173/11338291

https://gist.github.com/mmozeiko/7f3162ec2988e81e56d5c4e22cde9977

https://github.com/skeeto/w64devkit/

https://github.com/nodejs/node-addon-api/blob/main/doc/setup.md

<!--

#define NAPI_DISABLE_CPP_EXCEPTIONS
#define NODE_ADDON_API_DISABLE_DEPRECATED

# build type. MinSizeRel | Release | Debug
set(CMAKE_BUILD_TYPE MinSizeRel)

# enable LTO
# set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
# set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

# target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
# -shared -fno-exceptions -fPIC -Wall -Wextra -Os -s -flto -g -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer

# static
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_SEARCH_END_STATIC 1)

# target_link_options(${PROJECT_NAME} PUBLIC -s)
# target_compile_options(${PROJECT_NAME} PUBLIC /MT)
# target_link_options(${PROJECT_NAME} PUBLIC /NODEFAULTLIB:msvcrt.lib)
# include("${PROJECT_SOURCE_DIR}/third_party/vc-ltl/VC-LTL helper for cmake.cmake")
# -shared -fno-exceptions -fPIC -Wall -Wextra -Wl,-Bstatic -Os -s # -g -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer
# ~/misc/apps/node-19.7.0-pc src/main.js

Some of the disadvantages of node-gyp include that it can easily result in problems that are hard to resolve1. Due to historical reasons, using node-gyp can be difficult1. However, node-gyp is a tool which compiles Node.js Addons. Node.js Addons are native Node.js Modules, written in C or C++, which therefore need to be compiled on your machine2. After they are compiled with tools like node-gyp, their functionality can be accessed via require (), just as any other Node.js Module2.

-->
