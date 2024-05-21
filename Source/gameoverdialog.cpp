#include "gameoverdialog.h"
#include "qlabel.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameOverDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Game Over");
}

GameOverDialog::~GameOverDialog()
{
    delete ui;
}

void GameOverDialog::on_pushButton_clicked()
{
    this->close();
}

void GameOverDialog :: createLabel(QString text){

    ui->label->setText(text);
    ui->label->setWordWrap(true);
    ui->label->setParent(this);
    //desc->setGeometry(1, 1, this->width(), this->height());
}

