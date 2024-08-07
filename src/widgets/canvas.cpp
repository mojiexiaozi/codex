#include "widgets/canvas.h"

Canvas::Canvas(QWidget* parent) : QGraphicsView(parent) {}
Canvas::~Canvas() {}

void Canvas::wheelEvent(QWheelEvent* e)
{
    setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform |
                   QPainter::LosslessImageRendering);
    // 背景缓存
    setCacheMode(QGraphicsView::CacheNone);
    // 隐藏滚动条
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // 框选模式
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::RubberBandDrag);
    // 拖拽模式
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setAcceptDrops(true);

    this->scene_ = new Scene();
    setScene(this->scene_);
}
void Canvas::mouseMoveEvent(QMouseEvent* e) {}
void Canvas::mousePressEvent(QMouseEvent* e) {}
void Canvas::mouseReleaseEvent(QMouseEvent* e) {}
void Canvas::mouseDoubleClickEvent(QMouseEvent* e) {}
void Canvas::dragMoveEvent(QDragMoveEvent* e) {}
void Canvas::dropEvent(QDropEvent* e) {}
void Canvas::keyReleaseEvent(QKeyEvent* e) {}