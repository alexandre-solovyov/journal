
#pragma once

#include <QString>

QString GetTestFile( const QString& theRelativePath );
const QString& operator << ( std::ostream& theStream, const QString& theLine );
