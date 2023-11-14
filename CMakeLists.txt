cmake_minimum_required(VERSION 3.16)

project(loggit
  VERSION 0.1.0
  LANGUAGES CXX
)

find_package(cupcake 0.4.1 REQUIRED)

cupcake_project()

# imports
target_link_libraries(${PROJECT_NAME}.dependencies PUBLIC
)

cupcake_add_library(loggit)
target_link_libraries(${this} PUBLIC ${PROJECT_NAME}.dependencies)

cupcake_add_executable(loggit)
target_link_libraries(${this} PRIVATE ${PROJECT_NAME}.libloggit)

cupcake_add_tests()

cupcake_install_project()
cupcake_install_cpp_info()
