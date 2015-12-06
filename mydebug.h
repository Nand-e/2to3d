#ifndef MYDEBUG_H
#define MYDEBUG_H

#include <QPlainTextEdit>

class MyDebug : public QObject
{
    Q_OBJECT
public:
    MyDebug();
    MyDebug( QObject * parent) { this->parent = parent; }
    void set ( QPlainTextEdit * out ) {
        this->out = out;

        connect( this, SIGNAL(SendText(QString)), this, SLOT( SendTextTo(QString)));
    }

    MyDebug& operator<< ( int rhv );
    MyDebug& operator<< ( float );
    MyDebug& operator<< ( const char * text );
    MyDebug& operator<< ( QString& str);
    MyDebug& operator<< ( unsigned char * rhv );

    QMutex mutex;

    signals: void SendText (QString str);

    public slots:
             void SendTextTo ( QString str );


private:
    QPlainTextEdit *out;
    QObject * parent;

};

#endif // MYDEBUG_H
