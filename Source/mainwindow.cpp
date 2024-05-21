#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <algorithm>

/**
 * @brief tile_factory This function produces and returns a tile based on the passed params
 * @param num
 * @param x
 * @param y
 * @param width
 * @param height
 * @param tile TileType enum
 * @return
 */
Tile * tile_factory(int num, int x, int y, int width, int height, TileType tile){

    Tile * return_tile = nullptr;
    QString path = "";
    switch(tile){

    case TileType::normal:
        return_tile = new Tile(num, x, y, width, height, tile);
        return_tile->set_TileType(TileType::normal);
        path = ":/MINESWEEPER_0.png";
        return_tile->set_tileimage(path);
        return return_tile;
        break;

    case TileType::number:
        return_tile = new Tile(num, x, y, width, height, tile);
        return_tile->set_TileType(TileType::number);
        path = ":/MINESWEEPER_0.png";
        return_tile->set_tileimage(path);
        return return_tile;
        break;

    case TileType::bomb:
        return_tile = new Tile(num, x, y, width, height, tile);
        return_tile->set_TileType(TileType::bomb);
        path = ":/MINESWEEPER_M.png";
        return_tile->set_tileimage(path);
        return return_tile;
        break;

    case TileType::powerup:
        return_tile = new Tile(num, x, y, width, height, tile);
        return_tile->set_TileType(TileType::powerup);
        path = ":/MINESWEEPER_C.png";
        return_tile->set_tileimage(path);
        return return_tile;
        break;

    case TileType::defaulttile:
        return_tile = new Tile(num, x, y, width, height, tile);
        return_tile->set_TileType(TileType::defaulttile);
        path = ":/MINESWEEPER_X.png";
        return_tile->set_tileimage(path);
        return return_tile;
        break;

    default:
        return nullptr;
        break;

    }
}

/**
 * @brief AlterTile Takes in a tile and changes its type and image based on the passed type
 * @param object
 * @param type
 * @param number
 */
void AlterTile(Tile * object, TileType type, int number = 0){

    QString path = "";
    switch(type){

    case TileType::normal:

        object->set_TileType(TileType::normal);
        path = ":/MINESWEEPER_0.png";
        object->set_tileimage(path);
        break;

    case TileType::number:

        switch(number){

        case 0:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_0.png";
            object->set_tileimage(path);
            break;

        case 1:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_1.png";
            object->set_tileimage(path);
            break;

        case 2:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_2.png";
            object->set_tileimage(path);
            break;

        case 3:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_3.png";
            object->set_tileimage(path);
            break;

        case 4:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_4.png";
            object->set_tileimage(path);
            break;

        case 5:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_5.png";
            object->set_tileimage(path);
            break;

        case 6:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_6.png";
            object->set_tileimage(path);
            break;

        case 7:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_7.png";
            object->set_tileimage(path);
            break;

        case 8:
            object->set_TileType(TileType::number);
            path = ":/MINESWEEPER_8.png";
            object->set_tileimage(path);
            break;

        default:
            return;
            break;
        }
        break;

    case TileType::bomb:

        object->set_TileType(TileType::bomb);
        path = ":/MINESWEEPER_M.png";
        object->set_tileimage(path);
        break;

    case TileType::powerup:

        object->set_TileType(TileType::powerup);
        path = ":/MINESWEEPER_C.png";
        object->set_tileimage(path);
        break;

    case TileType::defaulttile:

        object->set_TileType(TileType::defaulttile);
        path = ":/MINESWEEPER_X.png";
        object->set_tileimage(path);
        break;

    default:
        return;
        break;

    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene1 = new QGraphicsScene();

    view1 = ui->playerView;

    view1 ->setScene(scene1);

    scene2 = new QGraphicsScene();

    view2 = ui->playerView_2;

    view2 -> setScene(scene2);

    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &MainWindow::updateTimer1);
    turn_timer1 = 100;
    timer1->start(1000);

    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, this, &MainWindow::updateTimer2);
    turn_timer2 = 100;
    timer2->start(1000);

    timer1->stop();
    timer2->stop();

    intro = new IntroDialog;
    intro->setModal(true);
    intro->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::openMineHelper1 Recursive function for opening up safe tiles that are not numbered
 * @param base_tile
 */
void MainWindow::openMineHelper1(Tile * base_tile){

    if (base_tile -> get_hidden() == false || base_tile->get_TileType() == TileType::bomb || base_tile->get_mines()!=0){

        if(base_tile->get_TileType() == TileType::number){
            this->handlePoints(base_tile); //called to handle points on mining a tile
            //this->handlePowerups(base_tile);
            base_tile->set_hidden(false);
            base_tile->set_flag(false);
            this->handlePowerups(base_tile); //checks if tile had a powerup
            scene1->update();
            scene2->update();
        }
        return;
    }


    this->handlePoints(base_tile); //processing current tile
    base_tile->set_hidden(false);
    base_tile->set_flag(false);
    this->handlePowerups(base_tile);
    scene1->update();
    scene2->update();


    for (Tile * adj : base_tile->get_adjacent_tiles()){
        this->openMineHelper1(adj); //processing adjacent tiles
    }
}

/**
 * @brief MainWindow::MineSlot Protected slot called when a user clicks on a tile. Will be called different when markers are implemented.
 * @param t
 */
