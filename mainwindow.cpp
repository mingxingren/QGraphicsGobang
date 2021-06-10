#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphicsscene.h"
#include "bggraphicsitem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->_InitUi();

    m_pScene = new CGraphicsScene(this);
    ui->gvWindow->setScene(m_pScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_InitUi()
{
    this->setWindowTitle("五子棋");
}

