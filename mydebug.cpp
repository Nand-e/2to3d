#include "mydebug.h"

#include <QTextEdit>
#include <QString>

MyDebug::MyDebug() {}

MyDebug & MyDebug::operator<< (  int rhv ) {
    if ( out != NULL ) {
        emit SendText(QString::number(rhv));
    }
    return *this;
}

MyDebug & MyDebug::operator<< (  unsigned char * rhv ) {
    if ( out != NULL ) {
        emit SendText(QString::number( ( int ) rhv));
    }
    return *this;
}

MyDebug& MyDebug::operator<< ( const char * text ) {
    if ( out != NULL ) {
        emit SendText(QString(text));
    }
    return *this;
}


MyDebug& MyDebug::operator<< ( QString & str) {
    if ( out != NULL ) {
        emit SendText(str);
    }
    return * this;
}

MyDebug& MyDebug::operator<< ( float f ) {
    if ( out != NULL) {
         emit SendText(QString::number( f ));
    }
    return * this;
}

 void MyDebug::SendTextTo ( QString str ) {
    mutex.lock();
    out->moveCursor (QTextCursor::End);
    out->insertPlainText( str);
    out->moveCursor (QTextCursor::End);
    mutex.unlock();
 }
