#ifndef QGIS_HELLO_WORLD_H
#define QGIS_HELLO_WORLD_H

#include "qgisplugin.h"
#include "qgsmapcanvas.h"
#include "qgisinterface.h"
#include <iostream>
#include <QAction>

class HelloWorldPlugin : public QObject, public QgisPlugin
{
   Q_OBJECT

public:
   static const QString s_name, s_description, s_category, s_version, s_icon;
   static const QgisPlugin::PLUGINTYPE s_type;

   HelloWorldPlugin(QgisInterface* qgis_if) : QgisPlugin(s_name, s_description, s_category, s_version, s_type), m_qgis_if(qgis_if)
   {
   }

   // virtual methods from QgisPlugin
   virtual void initGui();
   virtual void unload()
   {
      std::cout << "HelloWorldPlugin::unload" << std::endl;
   }

public slots:
   void StartOverlay();
   void DrawOverlay(QPainter* painter);

private:
   QgisInterface* m_qgis_if;
   QAction* m_action;

};

#endif // #ifndef QGIS_HELLO_WORLD_H
