find_package(LLVM REQUIRED)

# Set the debug flags for the generator
set(CMAKE_CXX_FLAGS "-g")
add_executable(sysu-generator main.cc)
llvm_map_components_to_libnames(LLVM_LIBS core support)
target_link_libraries(sysu-generator ${LLVM_LIBS})
target_include_directories(sysu-generator PRIVATE ${LLVM_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TangZ_lib)
add_library(ast ./TangZ_lib/ast.cc)
target_link_libraries(sysu-generator ast)
install(TARGETS sysu-generator)
