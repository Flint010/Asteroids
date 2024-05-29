**Asteroids game**

An example of this game is taken from the book Sfml Blueprints by Maxime Barbier

To install the SFML library I use vcpkg

In vcpkg directory:
```
vcpkg install sfml
vcpkg integrate
```

In Asteroids repository:
```bash
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=<vcpkg-root>/scripts/buildsystems/vcpkg.cmake
cmake --build .
```
