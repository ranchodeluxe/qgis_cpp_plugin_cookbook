#include "qgis_hello_world.h"

/*static*/ const QString HelloWorldPlugin::s_name = QObject::tr("Hello World Plugin");
/*static*/ const QString HelloWorldPlugin::s_description = QObject::tr("Sample Plugin");
/*static*/ const QString HelloWorldPlugin::s_category = QObject::tr("Plugins");
/*static*/ const QString HelloWorldPlugin::s_version = QObject::tr("Version 5.2.0");
/*static*/ const QString HelloWorldPlugin::s_icon = "";
/*static*/ const QgisPlugin::PLUGINTYPE HelloWorldPlugin::s_type = QgisPlugin::UI;

QGISEXTERN QgisPlugin* classFactory(QgisInterface* qgis_if)
{
   std::cout << "::classFactory" << std::endl;
   return new HelloWorldPlugin(qgis_if);
}

QGISEXTERN QString name()
{
   std::cout << "::name" << std::endl;
   return HelloWorldPlugin::s_name;
}

QGISEXTERN QString description()
{
   std::cout << "::description" << std::endl;
   return HelloWorldPlugin::s_description;
}

QGISEXTERN QString category()
{
   std::cout << "::category" << std::endl;
   return HelloWorldPlugin::s_category;
}

QGISEXTERN int type()
{
   std::cout << "::type" << std::endl;
   return HelloWorldPlugin::s_type;
}

QGISEXTERN QString version()
{
   std::cout << "::version" << std::endl;
   return HelloWorldPlugin::s_version;
}

QGISEXTERN QString icon()
{
   std::cout << "::icon" << std::endl;
   return HelloWorldPlugin::s_icon;
}

QGISEXTERN void unload(QgisPlugin* plugin)
{
   std::cout << "::unload" << std::endl;
   delete plugin;
}

/*virtual*/ void HelloWorldPlugin::initGui()
{
   std::cout << "HelloWorldPlugin::initGui" << std::endl;

   // add an action to the menu
   m_action = new QAction(QIcon("" ), tr("Hello World"), this);
   m_action->setWhatsThis(tr("Draw on the map canvas."));
   connect(m_action, SIGNAL(triggered()), this, SLOT(StartOverlay()));
   m_qgis_if->addRasterToolBarIcon(m_action);
   m_qgis_if->addPluginToMenu(tr("&Hello World"), m_action);
}

void HelloWorldPlugin::StartOverlay()
{
   std::cout << "HelloWorldPlugin::StartOverlay" << std::endl;

   // get the map canvas
   QgsMapCanvas* canvas = m_qgis_if->mapCanvas();

   // connect to the render complete signal
   connect(canvas, SIGNAL(renderComplete(QPainter*)),
      this, SLOT(DrawOverlay(QPainter*)));

   // zoom out for fun
   canvas->zoomOut(); // wheeeeee!!!
}

void HelloWorldPlugin::DrawOverlay(QPainter* painter)
{
   std::cout << "HelloWorldPlugin::DrawOverlay" << std::endl;
   painter->drawRect(20, 20, 60, 60);
}
