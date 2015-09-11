
import os

ignore = {}

def warn( theFile, theComment, theLine, theMsg ):
  if ( theFile in ignore ) and ( theLine in ignore[theFile] ):
    return
  print "Warning:", theMsg
  print "  File: '%s'" % theFile
  print "  Line: '%i'" % theLine
  print "  Comment:"
  for aLine in theComment.split( "\n" ):
    print "  " + aLine

def check_comment( theFile, theComment, theLine, isTest ):
  if len( theComment.strip() )==0:
    return
  if '@file' in theComment and not r'\brief' in theComment:
    warn( theFile, theComment, theLine, r"file should contain \brief description" )
  if r'\class' in theComment and not r'\brief' in theComment:
    warn( theFile, theComment, theLine, r"class should contain \brief description" )
  if r'\struct' in theComment and not r'\brief' in theComment:
    warn( theFile, theComment, theLine, r"struct should contain \brief description" )
  if not( '@' in theComment ) and not( '\\' in theComment ) and not ( r'\test' in theComment ) and ( isTest ):
    warn( theFile, theComment, theLine, r"the test methods should be commented using \test command" )
  
def check_file( theFile, isTest, isHeader ):
  global files
  #print 'Checking %s...' % theFile
  aLines = open( theFile, 'r' ).readlines()
  
  isComment = False
  isFileFound = False
  isFriendFound = False
  isCode = False
  aTemplate = 0
  aTemplBr = 0
  aCommentLine = 0
  aComment = ""
  aEnum = False

  i = 1
  for aLine in aLines:
    if 'this->' in aLine:
      warn( theFile, "", aLine[:-1], r"this-> is found" )

    if '@file' in aLine:
      isFileFound = True
    if 'friend' in aLine:
      isFriendFound = True
    if '/**' in aLine and '*/' in aLine:
      check_comment( theFile, aLine, i, isTest )
    elif '/**' in aLine:
      isComment = True
      aComment = ""
      aCommentLine = i
    elif '*/' in aLine:
      isComment = False
      check_comment( theFile, aComment, aCommentLine, isTest )
    elif isComment:
      aComment = aComment + aLine

    if '\code' in aLine:
      isCode = True
    if '\endcode' in aLine:
      isCode = False

    if isHeader:
      pi = aLine.find( '}' )
      if pi>=0 and ( pi==len(aLine)-1 or aLine[pi+1]!=';' ) and aTemplate==0 and not isCode:
        warn( theFile, '', i, 'method in header is detected' )
    i = i + 1

    if 'template<class' in aLine or 'template <class' in aLine:
      aTemplate = aTemplate + 1
      #print aLine[:-1]
      #print "Template:", aTemplate
      #print
    elif aTemplate>0:
      aTemplBrWas0 = aTemplBr == 0
      aTemplBr = aTemplBr + aLine.count( '{' )
      aTemplBr = aTemplBr - aLine.count( '}' )
      if aTemplBr == aTemplate-1 and not aTemplBrWas0:
        aTemplate = aTemplate - 1
        #print aLine[:-1]
        #print "Template:", aTemplate
        #print

    aLineTr = aLine.strip()
    if 'enum' in aLineTr: # candidate to enumeration declaration
      aParts = aLineTr.split( ' ' )
      if aParts[0]=='enum':
        aEnum = True
    elif aEnum and '};' in aLineTr:
      aEnum = False
    elif len(aLineTr)>0 and aEnum and not '{' in aLineTr and not '}' in aLineTr and not '///<' in aLineTr:
      warn( theFile, '"'+aLineTr+'"'+'\n', i-1, 'Enum item is not documented' )

    #print aLine[:-1]
    #print aTemplate, aTemplBr
    #print ''

  if not isFileFound:
    warn( theFile, "", 0, "@file is not found" )
  #if isFriendFound:
  #  warn( theFile, "", 0, "'friend' is found" )

def check_folder( theFolder, isTest ):
  aFiles = os.listdir( theFolder ); 
  aHeaders = filter( lambda x: x.endswith('.h'), aFiles );
  aSources = filter( lambda x: x.endswith('.cpp'), aFiles );
  aSourcesC = filter( lambda x: x.endswith('.c'), aFiles );
  for aHeader in aHeaders:
    check_file( theFolder + '/' + aHeader, False, True )
  for aSource in aSources:
    check_file( theFolder + '/' + aSource, isTest, False )
  for aSource in aSourcesC:
    check_file( theFolder + '/' + aSource, isTest, False )




check_folder( '../src/TestLib', False )
check_folder( '../src/JournalDM', False )
check_folder( '../src/JournalDM_tests', True )
check_folder( '../src/JournalGUI', False )
check_folder( '../src/JournalConsole', True )
