
include(../../cmake/common.cmake)
include(../../cmake/cppunit.cmake)

set( PROJECT_HEADERS 
  TestLib.h
  TestLib_Exception.h
  TestLib_Listener.h
  TestLib_PerformanceTest.h
  TestLib_Runner.h
)

set( PROJECT_SOURCES
  TestLib.cpp
  TestLib_Listener.cpp
  TestLib_PerformanceTest.cpp
  TestLib_Runner.cpp
)

add_definitions( -DTESTLIB_EXPORTS -D_CRT_SECURE_NO_WARNINGS )
add_library( TestLib SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
set_target_properties( TestLib PROPERTIES LINK_INTERFACE_LIBRARIES "" )
target_link_libraries( TestLib ${PROJECT_LIBRARIES} ${CPPUNIT_LIBRARIES} )

install_files( /include FILES ${PROJECT_HEADERS} )
