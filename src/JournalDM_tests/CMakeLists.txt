
include(../../cmake/common.cmake)
include(../../cmake/cppunit.cmake)
include(../../cmake/qt.cmake)

set( PROJECT_HEADERS 
  JournalDM_Tests.h
  JournalDM_TestModel.h
)

set( PROJECT_SOURCES
  JournalDM_TestModel.cpp
  JournalDM_Tests.cpp
)

include_directories( ../JournalDM ../TestLib )
set( PROJECT_LIBRARIES JournalDM TestLib )

add_definitions( -D_CRT_SECURE_NO_WARNINGS )
add_executable( JournalDM_tests ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
target_link_libraries( JournalDM_tests ${PROJECT_LIBRARIES} ${CPPUNIT_LIBRARIES} ${QT_CORE} )

IF( ${WIN32} )
  add_custom_command( TARGET JournalDM_tests POST_BUILD COMMAND $(TargetPath) COMMENT "Running tests" )
ENDIF()
