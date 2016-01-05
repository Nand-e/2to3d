HEADERS       = glwidget.h \
    camera.h \
    pmatricies.h \
    manager.h \
    project.h \
    mainwindow.h \
    itemform.h \
    projecttreeview.h \
    objectItem.h \
    treemodel.h \
    quadObj.h \
    cubeObj.h \
    emptyobj.h \
    imageitem.h \
    obj3dfactory.h
SOURCES       = glwidget.cpp \
                main.cpp \
    camera.cpp \
    pmatricies.cpp \
    manager.cpp \
    project.cpp \
    mainwindow.cpp \
    itemform.cpp \
    projecttreeview.cpp \
    treemodel.cpp \
    objectItem.cpp \
    quadObj.cpp \
    cubeObj.cpp \
    emptyobj.cpp \
    imageitem.cpp \
    obj3dfactory.cpp
RESOURCES     = textures.qrc
QT           += opengl widgets

INCLUDEPATH += C:\OpenCV\opencv\build\include \

LIBS += -LC:\\OpenCV\\opencv\\build\\x86\\vc10\\lib\
    -lopencv_core249d \
    -lopencv_highgui249d \
    -lopencv_imgproc249d \
    -lopencv_features2d249d \
    -lopencv_calib3d249d \

FORMS += \
    mainwindow.ui \
    itemform.ui


