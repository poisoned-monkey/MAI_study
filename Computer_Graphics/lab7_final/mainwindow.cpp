#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->widget, &ParamHandler::Send, ui->graphicsView, &GraphicWidget::SetParams);
    ui->widget->Setup();

}

MainWindow::~MainWindow()
{
    delete ui;
}