void MainWindow::MineSlot(Tile * t){

    //first click of p1. initializes stuff like the board, mines and powerups in random locations

    if(first1p_click == false && t->get_board() == 1){

        first1p_click = true;
        this->setAdjacentTiles1();
        this->setMines1(t);
        this->setNumbers1();
        this->setPowerups1();
        this->openMineHelper1(t);
    }

    //similar to p1 initialization but for p2
    else if(first2p_click == false && t->get_board() == 2){

        first2p_click = true;
        this->setAdjacentTiles2();
        this->setMines2(t);
        this->setNumbers2();
        this->setPowerups2();
        this->openMineHelper1(t);
    }

    //calls the helper recursively to open and mine tiles
    else {

        //numbered tile, so simply open
        if (t -> get_hidden() == true && (t->get_TileType() == TileType::number && t->get_mines() != 0) ){
            this->handlePoints(t);
            t->set_hidden(false);
            t->set_flag(false);
            this->handlePowerups(t);
            scene1->update();
            scene2->update();
        }

        //mine encountered. calls handler function
        else if (t -> get_hidden() == true && (t->get_TileType() == TileType::bomb) ){
            t->set_hidden(false);
            t->set_flag(false);
            scene1->update();
            scene2->update();

            this->mineClicked(t);

            //handle this better, does not work as expected

            //QApplication::exit();
        }

        //if not a numbered tile, then recursively open
        else if (t -> get_hidden() == true && (t->get_TileType() == TileType::number && t->get_mines() == 0)){
            this->openMineHelper1(t);
        }
    }
}

/**
 * @brief MainWindow::handlePowerups Checks the passed tile if it has a powerup and then calls a helper
 * @param t Tile being processed
 */
void MainWindow::handlePowerups(Tile * t){

    int board = t->get_board();

    if(board == 1){

        PowerUp * handle = this->getPowerUpbyTile1(t);

        if (handle != nullptr){
            this->handlePowerupsHelper(handle);
        }

        else{
            return;
        }
    }

    else if (board == 2){
        PowerUp * handle = this->getPowerUpbyTile2(t);

        if (handle != nullptr){
            this->handlePowerupsHelper(handle);
        }

        else{
            return;
        }
    }
}

/**
 * @brief MainWindow::handlePowerupsHelper Handles the type of powerup and updates player status accordingly
 * @param p
 */
void MainWindow::handlePowerupsHelper(PowerUp * p){

    if (p->get_board() == 1){

        bool it_flag = false;
        int bomb_size = this->board1_bombs.size();
        std :: string points_s;
        QString text;

        switch (p->get_powerup()){

        case PowerupEnum::HundredPoints:

            if(mark_flag1 == true){
                return;
            }
            this->game_player1_->set_points(this->game_player1_->get_points() + 100);

            points_s = std::to_string(this->game_player1_->get_points());

            text = QString("P1 Points: %1").arg(points_s.c_str());

            ui->timer_label1_2->setText(text);

            p->show();

            scene1->update();

            mark_flag1 = true;
            break;

        case PowerupEnum::RevealBomb:

            //reveal a random unopened bomb on board

            if(reveal_flag1 == true){
                return;
            }

            while(it_flag != true){
                int random = QRandomGenerator::global()->generate() % bomb_size;

                if (board1_bombs[random]->get_hidden() == true && board1_bombs[random]->get_flag() == false){
                    this->FlagSlot(board1_bombs[random]);

                    it_flag = true;

                }

            }

            p->show();

            reveal_flag1 = true;

            scene1->update();
            break;

        default:
            return;
            break;
        }
    }

    else if (p->get_board() == 2){

        bool it_flag = false;
        int bomb_size = this->board2_bombs.size();
        std :: string points_s;
        QString text;

        switch (p->get_powerup()){

        case PowerupEnum::HundredPoints:

            if (mark_flag2 == true){
                return;
            }
            this->game_player2_->set_points(this->game_player2_->get_points() + 100);
            points_s = std::to_string(this->game_player2_->get_points());

            text = QString("P2 Points: %1").arg(points_s.c_str());

            ui->timer_label2_2->setText(text);

            p->show();

            scene2->update();

            mark_flag2 = true;

            break;

        case PowerupEnum::RevealBomb:

            if(reveal_flag2 == true){
                return;
            }

            while(it_flag != true){
                int random = QRandomGenerator::global()->generate() % bomb_size;

                if (board2_bombs[random]->get_hidden() == true && board2_bombs[random]->get_flag() == false){
                    this->FlagSlot(board2_bombs[random]);

                    it_flag = true;

                }

            }

            p->show();
            scene2->update();
            reveal_flag2 = true;
            break;

        default:
            return;
            break;
        }
    }
}

/**
 * @brief MainWindow::mineClicked Handler for when user clicks a mine. Destroys that view's tiles and markers, the entire board essentially.
 * @param t
 */
void MainWindow::mineClicked(Tile * t){

    if (t->get_board() == 1){
        this->p1_over_ = true;

        for (std::vector<Tile *> row : this->board1_tiles_){
            for (Tile * ele : row){
                scene1->removeItem(ele);
                ele = nullptr;
                delete ele;
            }
        }

        for (std :: vector <PlayerMarker*> row : this->player1_marker){
            for (PlayerMarker * ele : row){
                scene1->removeItem(ele);
                ele = nullptr;
                delete ele;
            }
        }

        board1_tiles_.clear();
        player1_marker.clear();

        scene1->update();

        view1->setScene(nullptr);

        view1->update();

        this->timer1->stop();
    }

    if (t->get_board() == 2){
        this->p2_over_ = true;

        for (std::vector<Tile *> row : this->board2_tiles_){
            for (Tile * ele : row){
                scene2->removeItem(ele);
                ele = nullptr;
                delete ele;
            }
        }

        for (std :: vector <PlayerMarker*> row : this->player2_marker){
            for (PlayerMarker * ele : row){
                scene2->removeItem(ele);
                ele = nullptr;
                delete ele;
            }
        }

        board2_tiles_.clear();
        player2_marker.clear();

        scene2->update();

        view2->setScene(nullptr);

        view2->update();

        this->timer2->stop();
    }

    //both players clicked a mine
    if (p1_over_ == true && p2_over_ == true){
        this->handleGameOver();
    }
}

