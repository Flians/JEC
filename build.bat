if not exist build md build
cd build

if "%1" == "" (
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
) else (
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=%1 ..
)

make