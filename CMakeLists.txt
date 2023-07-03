cmake_minimum_required(VERSION 3.0.0)
project(AED_Proyecto VERSION 0.1.0)

include(CTest)
enable_testing()

# For the SSL library
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# For the Nana Library
set(NANA_ROOT_DIR "C:/nana") # Reemplaze por el directorio de nana
set(NANA_BINARY_DIR "${NANA_ROOT_DIR}/build")
add_subdirectory(${NANA_ROOT_DIR} ${NANA_BINARY_DIR})

add_executable(AED_Proyecto main.cpp
                            blockchain_files/transaction.h
                            blockchain_files/block.h
                            blockchain_files/blockchain.h
                            data_structures/hashtable.h
                            data_structures/avl.h
                            data_structures/trie.h
                            data_structures/suffixtree.h
                            data_structures/maxheap.h
                            data_structures/minheap.h)

# Link OpenSSL
target_link_libraries(AED_Proyecto ${OPENSSL_LIBRARIES})

# Link Nana
target_link_libraries(AED_Proyecto nana)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)