/**
 * @brief MainWindow::handlePoints Function to handle points when a user mines a tile.
 * @param t
 */
void MainWindow::handlePoints(Tile * t){

    if (t->get_board() == 1){

        if (t->get_hidden() == true){
            this->game_player1_->set_points(this->game_player1_->get_points() + 1);

            this->safe_mines1 = this->safe_mines1 - 1;

            qDebug() << "player1 safe mines" << this->safe_mines1;

            std :: string points_s = std::to_string(this->game_player1_->get_points());

            QString text = QString("P1 Points: %1").arg(points_s.c_str());

            ui->timer_label1_2->setText(text);

            if (this->safe_mines1 == 2){
                this->handleGameOver();
            }

            qDebug() << "safe mines" << this->safe_mines1;
        }
    }

    else if (t->get_board() == 2){

        if(t->get_hidden() == true){
            this->game_player2_->set_points(this->game_player2_->get_points() + 1);

            this->safe_mines2 = this->safe_mines2 - 1;

            std :: string points_s = std::to_string(this->game_player2_->get_points());

            QString text = QString("P2 Points: %1").arg(points_s.c_str());

            ui->timer_label2_2->setText(text);

            if (this->safe_mines2 == 2){
                this->handleGameOver();
            }

            qDebug() << "safe mines" << this->safe_mines2;
        }
    }
}

/**
 * @brief MainWindow::FlagSlot Function for flagging hidden tiles
 * @param t
 */
void MainWindow::FlagSlot(Tile * t){

    if (t ->get_flag() == false && t->get_hidden() == true){
        t->set_flag(true);
        t->update();
        scene1->update();
        scene2->update();
    }

    else if (t->get_flag() == true && t->get_hidden() == true){
        t->set_flag(false);
        t->update();
        scene1->update();
        scene2->update();
    }
}

/**
 * @brief MainWindow::getTilebyNum1 Returns a tile with the corresponding number.
 * @param num
 * @return
 */
Tile * MainWindow::getTilebyNum1(int num){

    for (std::vector<Tile*> row : this->board1_tiles_){

        for (Tile * element : row){

            if (element->get_num() == num){
                return element;
            }
        }
    }

    return nullptr;
}

/**
 * @brief MainWindow::getTilebyCoords1 Returns a tile with the corresponding coordinates.
 * @param x
 * @param y
 * @return
 */
Tile * MainWindow::getTilebyCoords1(int x, int y){

    for (std::vector<Tile*> row : this->board1_tiles_){

        for (Tile * element : row){

            if ((element->get_x() == x) && (element->get_y() == y)){
                return element;
            }
        }
    }

    return nullptr;
}

/**
 * @brief MainWindow::setPowerups1 Sets up 2 powerups each for board 1 randomly. Called on user 1's first mine.
 */
void MainWindow::setPowerups1(){
    bool coin_flag = 0;
    bool check_flag = 0;
    Tile * occupied = nullptr;

    while (coin_flag != 1){
        int random = QRandomGenerator::global()->generate() % 64;

        Tile * mine_tile = this->getTilebyNum1(random);

        if (mine_tile->get_TileType() == TileType::bomb){
            continue;
        }

        else{
            PowerUp * point_powerup = new PowerUp(mine_tile->get_x(), mine_tile->get_y(), mine_tile->get_width(), mine_tile->get_height(), mine_tile, PowerupEnum::HundredPoints);
            coin_flag = 1;
            point_powerup->set_board(1);
            this->board1_powerups.push_back(point_powerup);
            scene1->addItem(point_powerup);
            point_powerup->hide();
            occupied = mine_tile;
            scene1->update();
        }
    }

    while (check_flag != 1){
        int random = QRandomGenerator::global()->generate() % 64;

        Tile * mine_tile = this->getTilebyNum1(random);

        if (mine_tile->get_TileType() == TileType::bomb || mine_tile == occupied){
            continue;
        }

        else{
            PowerUp * flag_powerup = new PowerUp(mine_tile->get_x(), mine_tile->get_y(), mine_tile->get_width(), mine_tile->get_height(), mine_tile, PowerupEnum::RevealBomb);
            check_flag = 1;
            flag_powerup->set_board(1);
            this->board1_powerups.push_back(flag_powerup);
            scene1->addItem(flag_powerup);
            flag_powerup->hide();
            scene1->update();
        }
    }
}

/**
 * @brief MainWindow::setPowerups2 Sets up 2 powerups each for board 2 randomly. Called on user 2's first mine.
 */
void MainWindow::setPowerups2(){
    bool coin_flag = 0;
    bool check_flag = 0;
    Tile * occupied = nullptr;

    while (coin_flag != 1){
        int random = QRandomGenerator::global()->generate() % 64;

        Tile * mine_tile = this->getTilebyNum2(random);

        if (mine_tile->get_TileType() == TileType::bomb){
            continue;
        }

        else{
            PowerUp * point_powerup = new PowerUp(mine_tile->get_x(), mine_tile->get_y(), mine_tile->get_width(), mine_tile->get_height(), mine_tile, PowerupEnum::HundredPoints);
            coin_flag = 1;
            point_powerup->set_board(2);
            this->board2_powerups.push_back(point_powerup);
            scene2->addItem(point_powerup);
            point_powerup->hide();
            occupied = mine_tile;
        }
    }

    while (check_flag != 1){
        int random = QRandomGenerator::global()->generate() % 64;

        Tile * mine_tile = this->getTilebyNum2(random);

        if (mine_tile->get_TileType() == TileType::bomb || mine_tile == occupied){
            continue;
        }

        else{
            PowerUp * flag_powerup = new PowerUp(mine_tile->get_x(), mine_tile->get_y(), mine_tile->get_width(), mine_tile->get_height(), mine_tile, PowerupEnum::RevealBomb);
            check_flag = 1;
            flag_powerup->set_board(2);
            this->board2_powerups.push_back(flag_powerup);
            scene2->addItem(flag_powerup);
            flag_powerup->hide();
        }
    }
}

