#ifndef PLAYERMARKER_H
#define PLAYERMARKER_H

#include "overlaygraphic.h"

class PlayerMarker : public OverlayGraphic
{
    Q_OBJECT

public:

    PlayerMarker(const int x, const int y, const int width, const int height, Tile * marker_tile);

    void set_board(int board){player_board_ = board;}
    int get_board(){return player_board_;}

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

private:

    int player_board_ = 0;

    QString red = ":/MINESWEEPER_1P.png";
    QString green = ":/MINESWEEPER_2P.png";

    QPixmap marker_image_;

protected:
    //void keyPressEvent(QKeyEvent * event) override;
};

#endif // PLAYERMARKER_H
