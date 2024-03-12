#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <mutex>
#include <task.h>
#include <QValidator>
#include <QMessageBox>

std::mutex Mut1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    codec = QTextCodec::codecForName("CP1251");
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
        QMessageBox::critical(this, codec->toUnicode("���������� �������"), codec->toUnicode("���������� �������� ���������� �������. ���������� ���"), codec->toUnicode("�������"));
        return;
    }
    unsigned int val = ui->ThrQuantity->text().toUInt();
    if(Pull.SetThreadQuantity(val))
    {
        ui->CurrentThrQuantity->setText(QString::number(val));
        QMessageBox::information(this, codec->toUnicode("���������� �������"), codec->toUnicode("���������� ������� �����������"), codec->toUnicode("�������"));
    }
    else
    {
      QMessageBox::critical(this, codec->toUnicode("���������� �������"), codec->toUnicode("���������� ������� �� �����������"), codec->toUnicode("�������"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    unsigned int tmp = 0;
    tmp = ui->NumberToFactorial->text().toUInt();

    if(tmp < 1)
    {
        QMessageBox::critical(this, codec->toUnicode("���� �����"), codec->toUnicode("������� ������������� �����"), codec->toUnicode("�������"));
    }

    Task task(tmp);
    Pull.submit(task);

    tmp = ui->TaskQuantity->text().toUInt();
    ++tmp;
    ui->TaskQuantity->setText(QString::number(tmp));
}

void MainWindow::LogChanged(QString str)
{
    ui->LogEdit->append(str);
}
