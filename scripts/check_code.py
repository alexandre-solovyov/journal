
import subprocess


aCppCheckApp  = 'cppcheck'


def add( theList, theItem ):
  if type(theItem) is list:
    for aSubItem in theItem:
      theList.append( aSubItem )
  else:
    theList.append( theItem )

aFoldersList  = [
  'JournalConsole', 'JournalDM', 'JournalDM_tests', 'JournalGUI', 'TestLib'
]

aSrcDir       = '..\src'
aSuppressions = 'check_code.suppressions'
aPlatform     = 'win64'
aThreadNum    = 1

aTypes        = ['style', 'performance', 'portability']
#aTypes.append( 'unusedFunction' )
aTemplate     = '{file}({line}): {severity} {id}: {message}'

aCmd = []
add( aCmd, aCppCheckApp )
add( aCmd, '--enable=%s' % ( ','.join( aTypes ) ) )
add( aCmd, ['--inconclusive', '--std=posix'] )
add( aCmd, ['-j', str( aThreadNum ) ] )
add( aCmd, '--template="%s"' % aTemplate )
add( aCmd, '--platform=%s' % aPlatform )
add( aCmd, '--suppressions-list=%s' % aSuppressions )
add( aCmd, '-j 4' )
for aDir in aFoldersList:
  add( aCmd, ['-I', '%s/%s' % ( aSrcDir, aDir ) ] )
add( aCmd, ['%s/%s' % ( aSrcDir, aDir ) for aDir in aFoldersList] )

aCmdLine = ' '.join( aCmd )
print( aCmdLine )

aFile = open( 'check_code_%s.log' % aPlatform, 'w' )
#aFile.write( aCmdLine )
aProcess = subprocess.Popen( aCmdLine, bufsize=1, stdout=None, stderr=aFile, universal_newlines=True, shell=True )  #subprocess.PIPE
(stdout, stderr) = aProcess.communicate()   # to wait the process end
aFile.close()
