#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QKeyEvent>

#include "player.h"
#include "tile.h"
#include "playermarker.h"
#include "powerup.h"
#include "introdialog.h"
#include "gameoverdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setMines1(Tile * avoid);

    Tile* getTilebyNum1(int num);

    Tile* getTilebyCoords1(int x, int y);

    void setAdjacentTilesHelper1(Tile * base_tile);

    void setAdjacentTiles1();

    void setNumbersHelper1(Tile * base_tile);

    void setNumbers1();

    void openMineHelper1(Tile * base_tile);

    void setMines2(Tile * avoid);

    void setPowerups1();

    void setPowerups2();

    void handlePowerups(Tile * t);

    void handlePowerupsHelper(PowerUp * p);

    Tile* getTilebyNum2(int num);

    Tile* getTilebyCoords2(int x, int y);

    PlayerMarker * getMarkerbyTile1(Tile * current_tile);

    PlayerMarker * getMarkerbyTile2(Tile * current_tile);

    PowerUp * getPowerUpbyTile1(Tile * current_tile);

    PowerUp * getPowerUpbyTile2(Tile * current_tile);

    void setAdjacentTilesHelper2(Tile * base_tile);

    void setAdjacentTiles2();

    void setNumbersHelper2(Tile * base_tile);

    void setNumbers2();

    void openMineHelper2(Tile * base_tile);

    void updateTimer1();

    void updateTimer2();

    void handleMarkerMovement1();

    void handleMarkerMovement2();

    void handleGameOver();

    void handlePoints(Tile * t);

    void mineClicked(Tile * t);

    void resetBoard();

protected:
    void keyPressEvent(QKeyEvent * event);


private slots:
    void FlagSlot(Tile * t);
    void MineSlot(Tile * t);

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;

    QGraphicsScene * scene1;
    QGraphicsView * view1;

    QGraphicsScene * scene2;
    QGraphicsView * view2;

    std :: vector <std :: vector <Tile *>> board1_tiles_;
    std :: vector <std :: vector <Tile *>> board2_tiles_;

    std :: vector <std :: vector <PlayerMarker *>> player1_marker;
    std :: vector <std :: vector <PlayerMarker *>> player2_marker;

    std::vector<PowerUp*> board1_powerups;
    std::vector<PowerUp*> board2_powerups;

    std::vector<Tile*> board1_bombs;
    std::vector<Tile*> board2_bombs;

    Player * game_player1_;
    Player * game_player2_;

    bool reveal_flag1 = false;
    bool mark_flag1 = false;

    bool reveal_flag2 = false;
    bool mark_flag2 = false;

    int mines = 8;

    bool first1p_click = false;
    bool first2p_click = false;

    QTimer * timer1;
    int turn_timer1;

    QTimer * timer2;
    int turn_timer2;

    QString p1_movement = "";

    QString p2_movement = "";

    bool start_flag = 0;

    int safe_mines1 = 64 - mines;
    int safe_mines2 = 64 - mines;

    bool p2_over_ = false;
    bool p1_over_ = false;

    IntroDialog * intro;

    GameOverDialog * go_dialog;
};


#endif // MAINWINDOW_H
