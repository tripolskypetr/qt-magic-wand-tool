#include "mainwindow.h"

namespace MagicWandTool {

/*****************************************************************************/

Worker::Worker(QImage image) {
    qDebug() << "Worker ctor";
    this->image = image;
}

/*---------------------------------------------------------------------------*/

Worker::~Worker() {
    qDebug() << "Worker dtor";
}

/*---------------------------------------------------------------------------*/

QImage Worker::click(QColor fillColor, QPoint point, int sensitivity) {
    this->templColor = QColor(image.pixel(point.x(), point.y()));
    this->sensitivity = sensitivity;
    this->fillColor = fillColor;
    fill(point);
    return image;
}

/*---------------------------------------------------------------------------*/

bool Worker::inRange(QPoint point) {
    int x = point.x();
    int y = point.y();
    if (x < 0 || x >= image.width()) {
      return false;
    } else if (y < 0 || y >= image.height()) {
      return false;
    } else {
      return true;
    }
}

/*---------------------------------------------------------------------------*/

bool Worker::compare(QColor a, QColor b) {
    int da = a.red() + a.green() + a.blue();
    int db = b.red() + b.green() + b.blue();
    return qAbs(da - db) <= sensitivity;
}

/*---------------------------------------------------------------------------*/

QList<QPoint> Worker::border(QPoint point) {
    QList<QPoint> dots;
    int x = point.x();
    int y = point.y();
    if (inRange(QPoint(x-1,y-1))) {
        dots.append(QPoint(x-1,y-1));
    }
    if (inRange(QPoint(x-1,y))) {
        dots.append(QPoint(x-1,y));
    }
    if (inRange(QPoint(x-1,y+1))) {
        dots.append(QPoint(x-1,y+1));
    }
    if (inRange(QPoint(x,y+1))) {
        dots.append(QPoint(x,y+1));
    }
    if (inRange(QPoint(x,y-1))) {
        dots.append(QPoint(x,y-1));
    }
    if (inRange(QPoint(x+1,y))) {
        dots.append(QPoint(x+1,y));
    }
    if (inRange(QPoint(x+1,y+1))) {
        dots.append(QPoint(x+1,y+1));
    }
    if (inRange(QPoint(x+1,y-1))) {
        dots.append(QPoint(x+1,y-1));
    }
    return dots;
}

/*---------------------------------------------------------------------------*/

void Worker::fill(QPoint point) {
    QColor pointColor = QColor(image.pixel(point));
    if (ignore.contains(point)) {
        return;
    } else if (compare(templColor, pointColor)) {
        ignore.insert(point);
        qDebug() << point.x() << point.y();
        image.setPixelColor(point.x(), point.y(), fillColor);
        QList<QPoint> bounding = border(point);
        QList<QPoint>::iterator iter;
        for (iter = bounding.begin(); iter != bounding.end(); iter++) {
            fill(*iter);
        }
    } else {
        return;
    }
}

/*****************************************************************************/

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) {
    qDebug() << "MainWindow ctor";
    actionOpen = new QAction(this);
    actionSave = new QAction(this);
    actionExit = new QAction(this);
    actionUndo = new QAction(this);
    actionRedo = new QAction(this);
    setupUi(this);
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);
    actionSave->setEnabled(false);
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(openHandler()));
}

/*---------------------------------------------------------------------------*/

MainWindow::~MainWindow() {
    qDebug() << "MainWindow dtor";
}

/*---------------------------------------------------------------------------*/

int MainWindow::exec(int argc, char **argv) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

/*---------------------------------------------------------------------------*/

