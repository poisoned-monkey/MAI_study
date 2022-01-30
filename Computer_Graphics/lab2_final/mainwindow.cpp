#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->handler, &ParamHandler::SendParameters, ui->widget, &GraphicWidget::SetParameters);
    ui->handler->Setup();

}

MainWindow::~MainWindow()
{
    delete ui;
}