/**
 * @brief MainWindow::setMines1 Sets mines in a way that avoids param tile and its adjacent tiles
 * @param avoid
 */

void MainWindow::setMines1(Tile * avoid){

    int mine_loop = 0;

    std::vector<Tile *> track_mines;

    std::vector<Tile*>avoid_adj_tiles = avoid->get_adjacent_tiles();

    track_mines = avoid_adj_tiles;

    track_mines.push_back(avoid);

    while(mine_loop != 10){

        int random = QRandomGenerator::global()->generate() % 64;

        Tile * mine_tile = this->getTilebyNum1(random);

        auto it = std::find(track_mines.begin(), track_mines.end(), mine_tile);

        if (it != track_mines.end()){
            continue;
        }
        else{
            track_mines.push_back(mine_tile);
            AlterTile(mine_tile, TileType::bomb);
            board1_bombs.push_back(mine_tile);
            mine_loop = mine_loop + 1;
        }
    }
}

/**
 * @brief MainWindow::setAdjacentTilesHelper1 Helper for below function. Does all the work.
 * @param base_tile
 */
void MainWindow::setAdjacentTilesHelper1(Tile * base_tile){

    int width = view1->frameSize().width();
    int height = view1->frameSize().height();

    const int squareWidth = width / 8;
    const int squareHeight = height / 8;

    int base_x = base_tile->get_x();
    int base_y = base_tile->get_y();

    std::vector<int> dy = {squareHeight, -squareHeight, 0, 0, squareHeight, squareHeight, -squareHeight, -squareHeight};
    std::vector<int> dx = {0, 0, squareWidth, -squareWidth, squareWidth, -squareWidth, squareWidth, -squareWidth};

    for (int i = 0; i < (int)dy.size(); i++){

        Tile * adj = this->getTilebyCoords1(base_x + dx[i], base_y + dy[i]);

        if (adj != nullptr){
            base_tile->append_adjacent_tiles(adj);
        }
        else{
            continue;
        }
    }
}

/**
 * @brief MainWindow::setAdjacentTiles1 Populates the adjacent tiles vector for each tile object
 */
void MainWindow::setAdjacentTiles1(){

    for (std::vector<Tile*> row : this->board1_tiles_){

        for (Tile * element : row){

            this->setAdjacentTilesHelper1(element);

        }
    }

    //print check that tiles are set properly

    /*for (std::vector<Tile*> row : this->board1_tiles_){

        for (Tile * element : row){

            qDebug() << "Base tile:" << element->get_num();
            qDebug() << "Adjacent tiles for" << element->get_num();

            QString adjacentTilesString; // String to hold adjacent tiles

            for (Tile * adj : element->get_adjacent_tiles()){
                adjacentTilesString += QString::number(adj->get_num()) + " "; // Concatenate adjacent tile numbers with space
            }

            qDebug() << adjacentTilesString; // Print the concatenated string
        }
    }*/

}

/**
 * @brief MainWindow::setNumbersHelper1 Helper that sets the number and also alters the tile and its image corresponding to surrounding bombs.
 * @param base_tile
 */
void MainWindow::setNumbersHelper1(Tile * base_tile){

    std::vector<Tile*> adj_tiles = base_tile->get_adjacent_tiles();

    int bombs = 0;

    for (Tile * adj : adj_tiles){

        if(adj->get_TileType() == TileType::bomb){
            bombs = bombs + 1;
        }

    }

    AlterTile(base_tile, TileType::number, bombs);
    base_tile->set_mines(bombs);
}

/**
 * @brief MainWindow::setNumbers1 Sets surrounding mines for each tile
 */
void MainWindow::setNumbers1(){

    for (std::vector<Tile*> row : this->board1_tiles_){

        for (Tile * element : row){

            if (element->get_TileType() != TileType::bomb){
                this->setNumbersHelper1(element);
            }

        }
    }
}


/*The below functions do the same tasks as the above but for the second board.
 * Could have had probably implemented this a little better but was short on time.
 * */

Tile * MainWindow::getTilebyNum2(int num){

    for (std::vector<Tile*> row : this->board2_tiles_){

        for (Tile * element : row){

            if (element->get_num() == num){
                return element;
            }
        }
    }

    return nullptr;
}

Tile * MainWindow::getTilebyCoords2(int x, int y){

    for (std::vector<Tile*> row : this->board2_tiles_){

        for (Tile * element : row){

            if ((element->get_x() == x) && (element->get_y() == y)){
                return element;
            }
        }
    }

    return nullptr;
}

void MainWindow::setMines2(Tile * avoid){

    int mine_loop = 0;

    std::vector<Tile *> track_mines;

    std::vector<Tile*>avoid_adj_tiles = avoid->get_adjacent_tiles();

    track_mines = avoid_adj_tiles;

    track_mines.push_back(avoid);

    while(mine_loop != 10){

        int random = QRandomGenerator::global()->generate() % 64;

        Tile * mine_tile = this->getTilebyNum2(random);

        auto it = std::find(track_mines.begin(), track_mines.end(), mine_tile);

        if (it != track_mines.end()){
            continue;
        }
        else{
            track_mines.push_back(mine_tile);
            AlterTile(mine_tile, TileType::bomb);
            board2_bombs.push_back(mine_tile);
            mine_loop = mine_loop + 1;
        }
    }
}


