#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <threadpull.h>
#include <QTextCodec>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbStart_clicked();

    void on_pbStop_clicked();

    void on_SetThrQuantity_clicked();

private:
    QTextCodec *codec;
    Ui::MainWindow *ui;
    ThreadPull Pull;
};
#endif // MAINWINDOW_H
