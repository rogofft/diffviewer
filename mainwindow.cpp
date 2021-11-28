#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <QSettings>


MainWindow::MainWindow(const QStringList &imgPaths, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewerVector = new QVector<Viewer *>;
    for (const auto& imgPath : imgPaths) {
        viewerVector->push_back(new Viewer(imgPath, this));
    }

    addWidgets();
    synchronizeViewers();

    viewerZoom = new ViewerZoom(viewerVector, this);
    viewerZoom->set_modifiers(Qt::NoModifier);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::synchronizeViewers(void)
{
    for (auto iter = viewerVector->begin(); iter < viewerVector->end(); ++iter) {
        for (auto jter = viewerVector->begin(); jter < viewerVector->end(); ++jter) {
            if (iter != jter) {
                connect((*iter)->verticalScrollBar(), SIGNAL(valueChanged(int)),
                        (*jter)->verticalScrollBar(), SLOT(setValue(int)));
                connect((*iter)->verticalScrollBar(), SIGNAL(valueChanged(int)),
                        (*jter)->verticalScrollBar(), SLOT(setValue(int)));
                connect((*iter)->horizontalScrollBar(), SIGNAL(valueChanged(int)),
                        (*jter)->horizontalScrollBar(), SLOT(setValue(int)));
                connect((*iter)->horizontalScrollBar(), SIGNAL(valueChanged(int)),
                        (*jter)->horizontalScrollBar(), SLOT(setValue(int)));
            }
        }
    }
}

void MainWindow::addWidgets(void)
{
    int num = 0;
    for (auto& widget : *viewerVector) {
        ui->gridLayout->addWidget(widget, num/2, num%2);
        num++;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings("Repr", "DiffViewer");
    settings.beginGroup("MainWindow");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    if (!isMaximized()) {
        settings.setValue( "pos", pos() );
        settings.setValue( "size", size() );
    }
    settings.endGroup();
    QMainWindow::closeEvent(event);
}

void MainWindow::readSettings(void)
{
    QSettings settings("Repr", "DiffViewer");
    settings.beginGroup("MainWindow");
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    restoreState(settings.value("windowState", saveState()).toByteArray());
    move(settings.value( "pos", pos() ).toPoint());
    resize(settings.value( "size", size() ).toSize());
    if (settings.value("maximized", isMaximized()).toBool()) showMaximized();
    settings.endGroup();
}