void MainWindow::setAdjacentTilesHelper2(Tile * base_tile){

    int width = view2->frameSize().width();
    int height = view2->frameSize().height();

    const int squareWidth = width / 8;
    const int squareHeight = height / 8;

    int base_x = base_tile->get_x();
    int base_y = base_tile->get_y();

    std::vector<int> dy = {squareHeight, -squareHeight, 0, 0, squareHeight, squareHeight, -squareHeight, -squareHeight};
    std::vector<int> dx = {0, 0, squareWidth, -squareWidth, squareWidth, -squareWidth, squareWidth, -squareWidth};

    for (int i = 0; i < (int)dy.size(); i++){

        Tile * adj = this->getTilebyCoords2(base_x + dx[i], base_y + dy[i]);

        if (adj != nullptr){
            base_tile->append_adjacent_tiles(adj);
        }
        else{
            continue;
        }
    }
}

void MainWindow::setAdjacentTiles2(){

    for (std::vector<Tile*> row : this->board2_tiles_){

        for (Tile * element : row){

            this->setAdjacentTilesHelper2(element);

        }
    }

    //print check that tiles are set properly

    /*for (std::vector<Tile*> row : this->board1_tiles_){

        for (Tile * element : row){

            qDebug() << "Base tile:" << element->get_num();
            qDebug() << "Adjacent tiles for" << element->get_num();

            QString adjacentTilesString; // String to hold adjacent tiles

            for (Tile * adj : element->get_adjacent_tiles()){
                adjacentTilesString += QString::number(adj->get_num()) + " "; // Concatenate adjacent tile numbers with space
            }

            qDebug() << adjacentTilesString; // Print the concatenated string
        }
    }*/

}

void MainWindow::setNumbersHelper2(Tile * base_tile){

    std::vector<Tile*> adj_tiles = base_tile->get_adjacent_tiles();

    int bombs = 0;

    for (Tile * adj : adj_tiles){

        if(adj->get_TileType() == TileType::bomb){
            bombs = bombs + 1;
        }

    }

    AlterTile(base_tile, TileType::number, bombs);
    base_tile->set_mines(bombs);
}


void MainWindow::setNumbers2(){

    for (std::vector<Tile*> row : this->board2_tiles_){

        for (Tile * element : row){

            if (element->get_TileType() != TileType::bomb){
                this->setNumbersHelper2(element);
            }

        }
    }
}

/**
 * @brief MainWindow::getPowerUpbyTile1 Returns the corresponding powerup to a tile, if any.
 * @param find
 * @return
 */
PowerUp * MainWindow::getPowerUpbyTile1(Tile * find){
    for(PowerUp * ele : this->board1_powerups){
        if (ele->get_overlay_tile() == find){
            return ele;
        }
    }

    return nullptr;
}

PowerUp * MainWindow::getPowerUpbyTile2(Tile * find){
    for(PowerUp * ele : this->board2_powerups){
        if (ele->get_overlay_tile() == find){
            return ele;
        }
    }

    return nullptr;
}

/**
 * @brief MainWindow::getMarkerbyTile1 Returns the corresponding marker to a tile.
 * @param find
 * @return
 */
PlayerMarker * MainWindow::getMarkerbyTile1(Tile * find){

    for (std::vector<PlayerMarker *> row : this->player1_marker){

        for (PlayerMarker * ele : row){

            if (ele->get_overlay_tile() == find){
                return ele;
            }
        }
    }

    return nullptr;
}

PlayerMarker * MainWindow::getMarkerbyTile2(Tile * find){

    for (std::vector<PlayerMarker *> row : this->player2_marker){

        for (PlayerMarker * ele : row){

            if (ele->get_overlay_tile() == find){
                return ele;
            }
        }
    }

    return nullptr;
}

/**
 * @brief MainWindow::handleMarkerMovement1 Deals with showing and hiding markers dependent on key inputs. Provides the illusion of marker movement for p1.
 */
void MainWindow::handleMarkerMovement1(){

    qDebug() << "this function gets called";

    Tile * base_tile = game_player1_->get_tile();

    qDebug() << "Player 1 Tile value in markermovement" << base_tile->get_num() << base_tile->get_x() << base_tile->get_y();

    int width = view1->frameSize().width();
    int height = view1->frameSize().height();

    qDebug() << "Widthnd height values in marker movmeent" << width << height;

    const int squareWidth = width / 8;
    const int squareHeight = height / 8;

    int base_x = base_tile->get_x();
    int base_y = base_tile->get_y();

    qDebug() << "base x" << base_x;
    qDebug() << "Base y " << base_y;
    std::vector<int> dy = {squareHeight, -squareHeight, 0, 0, squareHeight, squareHeight, -squareHeight, -squareHeight};
    std::vector<int> dx = {0, 0, squareWidth, -squareWidth, squareWidth, -squareWidth, squareWidth, -squareWidth};

    int final_x;
    int final_y;

    qDebug() << "this function gets called 2";

    //compute final positions dependent on key input

    if (this->p1_movement == "W"){
        final_y = base_y - squareHeight;
        qDebug() << "value of final y in w" << final_y;
        final_x = base_x;
        qDebug() << "value of final x in w" << final_x;
    }

    else if (this -> p1_movement == "A"){
        final_y = base_y;
        qDebug() << "value of final y in a" << final_y;
        final_x = base_x - squareWidth;
        qDebug() << "value of final x in a" << final_x;
    }

    else if (this -> p1_movement == "S"){
        final_y = base_y + squareHeight;
        qDebug() << "value of final y in s" << final_y;
        final_x = base_x;
        qDebug() << "value of final x in s" << final_x;
    }

    else if (this -> p1_movement == "D"){
        final_y = base_y;
        final_x = base_x + squareWidth;
        qDebug() << "value of final y in d" << final_y;
        qDebug() << "value of final x in d" << final_x;
    }

    else{
        return;
    }

    p1_movement = "";

    //update which tile to be hid and which tile to be shown
    if ((0 <= final_y) && (final_y <= (height-squareHeight)) && (0 <= final_x) && (final_x <= (width-squareWidth))){

        PlayerMarker * og_marker = this->getMarkerbyTile1(game_player1_->get_tile());

        qDebug() << og_marker->get_x() << og_marker->get_y() << og_marker->get_height() << og_marker->get_width() << og_marker->get_overlay_tile()->get_num();

        og_marker->hide();

        Tile * next_tile = this->getTilebyCoords1(final_x, final_y);

        game_player1_ -> set_tile(next_tile);

        PlayerMarker * new_marker = this->getMarkerbyTile1(next_tile);

        qDebug() << new_marker->get_x() << new_marker->get_y() << new_marker->get_height() << new_marker->get_width() << new_marker->get_overlay_tile()->get_num();

        new_marker->show();

        scene1->update();

        qDebug() << "this is probably working.";

    }

    else{
        return;
    }

    return;
}

