#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <mutex>

std::mutex Mut1;

void f1() {Mut1.lock(); std::cout << "1 function" << std::endl; Mut1.unlock();}
void f2() {Mut1.lock(); std::cout << "2 function" << std::endl; Mut1.unlock();}
void f3() {Mut1.lock(); std::cout << "3 function" << std::endl; Mut1.unlock();}
void f4() {Mut1.lock(); std::cout << "4 function" << std::endl; Mut1.unlock();}
void f5() {Mut1.lock();std::cout << "5 function" << std::endl; Mut1.unlock();}

//uint factorial(uint x)
//{
//    if(x <= 1) return 1;
//    return x * factorial(x - 1);
//}

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

    Pull.StartThreads();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbStart_clicked()
{
    for (int i = 0; i < 1000; i++)
    {
        Pull.submit(f1);
        Pull.submit(f2);
        Pull.submit(f3);
        Pull.submit(f4);
        Pull.submit(f5);
    }
    Pull.StartThreads();
}

void MainWindow::on_pbStop_clicked()
{
    Pull.StopThreads();
}