void MagicWandTool::MainWindow::setupUi(QMainWindow *MainWindow) {
    MainWindow->resize(490, 315);
    QWidget* centralwidget = new QWidget(MainWindow);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(centralwidget);
    QFrame* frame = new QFrame(centralwidget);
    frame->setMinimumSize(QSize(181, 0));
    frame->setMaximumSize(QSize(181, 16777215));
    frame->setFrameShape(QFrame::NoFrame);
    frame->setFrameShadow(QFrame::Raised);
    QVBoxLayout* verticalLayout_4 = new QVBoxLayout(frame);
    verticalLayout_4->setContentsMargins(0, 0, 0, 0);
    QGroupBox* groupBox = new QGroupBox(frame);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
    groupBox->setSizePolicy(sizePolicy);
    QVBoxLayout* verticalLayout = new QVBoxLayout(groupBox);
    verticalLayout->setContentsMargins(5, 5, 5, 5);
    QFrame* frame_3 = new QFrame(groupBox);
    frame_3->setFrameShape(QFrame::NoFrame);
    frame_3->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout_2 = new QHBoxLayout(frame_3);
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    QLabel* label = new QLabel(frame_3);
    horizontalLayout_2->addWidget(label);
    QSpinBox* spinBox = new QSpinBox(frame_3);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
    spinBox->setSizePolicy(sizePolicy1);
    spinBox->setMaximum(255);
    horizontalLayout_2->addWidget(spinBox);
    verticalLayout->addWidget(frame_3);
    QFrame* frame_4 = new QFrame(groupBox);
    frame_4->setFrameShape(QFrame::NoFrame);
    frame_4->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout_3 = new QHBoxLayout(frame_4);
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    QLabel* label_2 = new QLabel(frame_4);
    horizontalLayout_3->addWidget(label_2);
    QSpinBox* spinBox_2 = new QSpinBox(frame_4);
    sizePolicy1.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
    spinBox_2->setSizePolicy(sizePolicy1);
    spinBox_2->setMaximum(255);
    horizontalLayout_3->addWidget(spinBox_2);
    verticalLayout->addWidget(frame_4);
    QFrame* frame_5 = new QFrame(groupBox);
    frame_5->setFrameShape(QFrame::NoFrame);
    frame_5->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout_4 = new QHBoxLayout(frame_5);
    horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
    QLabel* label_3 = new QLabel(frame_5);
    horizontalLayout_4->addWidget(label_3);
    QSpinBox* spinBox_3 = new QSpinBox(frame_5);
    sizePolicy1.setHeightForWidth(spinBox_3->sizePolicy().hasHeightForWidth());
    spinBox_3->setSizePolicy(sizePolicy1);
    spinBox_3->setMaximum(255);
    horizontalLayout_4->addWidget(spinBox_3);
    verticalLayout->addWidget(frame_5);
    verticalLayout_4->addWidget(groupBox);
    QGroupBox* groupBox_3 = new QGroupBox(frame);
    QVBoxLayout* verticalLayout_3 = new QVBoxLayout(groupBox_3);
    verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    QFrame* frame_7 = new QFrame(groupBox_3);
    frame_7->setObjectName(QString::fromUtf8("frame_7"));
    frame_7->setFrameShape(QFrame::NoFrame);
    frame_7->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout_6 = new QHBoxLayout(frame_7);
    horizontalLayout_6->setContentsMargins(5, 5, 5, 5);
    QSlider* horizontalSlider = new QSlider(frame_7);
    horizontalSlider->setOrientation(Qt::Horizontal);
    horizontalLayout_6->addWidget(horizontalSlider);
    QLabel* label_4 = new QLabel(frame_7);
    label_4->setMinimumSize(QSize(23, 0));
    label_4->setAlignment(Qt::AlignCenter);
    horizontalLayout_6->addWidget(label_4);
    verticalLayout_3->addWidget(frame_7);
    verticalLayout_4->addWidget(groupBox_3);
    QGroupBox* groupBox_2 = new QGroupBox(frame);
    QVBoxLayout* verticalLayout_2 = new QVBoxLayout(groupBox_2);
    verticalLayout_2->setContentsMargins(5, 5, 5, 5);
    QFrame* frame_6 = new QFrame(groupBox_2);
    frame_6->setFrameShape(QFrame::NoFrame);
    frame_6->setFrameShadow(QFrame::Raised);
    QHBoxLayout* horizontalLayout_5 = new QHBoxLayout(frame_6);
    horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
    QPushButton* pushButton = new QPushButton(frame_6);
    horizontalLayout_5->addWidget(pushButton);
    QPushButton* pushButton_2 = new QPushButton(frame_6);
    horizontalLayout_5->addWidget(pushButton_2);
    verticalLayout_2->addWidget(frame_6);
    verticalLayout_4->addWidget(groupBox_2);
    QSpacerItem* verticalSpacer_2 = new QSpacerItem(20, 282,
        QSizePolicy::Minimum,
        QSizePolicy::Expanding
    );
    verticalLayout_4->addItem(verticalSpacer_2);
    horizontalLayout->addWidget(frame);
    QFrame* frame_2 = new QFrame(centralwidget);
    frame_2->setFrameShape(QFrame::NoFrame);
    frame_2->setFrameShadow(QFrame::Raised);
    QVBoxLayout* verticalLayout_5 = new QVBoxLayout(frame_2);
    verticalLayout_5->setContentsMargins(0, 0, 0, 0);
    area = new Area(frame_2);
    verticalLayout_5->addWidget(area);
    horizontalLayout->addWidget(frame_2);
    MainWindow->setCentralWidget(centralwidget);
    QMenuBar* menubar = new QMenuBar(MainWindow);
    menubar->setGeometry(QRect(0, 0, 688, 22));
    QMenu* menuFile = new QMenu(menubar);
    QMenu* menuEdit = new QMenu(menubar);
    MainWindow->setMenuBar(menubar);
    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuEdit->menuAction());
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);
    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    actionOpen->setText("Open");
    actionSave->setText("Save as");
    actionExit->setText("Exit");
    actionUndo->setText("Undo");
    actionRedo->setText("Redo");
    groupBox->setTitle("Color");
    label->setText("R:");
    label_2->setText("G:");
    label_3->setText("B:");
    groupBox_3->setTitle("Sensitivity");
    label_4->setText("0");
    groupBox_2->setTitle("Actions");
    pushButton->setText("Undo");
    pushButton_2->setText("Redo");
    menuFile->setTitle("File");
    menuEdit->setTitle("Edit");
    connect(pushButton, &QPushButton::clicked, actionUndo, &QAction::trigger);
    connect(pushButton_2, &QPushButton::clicked, actionRedo, &QAction::trigger);
    connect(spinBox, SIGNAL(valueChanged(int)), this, SLOT(rChanged(int)));
    connect(spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(gChanged(int)));
    connect(spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(bChanged(int)));
    connect(area, SIGNAL(click(QPoint)), this, SLOT(clickHandler(QPoint)));
    connect(horizontalSlider, &QSlider::valueChanged, [label_4](int v) {
       label_4->setText(QVariant(v).toString());
    });
    connect(actionUndo, &QAction::changed, [pushButton]() {
       pushButton->setEnabled(!pushButton->isEnabled());
    });
    connect(actionRedo, &QAction::changed, [pushButton_2]() {
       pushButton_2->setEnabled(!pushButton_2->isEnabled());
    });
    connect(
        horizontalSlider,
        SIGNAL(valueChanged(int)),
        this,
        SLOT(sensitivityChanged(int))
    );
}

