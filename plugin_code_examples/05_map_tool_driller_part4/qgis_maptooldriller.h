#ifndef QGIS_MAPTOOLDRILLER_H
#define QGIS_MAPTOOLDRILLER_H

#include "maptooldriller.h" 

#include "qgisplugin.h"
#include "qgsmapcanvas.h"
#include "qgisinterface.h"
#include "qgsvectorlayer.h"
#include "qgsvectordataprovider.h"
#include "qgsmessagelog.h"
#include "qgsmaplayerregistry.h"
#include <iostream>

// forward declarations
class QAction;
class QToolBar;
class QToolButton;
class QPushButton;
class QDockWidget;
class QLineEdit;
class QIcon;
class QLabel;

class Qgis_MapToolDrillerPLugin : public QObject, public QgisPlugin
{
   Q_OBJECT

public:
    static const QString s_name, s_description, s_category, s_version, s_icon;

    static const QgisPlugin::PLUGINTYPE s_type;

    static const QString mTag;

    //! constructor
    Qgis_MapToolDrillerPLugin(QgisInterface* qgis_if) : 
        QgisPlugin(s_name, s_description, s_category, s_version, s_type), m_qgis_if(qgis_if)
    {

    }

    //! destructor
    virtual ~Qgis_MapToolDrillerPLugin();

    virtual void unload(){
      std::cout << "Qgis_MapToolDrillerPLugin::unload" << std::endl;
    }

public slots:
    // virtual methods from QgisPlugin
    virtual void initGui();

    void run();

    void showOrHide();

    void help();

    //! Called when mouse clicks on the canvas. Will populate text box with coords.
    void mouseClicked( QgsPoint thePoint );

    //! Called when mouse moved over the canvas.
    void mouseMoved( QgsPoint thePoint );

    //! Called when QgisInterface.currentLayerChanged
    void currentLayerChanged( QgsMapLayer* currentLayer );

    void StartOverlay();

private:

    MapToolDriller* mpMapTool;

    QPointer<QDockWidget> mpDockWidget;

    QPointer<QLineEdit> mpFeedbackEdit;

    QPushButton * mpOnButton;

    QgisInterface* m_qgis_if;

    QAction* m_action;

    QgsVectorLayer* mpCurrentMapLayer;

    QgsVectorDataProvider* mpCurrentVectorProvider;

    QgsLegendInterface* mpLegendInterface;

};

#endif // #ifndef QGIS_MAPTOOLDRILLER_H
