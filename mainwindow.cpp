#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <mutex>
#include <task.h>
#include <QValidator>
#include <QMessageBox>

unsigned int factorial(const unsigned int &x)
{
    if(x <= 1) return 1;
    return x * factorial(x - 1);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
            QMessageBox::critical(this, "Количество потоков", "Невозможно изменить количество потоков. Остановите пул", "Закрыть");
            return;
        }
        unsigned int val = ui->ThrQuantity->text().toUInt();
        if(Pull.SetThreadQuantity(val))
        {
            ui->CurrentThrQuantity->setText(QString::number(val));
            QMessageBox::information(this, "Количество потоков", "Количество потоков установлено", "Закрыть");
        }
        else
        {
          QMessageBox::critical(this, "Количество потоков", "Количество потоков не установлено", "Закрыть");
        }
}

void MainWindow::on_pushButton_clicked()
{
    unsigned int tmp = 0;
    tmp = ui->NumberToFactorial->text().toUInt();

    if(tmp < 1 || tmp > 33)
    {
        QMessageBox::critical(this, "Ввод числа", "Введите число от 1 до 33", "Закрыть");
        return;
    }

    Task task(tmp);
    task.SetFunction(factorial);
    Pull.submit(task);

//    if(Pull.IsDone())
//    {
        tmp = ui->TaskQuantity->text().toUInt();
        ++tmp;
        ui->TaskQuantity->setText(QString::number(tmp));
//    }
}

void MainWindow::LogChanged(QString str)
{
    ui->LogEdit->append(str);
}
