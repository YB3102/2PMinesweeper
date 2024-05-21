#ifndef PLAYER_H
#define PLAYER_H

class Tile;

class Player{
public:
    Player(Tile * current_tile);

    int get_points(){return points_;}

    void set_points(int points){points_ = points;}

    int get_mined(){return tiles_mined_;}

    void set_mined(int tiles_mined){tiles_mined_ = tiles_mined;}

    Tile * get_tile(){return current_tile_;}

    void set_tile(Tile * curr_tile){current_tile_ = curr_tile;}

    void set_player_number_(int player_number){player_number_ = player_number;}

    int get_player_number_(){return player_number_;}

    int player_number_ = 0;

private:

    int tiles_mined_ = 0;

    int points_ = 0;

    Tile * current_tile_;
};

#endif // PLAYER_H
