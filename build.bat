if not exist build md build
cd build

if "%1" == "" (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
) else (
    cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=%1 ..
)

make