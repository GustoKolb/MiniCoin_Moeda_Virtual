cmake_minimum_required(VERSION 3.5)
project(MiniCoin CXX)

include(CheckIncludeFileCXX)

# ---------------------------------------------------------------------
# DETECTAR SUPORTE DE LINGUAGEM
# ---------------------------------------------------------------------
check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Nada a fazer
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Forçar C++20
set(CMAKE_CXX_STANDARD 20)

# ---------------------------------------------------------------------
# DEPENDÊNCIAS COMUNS
# ---------------------------------------------------------------------
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
find_package(Drogon CONFIG REQUIRED)
find_package(Trantor CONFIG REQUIRED)
find_package(ixwebsocket REQUIRED)

# ---------------------------------------------------------------------
# SERVIDOR DROGON
# ---------------------------------------------------------------------
set(SERVER_TARGET miniCoin)

add_executable(${SERVER_TARGET}
    main.cc
    controllers/BlockchainWebSocket.cc
    models/BlockChain.cpp
    models/Currency.cpp
    models/Message.cpp
)

target_link_libraries(${SERVER_TARGET}
    PRIVATE
    Drogon::Drogon
    Trantor::Trantor
    ${JSONCPP_LIBRARIES}
)

target_include_directories(${SERVER_TARGET}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${JSONCPP_INCLUDE_DIRS}
)

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

drogon_create_views(${SERVER_TARGET}
    ${CMAKE_CURRENT_SOURCE_DIR}/views
    ${CMAKE_CURRENT_BINARY_DIR}
)

# ---------------------------------------------------------------------
# CLIENTE COM IXWEBSOCKET
# ---------------------------------------------------------------------
set(CLIENT_TARGET clientCoin)

add_executable(${CLIENT_TARGET}
    client.cc
    models/Message.cpp
)

target_link_libraries(${CLIENT_TARGET}
    PRIVATE
    ixwebsocket::ixwebsocket
    Drogon::Drogon
    Trantor::Trantor
    ${JSONCPP_LIBRARIES}
)

target_include_directories(${CLIENT_TARGET}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${JSONCPP_INCLUDE_DIRS}
)

# -------------------------------------------
