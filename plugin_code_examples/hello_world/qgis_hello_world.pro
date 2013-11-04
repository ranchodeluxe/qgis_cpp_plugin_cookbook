#QGIS_DIR = /home/marco/src/qgis
TEMPLATE = lib
CONFIG = qt
QT += xml qt3support
unix:LIBS += -L/$$QGIS_DIR/lib -lqgis_core -lqgis_gui
#INCLUDEPATH += $$QGIS_DIR/src/ui $$QGIS_DIR/src/plugins $$QGIS_DIR/src/gui $$QGIS_DIR/src/raster $$QGIS_DIR/src/core $$QGIS_DIR
INCLUDEPATH += /usr/include/qgis
SOURCES = qgis_hello_world.cpp
HEADERS = qgis_hello_world.h
DEST = qgis_hello_world.so
DEFINES += GUI_EXPORT= CORE_EXPORT=
