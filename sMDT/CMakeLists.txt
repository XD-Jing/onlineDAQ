project (sMDTLib)

add_library(${PROJECT_NAME}
    src/monitor.cxx
    src/gui.cxx
    src/sMDT.cxx
    src/server.cxx
    )
#add_library(sub::lib1 ALIAS ${PROJECT_NAME})

target_link_libraries(sMDTLib ${ROOT_LIBRARIES})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

