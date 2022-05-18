#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

signals:
    void sendPercentage(double num);

public slots:
    void percentage_5_pressed();
    void percentage_10_pressed();
    void percentage_25_pressed();
    void percentage_50_pressed();
    void percentage_90_pressed();
    void percentage_CA_tax_pressed();
    void submit_button_clicked();




private:
    Ui::Dialog *ui;


};

#endif // DIALOG_H
