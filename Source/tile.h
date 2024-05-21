#ifndef TILE_H
#define TILE_H

#include <QWidget>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QRandomGenerator>

enum class TileType {normal, number,  bomb, powerup, defaulttile};


class Tile : public QObject, public QGraphicsPixmapItem{

    Q_OBJECT

public:
    Tile(const int num, const int x, const int y, const int width, const int height, TileType type = TileType::defaulttile);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    int get_x(){return x_;}
    int get_y(){return y_;}

    int get_width(){return width_;}
    int get_height(){return height_;}

    int get_num(){return num_;}

    TileType get_TileType(){return type_;}

    void set_x(int x){x_ = x;}
    void set_y(int y){y_ = y;}

    void set_width(int width){width_ = width;}
    void set_height(int height){height_ = height;}

    void set_num(int num){num_ = num;}

    void set_TileType(TileType type){type_ = type;}

    void set_tileimage(const QPixmap &image){
        tileImage_ = image;
        update();
    }

    std::vector <Tile *> get_adjacent_tiles(){return adjacent_tiles_;}

    void set_adjacent_tiles(std::vector <Tile *> adjacent_tiles){adjacent_tiles_ = adjacent_tiles;}

    void append_adjacent_tiles(Tile * adj){adjacent_tiles_.push_back(adj);}

    void clear_adjacent_tiles(){adjacent_tiles_.clear();}

    void pop_adjacent_tiles(){adjacent_tiles_.pop_back();}

    void set_flag(boolean value){flag = value;}
    boolean get_flag(){return flag;}

    void set_hidden(boolean value){hidden = value;}
    boolean get_hidden(){return hidden;}

    void set_mines(int mines){surrounding_mines_ = mines;}
    int get_mines(){return surrounding_mines_;}

    void set_board(int board){board_ = board;}
    int get_board(){return board_;}

signals:
    void ToggleFlag(Tile * t);
    void MineTile(Tile * t);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int num_;
    int x_;
    int y_;
    int width_ = 0;
    int height_ = 0;

    bool flag = false;
    bool hidden = true;

    int board_;

    TileType type_ = TileType::defaulttile;

    QPixmap tileImage_;

    QString flagImage= ":/MINESWEEPER_F.png";
    QString closedImage = ":/MINESWEEPER_X.png";


    //create a subclass for player marker
    //more or less the same attributes but separate from

    int surrounding_mines_;

    std::vector<Tile *> adjacent_tiles_;
};

#endif // TILE_H
