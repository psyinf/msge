# msge
Minimal Space Game Engine


Setup
Install conan (https://docs.conan.io/en/latest/installation.html)

Create conan profile (optional)

* conan profile new default --detect
* conan profile update settings.compiler.cppstd=gnu23 default

Build missing packages
* conan  install . --build=missing  --install-folder=../build/msge


