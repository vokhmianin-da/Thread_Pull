#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <mutex>
#include <task.h>
#include <QValidator>
#include <QMessageBox>

std::mutex Mut1;

//void f1() {Mut1.lock(); std::cout << "1 function" << std::endl; Mut1.unlock();}
//void f2() {Mut1.lock(); std::cout << "2 function" << std::endl; Mut1.unlock();}
//void f3() {Mut1.lock(); std::cout << "3 function" << std::endl; Mut1.unlock();}
//void f4() {Mut1.lock(); std::cout << "4 function" << std::endl; Mut1.unlock();}
//void f5() {Mut1.lock();std::cout << "5 function" << std::endl; Mut1.unlock();}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    codec = QTextCodec::codecForName("CP1251");
    ui->ThrQuantity->setValidator(new QIntValidator(this));
    ui->NumberToFactorial->setValidator(new QIntValidator(this));

//    for (unsigned int i = 1; i < 6; ++i)
//    {
//        Task task(i);
//        Pull.submit(task);
//    }

//    Pull.submit(f1);
//    Pull.submit(f2);
//    Pull.submit(f3);
//    Pull.submit(f4);
//    Pull.submit(f5);

//    Pull.StartThreads();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbStart_clicked()
{
//    for (unsigned int i = 5; i < 1000; i++)
//    {
////        Pull.submit(f1);
////        Pull.submit(f2);
////        Pull.submit(f3);
////        Pull.submit(f4);
////        Pull.submit(f5);
//        Task task(i % 10);
//        Pull.submit(task);
//    }
    Pull.StartThreads();
}

void MainWindow::on_pbStop_clicked()
{
    Pull.StopThreads();
    ui->TaskQuantity->setText(QString::number(Pull.GetTasks()));
}

void MainWindow::on_SetThrQuantity_clicked()
{
    if(!Pull.IsDone())
    {
        QMessageBox::critical(this, codec->toUnicode("Количество потоков"), codec->toUnicode("Невозможно изменить количество потоков. Остановите пул"), codec->toUnicode("Закрыть"));
        return;
    }
    unsigned int val = ui->ThrQuantity->text().toUInt();
    if(Pull.SetThreadQuantity(val))
    {
        ui->CurrentThrQuantity->setText(QString::number(val));
        QMessageBox::information(this, codec->toUnicode("Количество потоков"), codec->toUnicode("Количество потоков установлено"), codec->toUnicode("Закрыть"));
    }
    else
    {
      QMessageBox::critical(this, codec->toUnicode("Количество потоков"), codec->toUnicode("Количество потоков не установлено"), codec->toUnicode("Закрыть"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    unsigned int tmp = 0;
    tmp = ui->NumberToFactorial->text().toUInt();

    Task task(tmp);
    Pull.submit(task);

    tmp = ui->TaskQuantity->text().toUInt();
    ++tmp;
    ui->TaskQuantity->setText(QString::number(tmp));
}
