#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <viewer.h>
#include "viewerzoom.h"
#include <QVector>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QStringList &imgPaths, QWidget *parent = nullptr);
    ~MainWindow();
    void readSettings();

private:
    void synchronizeViewers(void);
    void addWidgets(void);

    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    Viewer *viewer_lu;
    Viewer *viewer_ru;
    Viewer *viewer_lb;
    Viewer *viewer_rb;

    QVector<Viewer *> *viewerVector;

    ViewerZoom *viewerZoom;
};
#endif // MAINWINDOW_H
