mkdir -p build
cd build
cmake ..
cmake --build . --config Release
ctest -v -C Release # --rerun-failed --output-on-failure