#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->handler->Setup();
    connect(ui->handler, &ParamHandler::SendParameters, ui->widget, &GraphicWidget::SetParameters);


}

MainWindow::~MainWindow()
{
    delete ui;
}
