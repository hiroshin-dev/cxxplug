# Tests

## Running the test

1. Create a build directory and work there
   - `mkdir build && cd build`
2. Generate a build configuration
   - `cmake ..`
   - For Windows, specifies the CPU architecture: `cmake .. -A x64`
3. Build
   - `cmake --build . --parallel 4`
   - For Windows, specifies the configuration: `cmake --build . --config Debug --parallel 4`
4. Run the test
   - `ctest`
   - For Windows, specifies the configuration: `ctest -C Debug`

## Dynamic analysis of memory (Linux only)

1. Run the test with memory check options
   - `ctest -T memcheck`