/**
 * @brief MainWindow::handleMarkerMovement2 Deals with showing and hiding markers dependent on key inputs. Provides the illusion of marker movement for p2.
 */
void MainWindow::handleMarkerMovement2(){

    qDebug() << "this function gets called";

    Tile * base_tile = game_player2_->get_tile();

    qDebug() << "Player 2 Tile value in markermovement" << base_tile->get_num() << base_tile->get_x() << base_tile->get_y();

    int width = view2->frameSize().width();
    int height = view2->frameSize().height();

    qDebug() << "Widthnd height values in marker movmeent" << width << height;

    const int squareWidth = width / 8;
    const int squareHeight = height / 8;

    int base_x = base_tile->get_x();
    int base_y = base_tile->get_y();

    qDebug() << "base x" << base_x;
    qDebug() << "Base y " << base_y;
    std::vector<int> dy = {squareHeight, -squareHeight, 0, 0, squareHeight, squareHeight, -squareHeight, -squareHeight};
    std::vector<int> dx = {0, 0, squareWidth, -squareWidth, squareWidth, -squareWidth, squareWidth, -squareWidth};

    int final_x;
    int final_y;

    qDebug() << "this function gets called 2";

    if (this->p2_movement == "8"){
        final_y = base_y - squareHeight;
        qDebug() << "value of final y in w" << final_y;
        final_x = base_x;
        qDebug() << "value of final x in w" << final_x;
    }

    else if (this -> p2_movement == "4"){
        final_y = base_y;
        qDebug() << "value of final y in a" << final_y;
        final_x = base_x - squareWidth;
        qDebug() << "value of final x in a" << final_x;
    }

    else if (this -> p2_movement == "5"){
        final_y = base_y + squareHeight;
        qDebug() << "value of final y in s" << final_y;
        final_x = base_x;
        qDebug() << "value of final x in s" << final_x;
    }

    else if (this -> p2_movement == "6"){
        final_y = base_y;
        final_x = base_x + squareWidth;
        qDebug() << "value of final y in d" << final_y;
        qDebug() << "value of final x in d" << final_x;
    }

    else{
        return;
    }

    p2_movement = "";

    if ((0 <= final_y) && (final_y <= (height-squareHeight)) && (0 <= final_x) && (final_x <= (width-squareWidth))){

        PlayerMarker * og_marker = this->getMarkerbyTile2(game_player2_->get_tile());

        qDebug() << og_marker->get_x() << og_marker->get_y() << og_marker->get_height() << og_marker->get_width() << og_marker->get_overlay_tile()->get_num();

        og_marker->hide();

        Tile * next_tile = this->getTilebyCoords2(final_x, final_y);

        game_player2_ -> set_tile(next_tile);

        PlayerMarker * new_marker = this->getMarkerbyTile2(next_tile);

        qDebug() << new_marker->get_x() << new_marker->get_y() << new_marker->get_height() << new_marker->get_width() << new_marker->get_overlay_tile()->get_num();

        new_marker->show();

        scene2->update();

        qDebug() << "this is probably working.";

    }

    else{
        return;
    }

    return;
}

/**
 * @brief MainWindow::keyPressEvent This slot controls key presses. Returns when graphic element vectors are empty.
 *                  Stores a corresponding letter string to the keypress in a class variable.
 * @param event
 */
