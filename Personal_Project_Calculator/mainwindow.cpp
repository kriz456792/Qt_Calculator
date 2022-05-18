#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setText("0");
    /*Numerical button connections below*/
    connect(ui->pushButton_00, SIGNAL(clicked()), this, SLOT(button0Clicked()));
    connect(ui->pushButton_01, SIGNAL(clicked()), this, SLOT(button1Clicked()));
    connect(ui->pushButton_02, SIGNAL(clicked()), this, SLOT(button2Clicked()));
    connect(ui->pushButton_03, SIGNAL(clicked()), this, SLOT(button3Clicked()));
    connect(ui->pushButton_04, SIGNAL(clicked()), this, SLOT(button4Clicked()));
    connect(ui->pushButton_05, SIGNAL(clicked()), this, SLOT(button5Clicked()));
    connect(ui->pushButton_06, SIGNAL(clicked()), this, SLOT(button6Clicked()));
    connect(ui->pushButton_07, SIGNAL(clicked()), this, SLOT(button7Clicked()));
    connect(ui->pushButton_08, SIGNAL(clicked()), this, SLOT(button8Clicked()));
    connect(ui->pushButton_09, SIGNAL(clicked()), this, SLOT(button9Clicked()));

    /*Procedural button connections below*/
    connect(ui->pushButton_division, SIGNAL(clicked()), this, SLOT(buttonDivisionClicked()));
    connect(ui->pushButton_multiplication, SIGNAL(clicked()), this, SLOT(buttonMultiplyClicked()));
    connect(ui->pushButton_subtraction, SIGNAL(clicked()), this, SLOT(buttonSubtractionClicked()));
    connect(ui->pushButton_addition, SIGNAL(clicked()), this, SLOT(buttonAdditionClicked()));

    /*Other button connections below*/
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(buttonClearClicked()));
    connect(ui->pushButton_sign_change, SIGNAL(clicked()), this, SLOT(buttonSignClicked()));
    connect(ui->pushButton_period, SIGNAL(clicked()), this, SLOT(buttonPeriodClicked()));
    connect(ui->pushButton_percentage, SIGNAL(clicked()), this, SLOT(buttonPercentageClicked()));

    connect(ui->pushButton_equal, SIGNAL(clicked()), this, SLOT(buttonEqualClicked()));

    connect(ui->actionSet_Percentage, SIGNAL(triggered()), this, SLOT(action_set_percentage_clicked()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText(QString str) //Method sets the text on the LineEdit.
{
    ui->lineEdit->setText(str);
}

QString MainWindow::getText() //Method gets the text on from LineEdit.
{
    return ui->lineEdit->text();
}

void MainWindow::numericalButtonClicked(QChar ch){//Used by all number button slots.

    if(proceduralBtnPressed){
        setText("");
        proceduralBtnPressed = false;
        qInfo() << "numericalButtonClicked(QChar ch) proceduralBtnPressed true -> false.";
    }

    QString text = getText();
    if(text == "0") {
        setText(QString(ch));
        return;
    }

    if(text == "-0") {
        setText(QString("-") + QString(ch));
        return;
    }

    text.append(ch);
    setText(text);
}
/*All the button slots call on the numericalButtonClicked() method & pass the related number character.*/
void MainWindow::button0Clicked(){ numericalButtonClicked('0'); }
void MainWindow::button1Clicked(){ numericalButtonClicked('1'); }
void MainWindow::button2Clicked(){ numericalButtonClicked('2'); }
void MainWindow::button3Clicked(){ numericalButtonClicked('3'); }
void MainWindow::button4Clicked(){ numericalButtonClicked('4'); }
void MainWindow::button5Clicked(){ numericalButtonClicked('5'); }
void MainWindow::button6Clicked(){ numericalButtonClicked('6'); }
void MainWindow::button7Clicked(){ numericalButtonClicked('7'); }
void MainWindow::button8Clicked(){ numericalButtonClicked('8'); }
void MainWindow::button9Clicked(){ numericalButtonClicked('9'); }

void MainWindow::buttonClearClicked() {
    setText("0");
    proceduralBtnPressed = false;

    proceduralChar = nullptr;
    first = nullptr;

    qInfo() << "buttonClearClicked() proceduralBtnPressed = false / proceduralChar = nullptr / first = nullptr";
}

void MainWindow::buttonSignClicked()
{
    if(proceduralBtnPressed) {
        return;
    }

    QString text = getText();
    if(text.at(0) != '-') { //If is not negative.
        text = QString("-") + text;
        setText(text);
        return;
    }

    if(text.at(0) == '-') { //If is negative.
        text.remove('-');
        setText(text);
        return;
    }
}

void MainWindow::buttonPeriodClicked()
{
    if(proceduralBtnPressed) {
        return;
    }

    QString text = getText();
    if(!text.contains('.')) {
        text.append('.');
        setText(text);
    }
}

void MainWindow::buttonPercentageClicked()
{
    if(first != nullptr || proceduralBtnPressed) {
        return;
    }

    QString text = getText();
    bool isNum = false;
    double num = text.toDouble(&isNum);

    if(isNum) {
        num = num * percentage;
        setText(QString::number(num));
    }
    return;
}

void MainWindow::proceduralButtonClicked(QChar ch)
{

    if(proceduralBtnPressed) {
        /*If "/ * - +" has been pressed, we will simply replace it.*/
        QSharedPointer<QChar> tempCh(new QChar(ch));
        proceduralChar = tempCh;
        return;
    }

    QString text = getText();
    bool isNum {false};
    double num = text.toDouble(&isNum);

    if(!isNum) {
        qInfo() << "proceduralButtonClicked(QChar ch) : isNum = false";
    }

    if(first == nullptr) {
        QSharedPointer<double> temp(new double(num));
        QSharedPointer<QChar> tempCh(new QChar(ch));
        first = temp;
        proceduralChar = tempCh;
        proceduralBtnPressed = true;
        return;
    }

    executeProcedure(num);
    text = getText();
    isNum = false;
    num = text.toDouble(&isNum);
    if(isNum) {
        QSharedPointer<double> temp(new double(num));
        QSharedPointer<QChar> tempCh(new QChar(ch));
        first = temp;
        proceduralChar = tempCh;
        proceduralBtnPressed = true;
    }

}

void MainWindow::executeProcedure(double num2)
{
    double result{};
    if(*proceduralChar == '/') {
        result = *first / num2;
    }
    if(*proceduralChar == '*') {
        result = *first * num2;
    }
    if(*proceduralChar == '-') {
        result = *first - num2;
    }
    if(*proceduralChar == '+') {
        result = *first + num2;
    }

    setText(QString::number(result));
    QSharedPointer<double> temp(new double(result));
    first = temp;
}

/*All procedural buttons call on the */
void MainWindow::buttonDivisionClicked(){ proceduralButtonClicked('/'); }
void MainWindow::buttonMultiplyClicked(){ proceduralButtonClicked('*'); }
void MainWindow::buttonSubtractionClicked(){ proceduralButtonClicked('-'); }
void MainWindow::buttonAdditionClicked(){ proceduralButtonClicked('+'); }

void MainWindow::buttonEqualClicked()
{
    if(first == nullptr || proceduralChar == nullptr) {
        return;
    }

    QString text = getText();
    bool isNum{false};
    double num = text.toDouble(&isNum);

    if(isNum) {
       executeProcedure(num);
       proceduralBtnPressed = true;
       qInfo() << "buttonEqualClicked() proceduralBtnPressed -> true / ";
    }
}

void MainWindow::action_set_percentage_clicked()
{
    Dialog dialog(this);

    connect(&dialog,SIGNAL(sendPercentage(double)), this, SLOT(changePercentage(double)));
    dialog.setWindowTitle("Set Percentage Menu");
    dialog.exec();
}

void MainWindow::changePercentage(double num)
{
    qInfo() << num;
    percentage = num;
    ui->pushButton_percentage->setText(QString::number(num * 100) + '%');
}






