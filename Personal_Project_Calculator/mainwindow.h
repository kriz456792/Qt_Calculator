#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSharedPointer>
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    double percentage {0.10};
    bool proceduralBtnPressed{false};
    QSharedPointer<QChar> proceduralChar{};
    QSharedPointer<double> first{};

public slots:
    void setText(QString str);
    QString getText();

    void numericalButtonClicked(QChar ch);
    void button0Clicked();
    void button1Clicked();
    void button2Clicked();
    void button3Clicked();
    void button4Clicked();
    void button5Clicked();
    void button6Clicked();
    void button7Clicked();
    void button8Clicked();
    void button9Clicked();

    void buttonClearClicked();
    void buttonSignClicked();
    void buttonPeriodClicked();
    void buttonPercentageClicked();

    void proceduralButtonClicked(QChar ch);
    void executeProcedure( double num2);

    void buttonDivisionClicked();
    void buttonMultiplyClicked();
    void buttonSubtractionClicked();
    void buttonAdditionClicked();

    void buttonEqualClicked();
    void action_set_percentage_clicked();
    void changePercentage(double num);

};
#endif // MAINWINDOW_H
