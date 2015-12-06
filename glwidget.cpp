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
#include <QtOpenGL>

#include "glwidget.h"
#include "Globals.h"
#include "manager.h"

#include "QVector3D"

GLWidget::GLWidget(QWidget *parent, QGLWidget *shareWidget, Manager & man1 )
    : QGLWidget(parent, shareWidget) , man ( man1 )
{
    clearColor = QColor (50, 20 , 50 , 255);
    program = 0;
}

GLWidget::~GLWidget()
{
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(200, 200);
}


void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_CULL_FACE);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);   

    #define PROGRAM_VERTEX_ATTRIBUTE 0
    #define PROGRAM_TEXCOORD_ATTRIBUTE 1
    #define ProgramColor 2
    InitShaders();
}


/*
 * Draw background image
 * *************************************/
void GLWidget::DrawBack() {
    man.mainproject->drawBackground(*this);
}


void GLWidget::paintGL()
{
    qglClearColor(clearColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawBack();
    man.mainproject->drawObjects( *this );

    return;
}

void GLWidget::resizeGL(int width, int height)
{
     glViewport( 0, 0, width, height);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent * wevent) {
    man.freeCamera->Step( 0, wevent->delta() /100 );            // TODO
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    float dx = ( float ) ( event->x() - lastPos.x() )/ 5;
    float dy = ( float ) ( event->y() - lastPos.y() )/ 5;

    if (event->buttons() & Qt::RightButton) {
        man.freeCamera->RotY ( dx );
        man.freeCamera->RotX ( dy );

    } else if (event->buttons() & Qt::LeftButton) {
        man.freeCamera->UpDown( dy / 10  );
        man.freeCamera->LeftRight( dx /10 );
    }
    lastPos = event->pos();
}

void GLWidget::mouseReleaseEvent(QMouseEvent * /* event */)
{
    emit clicked();
}


void GLWidget::InitShaders() {
    QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
    const char *vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "uniform mediump vec4 color;\n"
        "varying mediump vec4 color1;\n"
     //   "vec4 col2;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "    color1 = color;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);
    const char *fsrc =
        "uniform sampler2D texture;\n"
        "varying vec4 color1;\n"
        "varying mediump vec4 texc;\n"
        "vec4 cl; \n"
        "void main(void)\n"
        "{\n"
        "    cl = texture2D(texture, texc.st); \n"
        "    gl_FragColor = cl * color1; \n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program2 = new QGLShaderProgram(this);
    program2->addShader(vshader);
    program2->addShader(fshader);
    program2->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program2->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program2->link();

    //**********************************************************************
    vshader = new QGLShader(QGLShader::Vertex, this);
    vsrc =
            "attribute highp vec4 vertex;\n"
            "varying mediump vec4 colorout;\n"
            "uniform mediump mat4 matrix;\n"
            "uniform mediump vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    colorout = color;\n"
            "    gl_Position = matrix * vertex;\n"
            "}\n";
    vshader->compileSourceCode(vsrc);

    fshader = new QGLShader(QGLShader::Fragment, this);
    fsrc =
        "varying mediump vec4  colorout;\n"
        "vec4 color;\n"
        "void main(void)\n"

        "{\n"
            "    gl_FragColor = colorout ;\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    solidcolorp = new QGLShaderProgram(this);
    solidcolorp->addShader(vshader);
    solidcolorp->addShader(fshader);
    solidcolorp->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    solidcolorp->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    solidcolorp->link();

    /*
     * *************************************/
    vshader = new QGLShader(QGLShader::Vertex, this);
    vsrc =
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "varying mediump vec4 texc;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    fshader = new QGLShader(QGLShader::Fragment, this);
    fsrc =
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "vec4 col;\n"
        "void main(void)\n"
        "{\n"
        "    col = texture2D(texture, texc.st);\n"
   //     "    if ( col.r < 0.1 && col.g < 0.1 ) col *= vec4(1,1,1,0.2 ); \n"
        "    gl_FragColor = col;\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program = new QGLShaderProgram(this);
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->link();
}


/*    QMatrix4x4 m;

    program->enableAttributeArray(PROGRAM_VERTEX_ATTRIBUTE);
    program->enableAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    program->setAttributeArray(PROGRAM_VERTEX_ATTRIBUTE, vertices.constData());
    program->setAttributeArray(PROGRAM_TEXCOORD_ATTRIBUTE, texCoords.constData());
    program->bind();

    for ( int y =0; y< 10; y+=2)
    for ( int x =0; x< 10; x+=3 ){

        m = manager->actualCamera->getMatrix();                         // Camera matrix
        m.translate(  -7.5+ (float) x , 0 ,  - 20 - y );    // Model to word

        program->setUniformValue("matrix", m);

        for (int i = 0; i < 6; ++i) {
            glBindTexture(GL_TEXTURE_2D, textures[i]);
            glDrawArrays(GL_TRIANGLE_FAN, i*4, 4);
        }
    }
*/
