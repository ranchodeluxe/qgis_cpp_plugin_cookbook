#include "maptooldriller.h"
#include "qgscursors.h"
#include "qgsmapcanvas.h"
#include "qgsmaptopixel.h"
#include "qgsrubberband.h"
#include "qgscoordinatereferencesystem.h"

#include <QSettings>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCursor>
#include <QPixmap>


MapToolDriller::MapToolDriller(QgsMapCanvas* canvas) : QgsMapTool(canvas)
{
  // set cursor
  QPixmap myCursor = QPixmap(( const char ** ) capture_point_cursor ); // const from qgscursors
  mCursor = QCursor( myCursor, 8, 8 ); //8,8 is the point in the cursor where clicks register
  /*
  ** TODO:
  ** there is no reason to hold a pointer
  ** to MapCanvas when when QgsMapTool has protected member
  ** and we are passed one in the constructor
  ** remoe it later to see if it still works
  */
  mpMapCanvas = canvas;
  mpRubberBand = new QgsRubberBand( mpMapCanvas, QGis::Polygon );
  mpRubberBand->setColor( Qt::red );
  mpRubberBand->setWidth( 1 );
}
    
MapToolDriller::~MapToolDriller()
{
  if ( mpRubberBand != 0 ) {
    delete mpRubberBand;
  }
}

void MapToolDriller::canvasMoveEvent(QMouseEvent * e)
{
  QgsPoint myOriginalPoint = mCanvas->getCoordinateTransform()->toMapCoordinates( e->x(), e->y() );
  emit mouseMoved( myOriginalPoint );
}
  
void MapToolDriller::canvasPressEvent(QMouseEvent * e)
{
  Q_UNUSED( e );
}

void MapToolDriller::canvasReleaseEvent(QMouseEvent * e)
{
  if ( !mpMapCanvas || mpMapCanvas->isDrawing() )
  {
    return;
  }

  QgsPoint myOriginalPoint =
    mCanvas->getCoordinateTransform()->toMapCoordinates( e->x(), e->y() );
  emit mouseClicked( myOriginalPoint );

  //make a little box for display

  QgsPoint myPoint1 =
    mCanvas->getCoordinateTransform()->toMapCoordinates( e->x() - 1, e->y() - 1 );
  QgsPoint myPoint2 =
    mCanvas->getCoordinateTransform()->toMapCoordinates( e->x() + 1, e->y() - 1 );
  QgsPoint myPoint3 =
    mCanvas->getCoordinateTransform()->toMapCoordinates( e->x() + 1, e->y() + 1 );
  QgsPoint myPoint4 =
    mCanvas->getCoordinateTransform()->toMapCoordinates( e->x() - 1, e->y() + 1 );

  mpRubberBand->reset( QGis::Polygon );
  // convert screen coordinates to map coordinates
  mpRubberBand->addPoint( myPoint1, false ); //true - update canvas
  mpRubberBand->addPoint( myPoint2, false ); //true - update canvas
  mpRubberBand->addPoint( myPoint3, false ); //true - update canvas
  mpRubberBand->addPoint( myPoint4, true ); //true - update canvas
  mpRubberBand->show();
}

void MapToolDriller::deactivate()
{
  mpRubberBand->reset( QGis::Line );
  QgsMapTool::deactivate();
}
