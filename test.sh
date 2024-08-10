mkdir -p build
cd build
cmake ..
cmake --build . --config Release
ctest -V -C Release # --rerun-failed --output-on-failure