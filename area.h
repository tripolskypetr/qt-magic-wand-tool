#ifndef AREA_H
#define AREA_H

#include <QObject>
#include <QtDebug>
#include <QPoint>
#include <QLabel>

namespace MagicWandTool {

/*****************************************************************************/

class Area : public QLabel {
  Q_OBJECT
  public:
    explicit Area(QWidget* parent = nullptr);
    virtual ~Area();
  signals:
    void click(QPoint point);
};

/*****************************************************************************/

}

#endif // AREA_H
