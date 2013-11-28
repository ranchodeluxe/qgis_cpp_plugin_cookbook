#ifndef MAPTOOLDRILLER_H
#define MAPTOOLDRILLER_H

#include "qgsmaptool.h"
#include "qgspoint.h"
#include "qgsmessagelog.h"

#include <QObject>
#include <QPointer>

/*
**  forward declarations instead of include
**  to cut down compile time since we only
**  want one class from the header
*/
class QgsRubberBand;

class MapToolDriller : public QgsMapTool
{
  Q_OBJECT;

  public:
    MapToolDriller(QgsMapCanvas* canvas);

    ~MapToolDriller();

    //! Overridden mouse move event
    virtual void canvasMoveEvent(QMouseEvent * e);

    //! Overridden mouse press event
    virtual void canvasPressEvent(QMouseEvent * e);

    //! Overridden mouse release event
    virtual void canvasReleaseEvent(QMouseEvent * e);

    //! called when map tool is being deactivated
    virtual void deactivate();

    void canvasClickHandler(const QgsPoint&);

    typedef QHash<QString,double> DrillResult;

  public slots:

  signals:
    void mouseMoved( QgsPoint );

    void mouseClicked( QgsPoint );

  private:
    //! Rubber band for dropping visual of click on map
    QgsRubberBand * mpRubberBand;

    QPointer<QgsMapCanvas> mpMapCanvas;

  private slots:

};
#endif