void MainWindow::keyPressEvent(QKeyEvent * event){

    if (start_flag != 1){
        return;
    }

    switch (event->key()){

        case Qt::Key_W:

        if(board1_tiles_.empty() || player1_marker.empty()){return;}
            qDebug() << "w pressed";
            p1_movement = "W";
            this->handleMarkerMovement1();
            break;

        case Qt::Key_A:
            if(board1_tiles_.empty() || player1_marker.empty()){return;}
            qDebug() << "a pressed";
            p1_movement = "A";
            this->handleMarkerMovement1();
            break;

        case Qt::Key_S:
            if(board1_tiles_.empty() || player1_marker.empty()){return;}
            qDebug() << "s pressed";
            p1_movement = "S";
            this->handleMarkerMovement1();
            break;

        case Qt::Key_D:
            if(board1_tiles_.empty() || player1_marker.empty()){return;}
            qDebug() << "d pressed";
            p1_movement = "D";
            this->handleMarkerMovement1();
            break;

        case Qt::Key_8:
            if(board2_tiles_.empty() || player2_marker.empty()){return;}
            qDebug() << "8 pressed";
            p2_movement = "8";
            this->handleMarkerMovement2();
            break;

        case Qt::Key_4:
            if(board2_tiles_.empty() || player2_marker.empty()){return;}
            qDebug() << "4 pressed";
            p2_movement = "4";
            this->handleMarkerMovement2();
            break;

        case Qt::Key_5:
            if(board2_tiles_.empty() || player2_marker.empty()){return;}
            qDebug() << "5 pressed";
            p2_movement = "5";
            this->handleMarkerMovement2();
            break;

        case Qt::Key_6:
            if(board2_tiles_.empty() || player2_marker.empty()){return;}
            qDebug() << "6 pressed";
            p2_movement = "6";
            this->handleMarkerMovement2();
            break;

        case Qt::Key_C:
            if(board1_tiles_.empty() || player1_marker.empty()){return;}
            qDebug() << "c mine pressed";
            this->MineSlot(game_player1_->get_tile());
            break;

        case Qt::Key_F:
            if(board1_tiles_.empty() || player1_marker.empty()){return;}
            qDebug() << "f pressed for p1 flag";
            this->FlagSlot(game_player1_->get_tile());
            break;

        case Qt::Key_Plus:
            if(board2_tiles_.empty() || player2_marker.empty()){return;}
            qDebug() << "plus pressed for p2 flag";
            this->FlagSlot(game_player2_->get_tile());
            break;

        case Qt::Key_0:
            if(board2_tiles_.empty() || player2_marker.empty()){return;}
            qDebug() << "zero pressed";
            this->MineSlot(game_player2_->get_tile());
            break;

        default:
            break;
    }
}

/**
 * @brief MainWindow::handleGameOver Handles the game over state. P1 wins, P2 wins, both P1 and P2 fail to clear. Also calls function to reset the board.
 */
void MainWindow::handleGameOver(){

    go_dialog = new GameOverDialog;
    QString pass = "";

    if (this->safe_mines1 == 2){

        int points = game_player1_->get_points() + turn_timer1;
        std :: string points_s = std::to_string(points);
        QString pass = QString("Player1 wins! Points: %1").arg(points_s.c_str());
        go_dialog->createLabel(pass);

    }

    else if (this->safe_mines2 == 2){

        int points = game_player2_->get_points() + turn_timer2;
        std :: string points_s = std::to_string(points);
        QString pass = QString("Player2 wins! Points: %1").arg(points_s.c_str());
        go_dialog->createLabel(pass);

    }

    else if (this->p1_over_ == true && this->p2_over_ == true){

        if (game_player1_->get_points() > game_player2_->get_points()){

            int points = game_player1_->get_points();
            std :: string points_s = std::to_string(points);
            QString pass = QString("Player1 wins with more points! Points: %1").arg(points_s.c_str());
            go_dialog->createLabel(pass);

        }

        else if (game_player1_->get_points() < game_player2_->get_points()){
            int points = game_player2_->get_points();
            std :: string points_s = std::to_string(points);
            QString pass = QString("Player2 wins with more points! Points: %1").arg(points_s.c_str());
            go_dialog->createLabel(pass);
        }

        else{
            QString pass = QString("Both players have same points. Draw!");
            go_dialog->createLabel(pass);
        }
    }

    go_dialog->setModal(true);
    go_dialog->show();

    this->resetBoard();
}

/**
 * @brief MainWindow::resetBoard Resets the class. Deletes pointers and clears class vectors. Resets other class attributes.
 */
void MainWindow::resetBoard(){

    view1->setScene(scene1);
    view2->setScene(scene2);

    for (std :: vector <Tile *> row : board1_tiles_){
        for (Tile * ele : row){
            scene1->removeItem(ele);
            ele = nullptr;
            delete ele;
        }
    }

    for (std :: vector <Tile *> row : board2_tiles_){
        for (Tile * ele : row){
            scene2->removeItem(ele);
            ele = nullptr;
            delete ele;
        }
    }

    for (std :: vector <PlayerMarker*> row : player1_marker){
        for (PlayerMarker * ele : row){
            scene1->removeItem(ele);
            ele = nullptr;
            delete ele;
        }
    }

    for (PowerUp * ele : board1_powerups){
        scene1->removeItem(ele);
        ele = nullptr;
        delete ele;
    }

    for (PowerUp * ele : board2_powerups){
        scene2->removeItem(ele);
        ele = nullptr;
        delete ele;
    }

    for (Tile * ele : board1_bombs){
        scene1->removeItem(ele);
        ele = nullptr;
        delete ele;
    }

    for (Tile * ele : board2_bombs){
        scene2->removeItem(ele);
        ele = nullptr;
        delete ele;
    }

    for (std :: vector <PlayerMarker*> row : player2_marker){
        for (PlayerMarker * ele : row){
            scene2->removeItem(ele);
            ele = nullptr;
            delete ele;
        }
    }

    game_player1_ = nullptr;
    delete game_player1_;

    game_player2_ = nullptr;
    delete game_player2_;

    first1p_click = false;
    first2p_click = false;

    start_flag = 0;

    p2_over_ = false;
    p1_over_ = false;

    reveal_flag1 = false;
    mark_flag1 = false;

    reveal_flag2 = false;
    mark_flag2 = false;

    p1_movement = "";

    p2_movement = "";

    timer1->start();
    timer2->start();

    turn_timer1 = 100;
    turn_timer2 = 100;

    safe_mines1 = 64 - mines;
    safe_mines2 = 64 - mines;

    /*timer1 = nullptr;
    delete timer1;

    timer2 = nullptr;
    delete timer2;*/

    board1_tiles_.clear();
    board2_tiles_.clear();

    player1_marker.clear();
    player2_marker.clear();

    board1_bombs.clear();
    board2_bombs.clear();

    board2_powerups.clear();
    board1_powerups.clear();

    ui->timer_label1_2->setText("P1 Points: 0");

    ui->timer_label2_2->setText("P2 Points: 0");

}

