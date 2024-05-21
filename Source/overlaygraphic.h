#ifndef OVERLAYGRAPHIC_H
#define OVERLAYGRAPHIC_H

#include <QWidget>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QRandomGenerator>

#include <QObject>

class Tile; //forward declaration

class OverlayGraphic : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    OverlayGraphic(const int x, const int y, const int width, const int height, Tile * overlay_tile);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    int get_x(){return overlay_x_;}
    int get_y(){return overlay_y_;}

    int get_width(){return overlay_width_;}
    int get_height(){return overlay_height_;}

    Tile * get_overlay_tile(){return overlay_tile_;}

    void set_x(int overlay_x){overlay_x_ = overlay_x;}
    void set_y(int overlay_y){overlay_y_ = overlay_y;}

    void set_width(int overlay_width){overlay_width_ = overlay_width;}
    void set_height(int overlay_height){overlay_height_ = overlay_height;}

    void set_overlay_tile(Tile * overlay_tile){overlay_tile_ = overlay_tile;}


signals:

private:
    int overlay_x_;
    int overlay_y_;
    int overlay_width_;
    int overlay_height_;

    Tile * overlay_tile_;
};

#endif // OVERLAYGRAPHIC_H
