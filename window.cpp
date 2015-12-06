/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "glwidget.h"
#include "window.h"
#include "Globals.h"
//#include "opencv/highgui.h"

Window::Window()
{
    QBoxLayout *mainLayout = new QBoxLayout( QBoxLayout::TopToBottom );

    QColor clearColor ( 0, 50 , 0 , 255 );


    scroll = new QScrollBar ( Qt::Horizontal );

    glWidget= new GLWidget(0, 0);

    glWidget->setClearColor(clearColor);

    mainLayout->addWidget(glWidget);
    mainLayout->addWidget( scroll );
    setLayout(mainLayout);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
    connect(scroll, SIGNAL(valueChanged(int)), glWidget, SLOT(SetViewAngle(int)));

    installEventFilter(this);
    timer->start(20);

    setWindowTitle(tr("Textures"));
}

void Window::keyPressEvent(QKeyEvent *event) {
    if ( event->type() == QKeyEvent::KeyPress) {
        switch ( event->key() ) {
            case Qt::Key_W:
                manager->camera->Step(0, 0.1f); break;
            case Qt::Key_S:
                manager->camera->Step(0, -0.1f); break;
            case Qt::Key_A:
                manager->camera->Step( 2.0f, 0 ); break;
            case Qt::Key_D:
                manager->camera->Step( -2.0f, 0); break;
            case Qt::Key_Q:
                manager->camera->UpDown( 0.05f ); break;
            case Qt::Key_Y:
                manager->camera->UpDown( -0.05f ); break;




        }
     }
}

void Window::rotateOneStep()
{
    glWidget ->rotateBy(+2 * 16, +2 * 16, -1 * 16);
}
