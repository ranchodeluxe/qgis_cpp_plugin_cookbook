###Build dependecies

1. You will need QGIS source and all the dependecies. The [build instructions](https://github.com/qgis/QGIS/blob/master/INSTALL#L85-L340) you should follow are very clear.

###Building

1. run `$ qmake qgis_hello_world.pro` to create the Makefile

2. run `make` to build the dynamic .so lib

3. copy or link it to the qgis plugins directory: `sudo cp liqgis_hello_world.so.1.0.0 /usr/lib/qgis/plugins/libqgis_hello_world.so`


