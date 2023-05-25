cmake_minimum_required(VERSION 3.0.0)
project(AED_Proyecto VERSION 0.1.0)

include(CTest)
enable_testing()

# For the SSL library
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(AED_Proyecto main.cpp transaction.h block.h blockchain.h hashtable.h)

# Link OpenSSL
target_link_libraries(AED_Proyecto ${OPENSSL_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)