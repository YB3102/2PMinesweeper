#include "tile.h"

Tile::Tile(const int num, const int x, const int y, const int width, const int height, TileType type){
    this -> num_ = num;
    this -> x_ = x;
    this -> y_ = y;
    this -> width_ = width;
    this -> height_ = height;
    this->type_ = type;
}

QRectF Tile::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Tile::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QBrush b = painter->brush();

    //draw original image
    if(!tileImage_.isNull() && (hidden == false)){
        painter->drawPixmap(x_, y_, width_, height_, tileImage_);
        painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
    }

    //simply flag and apply flag image
    else if (flag == true && hidden == true){
        QPixmap flag_map(flagImage);
        painter->drawPixmap(x_, y_, width_, height_, flag_map);
        painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
    }

    //simply unflag and remove flag image
    else if (hidden == true || (hidden == true && flag == false)){
        QPixmap hidden_map(closedImage);
        painter->drawPixmap(x_, y_, width_, height_, hidden_map);
        painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
    }
    else{
        painter->drawRect(QRect(this->x_, this->y_, this->width_, this->height_));
        painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
        painter->setBrush(b);
    }
}

/**
 * @brief Tile::mousePressEvent Event for program testing. Sends signals for mining for left click and flagging for right click.
 * @param event
 */
void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        emit MineTile(this);
    }

    else if (event->button() == Qt::RightButton){
        emit ToggleFlag(this);
    }
    qDebug() << "tile clicked!";

}
