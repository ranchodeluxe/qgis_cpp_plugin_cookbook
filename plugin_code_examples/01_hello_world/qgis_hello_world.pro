#QGIS_DIR = /home/junkmob/QGIS-APP/lib/qgis
TEMPLATE = lib
CONFIG = qt
QT += xml qt3support
LIBS += -L/home/junkmob/QGIS-APP/lib -lqgis_core -lqgis_gui
#INCLUDEPATH += $$QGIS_DIR/src/ui $$QGIS_DIR/src/plugins $$QGIS_DIR/src/gui $$QGIS_DIR/src/raster $$QGIS_DIR/src/core $$QGIS_DIR
INCLUDEPATH += /home/junkmob/QGIS-APP/include/qgis
SOURCES = qgis_hello_world.cpp
HEADERS = qgis_hello_world.h
DEST = qgis_hello_world.so
DEFINES += GUI_EXPORT= CORE_EXPORT=
