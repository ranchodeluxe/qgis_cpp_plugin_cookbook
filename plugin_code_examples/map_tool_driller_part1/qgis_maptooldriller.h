#ifndef QGIS_MAPTOOLDRILLER_H
#define QGIS_MAPTOOLDRILLER_H

#include "qgsmaptoolemitpoint.h"
#include "maptooldriller.h" // not used in part1
#include "qgisplugin.h"
#include "qgsmapcanvas.h"
#include "qgisinterface.h"
#include "qgsvectorlayer.h"
#include "qgsmessagelog.h"
#include "qgsmaplayerregistry.h"
#include <iostream>
#include <QAction>

class Qgis_MapToolDrillerPLugin : public QObject, public QgisPlugin
{
   Q_OBJECT

public:
   static const QString s_name, s_description, s_category, s_version, s_icon;

   static const QgisPlugin::PLUGINTYPE s_type;

   Qgis_MapToolDrillerPLugin(QgisInterface* qgis_if) : 
        QgisPlugin(s_name, s_description, s_category, s_version, s_type), m_qgis_if(qgis_if)
   {

   }

   // virtual methods from QgisPlugin
   virtual void initGui();

   virtual void unload()
   {
      std::cout << "Qgis_MapToolDrillerPLugin::unload" << std::endl;
   }

public slots:
   void StartOverlay();

   void handleCanvasClick(const QgsPoint&);

private:
   QgisInterface* m_qgis_if;

   QAction* m_action;

   QgsMapToolEmitPoint *mEmitPointTool;

};

#endif // #ifndef QGIS_MAPTOOLDRILLER_H
