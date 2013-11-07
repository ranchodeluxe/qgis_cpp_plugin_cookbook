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
    // Layer QStrings
    QString mLayerPath         = "/home/gcorradini/Dropbox/LINUX_BASE_WORKSPACE/DATA/SHAPES/populated_places_simple/";
    QString mLayerBaseName     = "pop_places";
    QString mProviderName      = "ogr";

    // Get Vector Layer
    QgsVectorLayer * mLayer = new QgsVectorLayer(mLayerPath, mLayerBaseName, mProviderName);


    if (mLayer->isValid())
    {
        QString mFeedback = "layer is valid";
        QString mTag = "HelloWorld";
        QgsMessageLog::instance()->logMessage( mFeedback, mTag, QgsMessageLog::INFO );
    }
    else
    {
        QString mFeedback = "layer NOT valid";
        QString mTag = "HelloWorld";
        QgsMessageLog::instance()->logMessage( mFeedback, mTag, QgsMessageLog::INFO );
    }

    // Add the Vector Layer to the Layer Registry
    QgsMapLayerRegistry::instance()->addMapLayer(mLayer, TRUE);

    // get the map canvas
    QgsMapCanvas* canvas = m_qgis_if->mapCanvas();

    // Add the Layer to the Layer Set
    QList <QgsMapCanvasLayer> mLayerSet;
    mLayerSet.append(QgsMapCanvasLayer(mLayer, TRUE));

    // add it to the canvas
    canvas->setLayerSet( mLayerSet );

}
