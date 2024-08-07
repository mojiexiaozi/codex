#pragma once

#include <QGraphicsView>

#include "widgets/scene.h"

class Canvas : public QGraphicsView
{
public:
    Canvas(QWidget* parent = nullptr);
    ~Canvas();

    void wheelEvent(QWheelEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void mouseDoubleClickEvent(QMouseEvent* e) override;
    void dragMoveEvent(QDragMoveEvent* e) override;
    void dropEvent(QDropEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e) override;

private:
    Scene* scene_;
};
