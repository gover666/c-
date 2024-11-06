#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QPainter>
#include "chooselevelscene.h"
#include <QTimer>
#include <QSound>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ChooseLevelScene * chooselevelscene=NULL;

    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
