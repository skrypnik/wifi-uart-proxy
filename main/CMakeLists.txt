file( GLOB_RECURSE PROJECT_HEADERS main/*.h)
file( GLOB_RECURSE PROJECT_SOURCES main/*.cpp)

idf_component_register(

    SRCS main.c modules/wifi.c modules/wifi.h modules/udps.c modules/udps.h
)
