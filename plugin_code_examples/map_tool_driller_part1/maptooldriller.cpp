/***************************************************************************
    qgsmaptooldriller.h  -  This tool will drill through a bunch of rasters
                            and produce a table of values at a given point
                            in each layer
    ---------------------
    begin                : November 2006
    copyright            : (C) 2006 by Tim Sutton
    email                : tim at linfiniti.com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
/* $Id$ */

#include "qgsmaptoolemitpoint.h"
#include "maptooldriller.h"
#include "qgsmapcanvas.h"
#include "qgsrasterlayer.h"
#include "qgsmaptopixel.h"
#include "qgsmessagelog.h"
#include "qgscursors.h"
#include <QSettings>
#include <QMessageBox>
#include <QCursor>
#include <QPixmap>
#include <QHash>
#include <QMouseEvent>

MapToolDriller::MapToolDriller(QgsMapCanvas* canvas) : QgsMapTool(canvas)
{
  // set cursor
  QPixmap myIdentifyQPixmap = QPixmap((const char **) identify_cursor);
  mCursor = QCursor(myIdentifyQPixmap, 1, 1);

}
    
MapToolDriller::~MapToolDriller()
{

}

void MapToolDriller::canvasMoveEvent(QMouseEvent * e)
{

}
  
void MapToolDriller::canvasPressEvent(QMouseEvent * e)
{

}

void MapToolDriller::canvasReleaseEvent(QMouseEvent * e)
{
    QString mTag = "MapToolDriller";
    QString mFeedback = "inside canvasReleaseEvent";
    QgsMessageLog::instance()->logMessage( thePoint.toString(), mTag, QgsMessageLog::INFO );

    QgsPoint myPoint = mCanvas->getCoordinateTransform()->toMapCoordinates(e->x(), e->y());
    QHash <QString,double> myHash;
    myHash = drill(myPoint);

    QString xy = "Emitting...";
    QgsMessageLog::instance()->logMessage( xy, mTag, QgsMessageLog::INFO );

    emit drilled(myHash);
}

QHash<QString,double> MapToolDriller::drill(const QgsPoint &thePoint)
{
  QHash<QString,double> myHash;

  QgsMapLayer* layer = mCanvas->currentLayer();

  // call identify method for selected layer

  if (layer)
  {
      // convert screen coordinates to map coordinates
      if (layer->type() == QgsMapLayer::VectorLayer)
      {
        /*
        std::map<QString, QString> myAttributes;
        QgsVectorLayer* vectorLayer = dynamic_cast<QgsVectorLayer*>(layer);
        vectorLayer->identify(thePoint, myAttributes);
        */
        QString mFeedback = "Handling Vector Layer";
        QString mTag = "MapToolDriller";
        QgsMessageLog::instance()->logMessage( mFeedback, mTag, QgsMessageLog::INFO );
      }
      else if (layer->type() == QgsMapLayer::RasterLayer)
      {
        if (dynamic_cast<QgsRasterLayer*>(layer)->providerType() == "wms")
        {
            QString mFeedback = "This tool cannot handle WMS layers";
            QString mTag = "MapToolDriller";
            QgsMessageLog::instance()->logMessage( mFeedback, mTag, QgsMessageLog::INFO );
        }
        else
        {
          QString mFeedback = "This tool cannot handle QgsRaster layers";
          QString mTag = "MapToolDriller";
          QgsMessageLog::instance()->logMessage( mFeedback, mTag, QgsMessageLog::INFO );
          /*
          std::map<QString, QString> myAttributes;
          QgsRasterDataProvider* rasterProvider = dynamic_cast<QgsRasterLayer*>(layer)->dataProvider();
          rasterProvider->identify(thePoint, myAttributes);
          */
        }
      }
      else
      {
#ifdef QGISDEBUG
        std::cout << "MapToolDriller::canvasReleaseEvent: unknown layer type!" << std::endl;
#endif
        
        QString mFeedback = "Unknown layer type to handled";
        QString mTag = "MapToolDriller";
        QgsMessageLog::instance()->logMessage( mFeedback, mTag, QgsMessageLog::INFO );

      }
  }
  return myHash;
}

