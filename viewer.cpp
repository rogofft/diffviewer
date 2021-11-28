#include "viewer.h"
#include "ui_viewer.h"
#include <QPixmap>
#include <QScrollBar>


Viewer::Viewer(const QString& filename, QWidget *parent) :
    QGraphicsView(parent),
    ui(new Ui::Viewer)
{
    ui->setupUi(this);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->setMinimumWidth(200);
    this->setMinimumHeight(200);

    scene = new QGraphicsScene(this);
    this->setScene(scene);

    pixmapItem = new QGraphicsPixmapItem(QPixmap(filename));
    scene->addItem(pixmapItem);

}

Viewer::~Viewer()
{
    delete ui;
}

void Viewer::resizeEvent(QResizeEvent *event)
{
    //timer->start(50);
    QGraphicsView::resizeEvent(event);
}

void Viewer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        _pan = true;
        _panStartX = event->x();
        _panStartY = event->y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void Viewer::mouseMoveEvent(QMouseEvent *event)
{
    if (_pan)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - _panStartY));
        _panStartX = event->x();
        _panStartY = event->y();
        event->accept();
        return;
    }
    event->ignore();
}

void Viewer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        _pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}























