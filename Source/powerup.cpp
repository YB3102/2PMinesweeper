#include "powerup.h"

PowerUp::PowerUp(const int x, const int y, const int width, const int height, Tile * marker_tile, PowerupEnum power)
    : OverlayGraphic(x, y, width, height, marker_tile){
    this->power_ = power;
}

/**
 * @brief PowerUp::paint Overridden PowerUp method from overlaygraphic
 * @param painter
 * @param option
 * @param widget
 */
void PowerUp::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    qreal opacity = 0.5; // Change this to the desired opacity value (0.0 = fully transparent, 1.0 = fully opaque)
    painter->setOpacity(opacity);

    QBrush b = painter->brush();

    if (this->power_ == PowerupEnum::HundredPoints){
        this->powerup_image_ = QPixmap(coin);
    }

    else if (this->power_ == PowerupEnum::RevealBomb){
        this->powerup_image_ = QPixmap(yes);
    }

    //draw original image

    if(!powerup_image_.isNull()){
        painter->drawPixmap(this->get_x(), this->get_y(), this->get_width(), this->get_height(), powerup_image_);
        //painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
    }

    else{
        painter->drawRect(QRect(this->get_x(), this->get_y(), this->get_width(), this->get_height()));
        //painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
        painter->setBrush(b);
    }

}
