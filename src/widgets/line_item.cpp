#include "widgets/line_item.h"

LineItem::LineItem(const QPointF& start_point, const QPointF& end_point)
{
    setZValue(-1);
    setFlags(GraphicsItemFlag::ItemIsSelectable);
    setAcceptHoverEvents(true);

    this->shadow_ = new QGraphicsDropShadowEffect();
    this->shadow_color_ = Qt::yellow;
    this->shadow_->setOffset(0, 0);
    this->shadow_->setBlurRadius(20);
}
LineItem::~LineItem()
{
    if (this->shadow_ != nullptr)
    {
        delete this->shadow_;
        this->shadow_ = nullptr;
    }
}
void LineItem::update(const QPointF& start_point, const QPointF& end_point) {}
void LineItem::update(const QPointF& start_point) {}
void LineItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
}
