#include "mainwindow.h"
#include "ui_mainwindow.h"

// #include <QDebug>

// variable for first operand
double first_number;
bool is_entering_second_number = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connecting buttons in ui file with slots

    // digits
    connect(ui->zero_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->one_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->two_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->three_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->four_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->five_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->six_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->seven_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->eight_button, SIGNAL(released()),this,SLOT(digit_pressed()));
    connect(ui->nine_button, SIGNAL(released()),this,SLOT(digit_pressed()));

    // unary operators
    connect(ui->plusminus_button, SIGNAL(released()),this,SLOT(unary_operation_pressed()));
    connect(ui->percent_button, SIGNAL(released()),this,SLOT(unary_operation_pressed()));

    // binary operators
    connect(ui->add_button, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->subtract_button, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->multiply_button, SIGNAL(released()),this,SLOT(binary_operation_pressed()));
    connect(ui->divide_button, SIGNAL(released()),this,SLOT(binary_operation_pressed()));

    // make the binary buttons such that we can check them as bool when operating
    ui->add_button->setCheckable(true);
    ui->subtract_button->setCheckable(true);
    ui->multiply_button->setCheckable(true);
    ui->divide_button->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    //qDebug() << "test";

    // stores the pointer to the button pressed
    QPushButton *button = (QPushButton *)sender();

    // makes a variable (double) to concatenate the digits pressed
    double label_number;

    // uses a qstring to store the number so that it can be outputted on the label
    QString new_label;

    //concatenates the numbers and stores in variable
    label_number = (ui->label->text() + button->text()).toDouble();

    // store the double number in qstring. 'g' indicates char format(chk form doc). 15 indicates precision
    new_label = QString::number(label_number,'g',15);

    if (is_entering_second_number) {
        // Clear the label for the second number and reset the flag
        new_label = button->text();
        is_entering_second_number = false;
    } else {
        // Append the digit to the current label text
        new_label = ui->label->text() + button->text();
    }

    // visualization of qstring on label
    ui->label->setText(new_label);
}

void MainWindow::on_decimal_button_released()
{
    // appends a decimal after the text in the text label
    if(!ui->label->text().contains("."))
    {
        // append if not alr present
        ui->label->setText(ui->label->text() + ".");
    }
    else
    {
        // do nothing
        // qDebug() << "Decimal Point already exists!";
    }
}

void MainWindow::unary_operation_pressed()
{
    // checks button pressed
    QPushButton *button = (QPushButton *)sender();

    // variable for label number
    double label_number;

    // uses a qstring to store the label number
    QString new_label;

    if(button->text() == "+/-")
    {
        // negate number on label
        label_number = ui->label->text().toDouble();
        label_number = label_number * -1;
        new_label = QString::number(label_number, 'g', 15);
        ui->label->setText(new_label);
    }

    if(button->text() == "%")
    {
        // divide 100 to number on label
        label_number = ui->label->text().toDouble();
        label_number = label_number * 0.01;
        new_label = QString::number(label_number, 'g', 15);
        ui->label->setText(new_label);
    }
}

void MainWindow::on_clear_button_released()
{

}


void MainWindow::on_equals_button_released()
{
    double label_number, second_number;
    // uses a qstring to store the result number
    QString result_number;

    // sets the number on the label as second label
    second_number = ui->label->text().toDouble();

    // conditions check for each binary operator
    if(ui->add_button->isChecked())
    {
        label_number = first_number + second_number;
        result_number = QString::number(label_number, 'g', 15);
        ui->label->setText(result_number);
        ui->add_button->setChecked(false);
    }
    else if(ui->subtract_button->isChecked())
    {
        label_number = first_number - second_number;
        result_number = QString::number(label_number, 'g', 15);
        ui->label->setText(result_number);
        ui->subtract_button->setChecked(false);
    }
    else if(ui->multiply_button->isChecked())
    {
        label_number = first_number * second_number;
        result_number = QString::number(label_number, 'g', 15);
        ui->label->setText(result_number);
        ui->multiply_button->setChecked(false);
    }
    else if(ui->divide_button->isChecked())
    {
        label_number = first_number / second_number;
        result_number = QString::number(label_number, 'g', 15);
        ui->label->setText(result_number);
        ui->divide_button->setChecked(false);
    }

    // Reset the flag
    is_entering_second_number = false;
}

void MainWindow::binary_operation_pressed()
{
    // checks button pressed
    QPushButton *button = (QPushButton *)sender();

    first_number = ui->label->text().toDouble();

    // to check operator pressed
    button->setChecked(true);

    // Clear the label for the second number (use this if you want a clear screen when you input operator
    //ui->label->clear();

    // Indicate that the next input is for the second number
    is_entering_second_number = true;

    // view the operation that is being performed
    // ui->label->setText(button->text());
}
