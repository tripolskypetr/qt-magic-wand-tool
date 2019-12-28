#ifndef AREA_H
#define AREA_H

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QScrollArea>
#include <QObject>
#include <QtDebug>
#include <QPoint>
#include <QImage>
#include <QLabel>

namespace MagicWandTool {

/*****************************************************************************/

class Label: public QLabel {
  Q_OBJECT
  public:
    explicit Label(QWidget* parent = nullptr);
    virtual ~Label();
  protected:
    virtual void mousePressEvent(QMouseEvent *e);
  signals:
    void click(QPoint point);
};

/*****************************************************************************/

class Area: public QScrollArea {
  Q_OBJECT
  private:
    QImage image;
    Label* label;
    bool opened = false;
  public:
    explicit Area(QWidget* parent = nullptr);
    virtual ~Area();
  private:
    void setupUi(QScrollArea *area);
  public slots:
    void setImage(QImage image);
  signals:
    void click(QPoint point);
};

/*****************************************************************************/

}

#endif // AREA_H
