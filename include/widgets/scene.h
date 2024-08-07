#pragma once

#include <QGraphicsView>

class Scene : public QGraphicsScene
{
public:
    Scene(QWidget* parent = nullptr);
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    int scene_width_{5000};
    int scene_height_{5000};
    int scene_grid_size_{20};
    int scene_grid_chunk_{10};
    QPen norm_pen_;
    QPen dark_pen_;
};