/**
 * @brief MainWindow::on_startButton_clicked This slot sets up the game and board on clicking start button. Also calls resertBoard at the start.
 */
void MainWindow::on_startButton_clicked(){

    this->resetBoard();

    //ui->startButton->setDisabled(true);

    QRect rcontent = view1->contentsRect();
    view1->setSceneRect(0,0,rcontent.width(), rcontent.height());

    QRect rcontent2 = view2->contentsRect();
    view2->setSceneRect(0,0,rcontent2.width(), rcontent2.height());

    int width = view1->frameSize().width();
    int height = view1->frameSize().height();

    view1->setFrameStyle(0);

    view2->setFrameStyle(0);

    int total_count = 64;
    int starting = 0;

    const int squareWidth = width / 8;
    const int squareHeight = height / 8;

    for (int y = 0; y < 8; y++) {
        std::vector<Tile*> currRow;
        std::vector<PlayerMarker*> currMarkerRow;

        for(int x = 0; x < 8; x++){
            Tile * newTile = tile_factory(starting, x*squareWidth, y * squareHeight, squareWidth, squareHeight, TileType::defaulttile);

            qDebug() << "Tile" << newTile->get_num() << newTile->get_height() << newTile->get_width() << newTile->get_x() << newTile->get_y();

            PlayerMarker * curr_marker = new PlayerMarker(newTile->get_x(), newTile->get_y(), newTile->get_width(), newTile->get_height(), newTile);

            connect(newTile, &Tile::ToggleFlag, this, &MainWindow::FlagSlot);
            connect(newTile, &Tile::MineTile, this, &MainWindow::MineSlot);

            newTile->set_board(1);
            curr_marker->set_board(1);

            starting = starting + 1;

            currRow.push_back(newTile);
            currMarkerRow.push_back(curr_marker);

        }

        board1_tiles_.push_back(currRow);
        this->player1_marker.push_back(currMarkerRow);

    }

    for (std::vector<Tile *> curr_row : board1_tiles_) {
        for (Tile* curr : curr_row) {
            scene1->addItem(curr);
        }
    }

    for (std::vector<PlayerMarker *> curr_row : player1_marker) {
        for (PlayerMarker* curr : curr_row) {
            scene1->addItem(curr);
            curr->hide();
            qDebug() << "Marker Player 1" << curr->get_overlay_tile()->get_num()<< curr->get_x() << curr->get_y() << curr->get_width() << curr->get_height();
        }
    }

    scene1->update();

    int starting2 = 0;

    for (int y = 0; y < 8; y++) {
        std::vector<Tile*> currRow;

        std::vector<PlayerMarker*> currMarkerRow;

        for(int x = 0; x < 8; x++){
            Tile * newTile = tile_factory(starting2, x*squareWidth, y * squareHeight, squareWidth, squareHeight, TileType::defaulttile);

            PlayerMarker * curr_marker = new PlayerMarker(newTile->get_x(), newTile->get_y(), newTile->get_width(), newTile->get_height(), newTile);

            newTile->set_board(2);
            curr_marker->set_board(2);

            connect(newTile, &Tile::ToggleFlag, this, &MainWindow::FlagSlot);
            connect(newTile, &Tile::MineTile, this, &MainWindow::MineSlot);

            starting2 = starting2 + 1;

            currRow.push_back(newTile);
            currMarkerRow.push_back(curr_marker);
        }

        board2_tiles_.push_back(currRow);
        player2_marker.push_back(currMarkerRow);
    }

    for (std::vector<Tile *> curr_row : board2_tiles_) {
        for (Tile* curr : curr_row) {
            scene2->addItem(curr);
        }
    }

    for (std::vector<PlayerMarker *> curr_row : player2_marker) {
        for (PlayerMarker* curr : curr_row) {
            scene2->addItem(curr);
            curr->hide();
        }
    }

    scene2->update();

    //initializing players
    this->game_player1_ = new Player(board1_tiles_[0][0]);
    //game_player1_->set_tile(board1_tiles_[0][0]);
    game_player1_->set_player_number_(1);

    this->game_player2_ = new Player(board2_tiles_[0][0]);
    //game_player2_->set_tile(board2_tiles_[0][0]);
    game_player2_->set_player_number_(2);


    player1_marker[0][0]->show();
    player2_marker[0][0]->show();

    //Tile * first_tile = game_player1_->get_tile();

    //qDebug() << "Values of x and y for first tile" << first_tile->get_x() << first_tile->get_y();

    //this->setMines();

    //this->setAdjacentTiles();

    //this->setNumbers();

    /*Tile * one = this->board1_tiles_[0][0];

    PlayerMarker * first_player = new PlayerMarker(one->get_x(), one->get_y(), one->get_width(), one->get_height(), one);
    first_player->set_board(1);

    scene1->addItem(first_player);

    scene1->update();*/

    //flag to indicate that game has started

    start_flag = 1;

}

void MainWindow::updateTimer1(){
    turn_timer1 = turn_timer1 - 1;

    if (turn_timer1 == 0){
        //this->nextTurn();

        //function for game over

        timer1->stop();
    }

    std :: string disp = std::to_string(turn_timer1);

    QString qs(disp.c_str());

    ui->timer_label1->setText("Time bonus left: " + qs + "s");

}

void MainWindow::updateTimer2(){
    turn_timer2 = turn_timer2 - 1;

    if (turn_timer2 == 0){
        timer2->stop();
    }

    std :: string disp = std::to_string(turn_timer2);

    QString qs(disp.c_str());

    ui->timer_label2->setText("Time bonus left: " + qs + "s");

}


