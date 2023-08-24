project(fft86 CXX C ASM)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -g --fast-math")

set(fft_source_files
    src/butterfly.cpp
    src/factors.cpp
    src/fft.cpp
    src/fft86.cpp
    src/fftw.cpp
    src/scramble.cpp
    src/transpose.cpp
    src/twiddles.cpp
)      

set(fft_include_files
    fft86/butterfly.hpp
    fft86/defs.hpp
    fft86/factors.hpp
    fft86/fft.hpp
    fft86/fftw.hpp
    fft86/scramble.hpp
    fft86/timer.hpp
    fft86/transpose.hpp
    fft86/twiddles.hpp
    fft86/util.hpp
    fft86/vec.hpp
)

add_executable( fft86 ${fft_source_files} ${fft_header_files} )
target_include_directories(fft86 PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(fft86 PUBLIC simd fftw3 simd)

 