/*---------------------------------------------------------------------------*/

void MainWindow::rChanged(int r) {
    qDebug() << "rChanged" << r;
    this->r = r;
}

/*---------------------------------------------------------------------------*/

void MainWindow::gChanged(int g) {
    qDebug() << "gChanged" << g;
    this->g = g;
}

/*---------------------------------------------------------------------------*/

void MainWindow::bChanged(int b) {
    qDebug() << "bChanged" << b;
    this->b = b;
}

/*---------------------------------------------------------------------------*/

void MainWindow::sensitivityChanged(int sensitivity) {
    qDebug() << "sensitivityChanged" << sensitivity;
    this->sensitivity = sensitivity;
}

/*---------------------------------------------------------------------------*/

void MainWindow::clickHandler(QPoint point) {
    qDebug() << "MainWindow clickHandler";
    undo.push(area->getImage());
    redo.clear();
    actionUndo->setEnabled(true);
    actionRedo->setEnabled(false);
    Worker worker(area->getImage());
    area->setImage(worker.click(
        QColor(r, g, b),
        point,
        sensitivity
    ));
}

/*---------------------------------------------------------------------------*/

void MainWindow::openHandler() {
    qDebug() << "MainWindow openHandler";
    QString path = QFileDialog::getOpenFileName(this, "", "", "*.png *.jpg");
    QFile file(path);
    QImage image;
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox msg;
        msg.setText("It looks like image inaccessible");
        msg.exec();
    } else if (image.loadFromData(file.readAll())) {
        actionUndo->setEnabled(false);
        actionRedo->setEnabled(false);
        area->setImage(image);
        undo.clear();
        redo.clear();
        qDebug() << "image loaded";
    } else {
        QMessageBox msg;
        msg.setText("It looks like image unavalible");
        msg.exec();
    }
}

/*****************************************************************************/

} // namespace MagicWandTool
