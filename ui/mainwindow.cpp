#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWindow_tabCloseRequested(int index)
{
    ui->tabWindow->removeTab(index);
}

void MainWindow::on_addSensor_clicked()
{
    ui->tabWindow->addTab(new Sensor(), QString("GPS %0").arg(ui->tabWindow->count() + 1));
    ui->tabWindow->setCurrentIndex(ui->tabWindow->count() - 1);
}


