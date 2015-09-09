
include(../../cmake/common.cmake)
include(../../cmake/qt.cmake)

set( PROJECT_HEADERS 
  JournalDM.h
  JournalDM_Model.h
)

set( PROJECT_SOURCES
  JournalDM_Model.cpp
)

add_definitions( -DJOURNAL_DM_EXPORTS -D_CRT_SECURE_NO_WARNINGS )
add_library( JournalDM SHARED ${PROJECT_SOURCES} ${PROJECT_HEADERS} )
set_target_properties( JournalDM PROPERTIES LINK_INTERFACE_LIBRARIES "" )
target_link_libraries( JournalDM ${PROJECT_LIBRARIES} ${CPPUNIT_LIBRARIES} ${QT_CORE} )

install_files( /include FILES ${PROJECT_HEADERS} )
