#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QVariant>
#include <QSlider>
#include <QMenuBar>
#include <QSpinBox>
#include <QWidget>
#include <QtDebug>
#include <QAction>
#include <QFrame>
#include <QLabel>
#include <QStack>
#include <QMenu>

#include "area.h"

namespace MagicWandTool {

/*****************************************************************************/

class MainWindow : public QMainWindow {
  Q_OBJECT
  private:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
  private:
    QStack<QImage> undo;
    QStack<QImage> redo;
  private:
    Area* area;
  private:
    int r = 0;
    int g = 0;
    int b = 0;
    int sensitivity = 0;
  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static int exec(int argc, char** argv);
  private:
    void setupUi(QMainWindow *MainWindow);
  private slots:
    void rChanged(int r);
    void gChanged(int g);
    void bChanged(int b);
    void sensitivityChanged(int sensitivity);
    void clickHandler(QPoint point);
  private slots:
    void openHandler();
};
#endif // MAINWINDOW_H

/*****************************************************************************/

} // namespace MagicWandTool
