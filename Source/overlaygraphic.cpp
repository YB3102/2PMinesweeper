#include "overlaygraphic.h"

OverlayGraphic::OverlayGraphic(const int x, const int y, const int width, const int height, Tile * overlay_tile){
    this -> overlay_x_ = x;
    this -> overlay_y_ = y;
    this -> overlay_width_ = width;
    this -> overlay_height_ = height;
    this -> overlay_tile_ = overlay_tile;
}

QRectF OverlayGraphic::boundingRect() const
{
    return QRectF(overlay_x_, overlay_y_, overlay_width_, overlay_height_);
}

QPainterPath OverlayGraphic::shape() const
{
    QPainterPath path;
    path.addRect(overlay_x_, overlay_y_, overlay_width_, overlay_height_);
    return path;
}

void OverlayGraphic::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QBrush b = painter->brush();

    //draw original image

    painter->drawRect(QRect(overlay_x_, overlay_y_, overlay_width_, overlay_height_));
    //painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
    painter->setBrush(b);

}
