#include "introdialog.h"
#include "ui_introdialog.h"

IntroDialog::IntroDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IntroDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Description");
}

IntroDialog::~IntroDialog()
{
    delete ui;
}

void IntroDialog::on_pushButton_clicked()
{
    this->close();
}

