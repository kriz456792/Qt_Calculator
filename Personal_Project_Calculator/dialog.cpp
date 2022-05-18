#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->pushButton_5_percent, SIGNAL(clicked()), this, SLOT(percentage_5_pressed()));
    connect(ui->pushButton_10_percent, SIGNAL(clicked()), this, SLOT(percentage_10_pressed()));
    connect(ui->pushButton_25_percent, SIGNAL(clicked()), this, SLOT(percentage_25_pressed()));
    connect(ui->pushButton_50_percent, SIGNAL(clicked()), this, SLOT(percentage_50_pressed()));
    connect(ui->pushButton_90_percent, SIGNAL(clicked()), this, SLOT(percentage_90_pressed()));
    connect(ui->pushButton_CA_Tax_percent, SIGNAL(clicked()), this, SLOT(percentage_CA_tax_pressed()));
    connect(ui->submit_percentage_button, SIGNAL(clicked()), this, SLOT(submit_button_clicked()));


}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::percentage_5_pressed()
{
    emit sendPercentage(0.05);
    close();
}

void Dialog::percentage_10_pressed()
{
    emit sendPercentage(0.10);
    close();
}

void Dialog::percentage_25_pressed()
{
    emit sendPercentage(0.25);
    close();
}

void Dialog::percentage_50_pressed()
{
    emit sendPercentage(0.50);
    close();
}

void Dialog::percentage_90_pressed()
{
    emit sendPercentage(0.90);
    close();
}

void Dialog::percentage_CA_tax_pressed()
{
    emit sendPercentage(0.0975);
    close();
}

void Dialog::submit_button_clicked()
{
    QString text = ui->lineEdit_percentage->text();
    bool isNum{false};
    double num = text.toDouble(&isNum);

    if(!isNum){
        QMessageBox::warning(this,"WARNING!","Input not of valid numerical value.");
        return;
    }
    else if( num < 0){
        QMessageBox::warning(this,"WARNING!","Negative input is not valid");
        return;
    }
    else{
        emit sendPercentage(num / 100);
        close();
    }
}



