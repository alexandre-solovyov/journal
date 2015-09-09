
/**
  @file
  \brief Declaration of macros for exceptions testing
*/

#pragma once

#include <cppunit/extensions/HelperMacros.h>
#include <stdexcept>

/**
  Macro definition for the start of waited exception block
*/
#define WAIT_EXCEPTION                                                                            \
  {                                                                                               \
    bool isCaught = false;                                                                        \
    std::string aCaughtException;                                                                 \
    try                                                                                           \
    {                                                                                             \

/**
  Macro definition for the assertion of of waited exception
  @param ExceptionClass the expected exception's class
*/
#define ASSERT_EXCEPTION( ExceptionClass )                                                        \
    }                                                                                             \
    catch( const ExceptionClass& )                                                                \
    {                                                                                             \
      isCaught = true;                                                                            \
      aCaughtException = #ExceptionClass;                                                         \
    }                                                                                             \
    catch( const std::exception& theOther )                                                       \
    {                                                                                             \
      isCaught = true;                                                                            \
      aCaughtException = typeid( theOther ).name();                                               \
    }                                                                                             \
    catch( ... )                                                                                  \
    {                                                                                             \
      isCaught = true;                                                                            \
      aCaughtException = "Unknown exception";                                                     \
    }                                                                                             \
    CPPUNIT_ASSERT_EQUAL_MESSAGE( "Exception is not caught", true, isCaught );                    \
    CPPUNIT_ASSERT_EQUAL_MESSAGE(                                                                 \
      "Caught exception", std::string( #ExceptionClass ), aCaughtException );                     \
  }                                                                                               \
                                                                                                  \


