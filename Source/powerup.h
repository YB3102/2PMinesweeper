#ifndef POWERUP_H
#define POWERUP_H

#include "overlaygraphic.h"

enum class PowerupEnum {RevealBomb, HundredPoints, defaultup};

class PowerUp : public OverlayGraphic
{
    Q_OBJECT

public:

    PowerUp(const int x, const int y, const int width, const int height, Tile * powerup_tile, PowerupEnum power);

    void set_board(int board){player_board_ = board;}
    int get_board(){return player_board_;}

    void set_powerup(PowerupEnum power){power_ = power;}
    PowerupEnum get_powerup(){return power_;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

private:

    PowerupEnum power_;

    int player_board_ = 0;

    QString yes = ":/POWERUP_YES.png";
    QString coin = ":/POWERUP_POINTS.png";

    QPixmap powerup_image_;

protected:
           //void keyPressEvent(QKeyEvent * event) override;
};

#endif // POWERUP_H
