#pragma once
#include <QGraphicsDropShadowEffect>
#include <QGraphicsLineItem>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QStyleOptionGraphicsItem>

class LineItem : public QGraphicsLineItem
{
public:
    LineItem(const QPointF& start_point, const QPointF& end_point);
    ~LineItem();
    void update(const QPointF& start_point, const QPointF& end_point);
    void update(const QPointF& start_point);
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    QPointF start_point_;
    QPointF end_point_;
    QGraphicsDropShadowEffect* shadow_;
    QColor shadow_color_;
};