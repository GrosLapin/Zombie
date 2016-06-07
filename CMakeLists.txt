#Déclaration du projet
project(Zombie)






set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wsign-conversion -Wlogical-op -Wdouble-promotion  -std=c++14 -fno-strict-aliasing -DBOOST_SIMD_NO_STRICT_ALIASING -DNDBUG -pedantic -Ofast -ggdb3 ")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} " )

# Get local directory where .cmake are
set(CMAKE_CXX_COMPILER "gcc")

#Déclaration de l'exécutable
file(GLOB_RECURSE mesFichiers ./*.cpp )
add_executable(
        Zombie
        ${mesFichiers}
)

target_link_libraries (Zombie sfml-graphics)
target_link_libraries (Zombie sfml-window)
target_link_libraries (Zombie sfml-system)
