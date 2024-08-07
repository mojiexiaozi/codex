#include "widgets/scene.h"

Scene::Scene(QWidget* parent) : QGraphicsScene(parent)
{
    this->setBackgroundBrush(QBrush(QColor("#212121")));
    this->setSceneRect(-this->scene_width_ / 2, -this->scene_height_ / 2, this->scene_width_, -this->scene_height_);
    this->norm_pen_ = QPen(QColor("#313131"));
    this->norm_pen_.setWidthF(1.0);

    this->dark_pen_ = QPen(QColor("#151515"));
    this->dark_pen_.setWidthF(1.5);

    this->setItemIndexMethod(QGraphicsScene::NoIndex);
}
void Scene::drawBackground(QPainter* painter, const QRectF& rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    int left = rect.left();
    int right = rect.right();
    int top = rect.top();
    int bottom = rect.bottom();

    int left_start = left - (left % this->scene_grid_size_);
    int top_start = top - (top % this->scene_grid_size_);

    QList<QLine> lines;
    QList<QLine> dark_lines;
    auto step = this->scene_grid_size_ * this->scene_grid_size_;

    for (int v = top_start; v <= bottom; v += this->scene_grid_size_)
    {
        auto line = QLine(left, v, right, v);
        if (v % step == 0)
        {
            dark_lines.append(line);
        }
        else
        {
            lines.append(line);
        }
    }

    for (int h = left_start; h <= right; h += this->scene_grid_size_)
    {
        auto line = QLine(h, top, h, bottom);
        if (h % step == 0)
        {
            dark_lines.append(line);
        }
        else
        {
            lines.append(line);
        }
    }

    painter->setPen(this->norm_pen_);
    painter->drawLines(lines);

    painter->setPen(this->dark_pen_);
    painter->drawLines(dark_lines);
}
