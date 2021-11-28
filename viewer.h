#ifndef VIEWER_H
#define VIEWER_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

namespace Ui {
class Viewer;
}

class Viewer : public QGraphicsView
{
    Q_OBJECT

public:
    explicit Viewer(const QString& filename, QWidget *parent = nullptr);
    ~Viewer();

private:

private slots:
    void resizeEvent(QResizeEvent *event) override;

    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    Ui::Viewer *ui;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *pixmapItem;

    bool _pan{false};
    int _panStartX, _panStartY;
};

#endif // VIEWER_H
