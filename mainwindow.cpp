#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <mutex>
#include <task.h>
#include <QValidator>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#ifndef __unix__
    codec = QTextCodec::codecForName("CP1251");
#else
    codec = QTextCodec::codecForName("UTF-8");
#endif
    ui->ThrQuantity->setValidator(new QIntValidator(this));
    ui->NumberToFactorial->setValidator(new QIntValidator(this));

    connect(&Pull.MessageSender, SIGNAL(SendMessage(QString)), this, SLOT(LogChanged(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pbStart_clicked()
{

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

    if(tmp < 1 || tmp > 33)
    {
        QMessageBox::critical(this, codec->toUnicode("Ввод числа"), codec->toUnicode("Введите число от 1 до 33"), codec->toUnicode("Закрыть"));
        return;
    }

    Task task(tmp);
    Pull.submit(task);

    if(Pull.IsDone())
    {
        tmp = ui->TaskQuantity->text().toUInt();
        ++tmp;
        ui->TaskQuantity->setText(QString::number(tmp));
    }
}

void MainWindow::LogChanged(QString str)
{
    ui->LogEdit->append(str);
}
