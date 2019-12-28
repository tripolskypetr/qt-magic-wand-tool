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
    QWidget* scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setGeometry(QRect(0, 0, 187, 165));
    QVBoxLayout* verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    QSpacerItem* verticalSpacer = new QSpacerItem(20, 52,
        QSizePolicy::Minimum,
        QSizePolicy::Expanding
    );
    verticalLayout->addItem(verticalSpacer);
    QFrame* frame = new QFrame(scrollAreaWidgetContents);
    frame->setFrameShape(QFrame::NoFrame);
    frame->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(frame);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    QSpacerItem* horizontalSpacer = new QSpacerItem(52, 20,
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );
    horizontalLayout->addItem(horizontalSpacer);
    label = new Label(frame);
    horizontalLayout->addWidget(label);
    QSpacerItem* horizontalSpacer_2 = new QSpacerItem(52, 20,
        QSizePolicy::Expanding,
        QSizePolicy::Minimum
    );
    horizontalLayout->addItem(horizontalSpacer_2);
    verticalLayout->addWidget(frame);
    QSpacerItem* verticalSpacer_2 = new QSpacerItem(20, 52,
        QSizePolicy::Minimum,
        QSizePolicy::Expanding
    );
    verticalLayout->addItem(verticalSpacer_2);
    scrollArea->setWidget(scrollAreaWidgetContents);
    label->setText("Please open file to continue");
    connect(label, &Label::click, [this](QPoint point) {
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
    label->setPixmap(QPixmap::fromImage(image));
    opened = true;
}

/*---------------------------------------------------------------------------*/

const QImage Area::getImage() {
    return image;
}

/*****************************************************************************/

}
