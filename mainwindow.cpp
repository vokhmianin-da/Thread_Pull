#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

void f1() {std::cout << "1 function" << std::endl;}
void f2() {std::cout << "2 function" << std::endl;}
void f3() {std::cout << "3 function" << std::endl;}
void f4() {std::cout << "4 function" << std::endl;}
void f5() {std::cout << "5 function" << std::endl;}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Pull.submit(f1);
    Pull.submit(f2);
    Pull.submit(f3);
    Pull.submit(f4);
    Pull.submit(f5);

}

MainWindow::~MainWindow()
{
    delete ui;
}

