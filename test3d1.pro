QT += core gui opengl quick

CONFIG += gl
QT += quick quickcontrols2

QML_IMPORT_PATH += $$PWD/path/to/your/custom/module



RESOURCES += qml.qrc

SOURCES += \
        main.cpp \
        star3ditem.cpp

resources.files = main.qml
resources.prefix = /$${TARGET}

# Additional import path used to resolve QML modules in Qt Creator's code model
# Vous pouvez définir ici d'autres chemins si nécessaire
# QML_IMPORT_PATH = $$PWD  # Cette ligne est déjà définie ci-dessus et n'a pas besoin d'être répétée.

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    star3ditem.h
