#include "area.h"

namespace MagicWandTool {

/*****************************************************************************/

Label::Label(QWidget *parent)
  : QLabel(parent) {
    qDebug() << "Label ctor";
}

/*---------------------------------------------------------------------------*/

Label::~Label() {
    qDebug() << "Label dtor";
}

/*---------------------------------------------------------------------------*/

void Label::mousePressEvent(QMouseEvent *e) {
    qDebug() << "Label mousePressEvent" << e->x() << e->y();
    emit click(e->pos());
}

/*****************************************************************************/

Area::Area(QWidget *parent)
  : QScrollArea(parent) {
    qDebug() << "Area ctor";
    setupUi(this);
}

/*---------------------------------------------------------------------------*/

Area::~Area() {
    qDebug() << "Area dtor";
}

/*---------------------------------------------------------------------------*/

void Area::setupUi(QScrollArea* scrollArea) {
    scrollArea->setFrameShape(QFrame::Box);
    scrollArea->setWidgetResizable(true);
    scrollArea->setAlignment(Qt::AlignCenter);
    QWidget* areaWidgetContents = new QWidget();
    areaWidgetContents->setGeometry(QRect(0, 0, 337, 287));
    QVBoxLayout* verticalLayout = new QVBoxLayout(areaWidgetContents);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    label = new Label(areaWidgetContents);
    label->setAlignment(Qt::AlignCenter);
    verticalLayout->addWidget(label);
    scrollArea->setWidget(areaWidgetContents);
    label->setText("Please open file to continue");
    connect(label, &Label::click, [this](QPoint point){
       if (opened) {
           emit click(point);
       }
    });
}

/*---------------------------------------------------------------------------*/

void Area::setImage(QImage image) {
    qDebug() << "Area setImage";
    this->image = image;
    label->setMaximumSize(image.size());
    label->setMinimumSize(image.size());
    opened = true;
}

/*****************************************************************************/

}
