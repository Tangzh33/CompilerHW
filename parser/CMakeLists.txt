find_package(LLVM REQUIRED)
find_package(BISON REQUIRED)

# Adding option '-Wcounterexamples' to generate conflict counterexamples
# bison_target(parser parser.y main.cc DEFINES_FILE parser.hh COMPILE_FLAGS "-Wcounterexamples")
bison_target(parser parser.y main.cc DEFINES_FILE parser.hh)
add_executable(sysu-parser ${BISON_parser_OUTPUT_SOURCE})
llvm_map_components_to_libnames(LLVM_LIBS support)
target_link_libraries(sysu-parser ${LLVM_LIBS})
target_include_directories(sysu-parser PRIVATE ${LLVM_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TangZ_lib)
add_library(asg_Node ./TangZ_lib/asg_Node.cc)
target_link_libraries(sysu-parser asg_Node)
install(TARGETS sysu-parser)