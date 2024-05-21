#include "playermarker.h"

PlayerMarker::PlayerMarker(const int x, const int y, const int width, const int height, Tile * marker_tile)
    : OverlayGraphic(x, y, width, height, marker_tile){}

/**
 * @brief PlayerMarker::paint Overridden playermarker method from overlaygraphic
 * @param painter
 * @param option
 * @param widget
 */
void PlayerMarker::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    QBrush b = painter->brush();

    if (this->player_board_ == 1){
        this->marker_image_ = QPixmap(red);
    }

    else if (this->player_board_ == 2){
        this->marker_image_ = QPixmap(green);
    }

    //draw original image

    if(!marker_image_.isNull()){
        painter->drawPixmap(this->get_x(), this->get_y(), this->get_width(), this->get_height(), marker_image_);
        //painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
    }

    else{
        painter->drawRect(QRect(this->get_x(), this->get_y(), this->get_width(), this->get_height()));
        //painter->drawText(this->x_+2, this->y_+10, QString(QString::fromStdString(std::to_string(this->num_))));
        painter->setBrush(b);
    }

}
