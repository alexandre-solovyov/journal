
include(../../cmake/common.cmake)
include(../../cmake/qt.cmake)

set( PROJECT_HEADERS 
)

set( PROJECT_SOURCES
  JournalConsole.cpp
)

include_directories( ../JournalDM )
set( PROJECT_LIBRARIES JournalDM )

add_definitions( -D_CRT_SECURE_NO_WARNINGS )
add_executable( JournalConsole ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
target_link_libraries( JournalConsole ${PROJECT_LIBRARIES} ${QT_CORE} )
