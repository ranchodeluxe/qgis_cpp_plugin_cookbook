###Build dependecies

1. You will need QGIS installed with all it's [dependencies such as Qt, Proj4, GEOS, GDAL/OGR](http://hub.qgis.org/wiki/17/Building_QGIS_from_Source?version=2) 

2. You will also need the `libqgis-dev` and `libqt4-dev` libraries

###Building

1. run `$ qmake qgis_hello_world.pro` to create the Makefile

2. run `make` to build the dynamic .so lib

3. copy or link it to the qgis plugins directory: `sudo cp liqgis_hello_world.so.1.0.0 /usr/lib/qgis/plugins/libqgis_hello_world.so`


