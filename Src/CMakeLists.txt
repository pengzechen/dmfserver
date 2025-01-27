
file( GLOB main_SRC "*.h" "*.c" )
aux_source_directory(./model     model_SRC)
aux_source_directory(./elr_mpl   elr_mpl_SRC)
aux_source_directory(./conf      conf_SRC)
aux_source_directory(./views     views_SRC)
aux_source_directory(./utility   utility_SRC)
aux_source_directory(./middleware middleware_SRC)
include_directories(${PROJECT_SOURCE_DIR}/include/dmfserver)


if( CMAKE_SYSTEM_NAME STREQUAL "Windows" )
    include_directories(${PROJECT_SOURCE_DIR}/include)

    link_directories("${PROJECT_SOURCE_DIR}/lib")
    link_libraries("libssl")
    link_libraries("libmysql")
    link_libraries("pthreadVC2")
    link_libraries("ws2_32")
    link_libraries("libcrypto")
    link_libraries("libxml2")
    link_libraries("iconv")
    link_libraries("libjansson")
    link_libraries("libpcre32")
    link_libraries("libpcre")
    link_libraries("libjwt")

    # pthread 有冲突
    add_definitions("-DHAVE_STRUCT_TIMESPEC")

    #指定生成目标
    add_executable(server 
    ${main_SRC} 
    ${model_SRC} 
    ${elr_mpl_SRC} 
    ${conf_SRC} 
    ${utility_SRC}
    ${middleware_SRC}
    "./mdb/mdb_operate.c" )

elseif( CMAKE_SYSTEM_NAME STREQUAL "Linux" )

    #include_directories(${PROJECT_SOURCE_DIR}/includelinux)

    find_package(Threads REQUIRED)
    find_package(OpenSSL REQUIRED)
    find_package(LibXml2 REQUIRED)
    find_package(jansson REQUIRED)
    # find_package(pcre REQUIRED)
    # find_package(libjwt REQUIRED)

    link_libraries(pthread mysqlclient ssl crypto xml2 jansson pcre jwt)
    include_directories(
    ${MYSQL_INCLUDE_DIRS} 
    ${OPENSSL_INCLUDE_DIRS} 
    ${LIBXML2_INCLUDE_DIRS} 
    ${JANNSON_INCLUDE_DIRS} 
    ${PCRE_INCLUDE_DIRS}
    ${JWT_INCLUDE_DIRS})

    #指定生成目标
    add_executable(server 
    ${main_SRC} 
    ${model_SRC} 
    ${elr_mpl_SRC} 
    ${conf_SRC} 
    ${utility_SRC}
    ${middleware_SRC}
    "./mdb/mdb_operate.c" )

endif()

# 构建mdb子目录
add_subdirectory("${PROJECT_SOURCE_DIR}/Src/mdb") 

