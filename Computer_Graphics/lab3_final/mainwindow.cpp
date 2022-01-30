#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->handler, &ParamHandler::SendParameter, ui->widget, &GraphicWidget::SetParameter);
    ui->handler->Setup();

}

MainWindow::~MainWindow()
{
    delete ui;
}

