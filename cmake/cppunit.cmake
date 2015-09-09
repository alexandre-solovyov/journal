
cmake_minimum_required ( VERSION 2.6 )
cmake_policy ( SET CMP0011 NEW )

include_directories ( $ENV{CPPUNITDIR}/include )
link_directories    ( $ENV{CPPUNITDIR}/lib )

IF( ${WIN32} )
  set( CPPUNIT_LIBRARIES optimized cppunit_dll debug cppunitd_dll )
ELSE()
  set( CPPUNIT_LIBRARIES cppunit )
ENDIF()
