## opengl engine uni 2014

An opengl engine (old pipeline rendering) project I co-made for a university course in 2014. Right now mostly used as a demo of how to use cmake and vcpkg.

### Building with vcpkg and cmake

1. Update submodules
```
git submodule init
git submodule update
```
2. Build with cmake (msvc)
```
# in msvc developer prompt
mkdir build-msvc
cd build-msvc
cmake -DVCPKG_OVERLAY_PORTS=../port_overlays -DVCPKG_FEATURE_FLAGS=versions,manifests -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake ..
# build the solution in visual studio
```
3. Build with cmake (mingw)
```
# in msys2 mingw shell
mkdir build-mingw
cd build-mingw
cmake -DVCPKG_OVERLAY_PORTS=../port_overlays -DVCPKG_FEATURE_FLAGS=versions,manifests -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic -DCMAKE_TOOLCHAIN_FILE=../vcpkg/scripts/buildsystems/vcpkg.cmake -GNinja ..
ninja
```
4. Build using presets (linux)
```
cmake -S . --preset=default
make --build --preset=default
```

