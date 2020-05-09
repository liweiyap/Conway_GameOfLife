#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridwidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , grid(new GridWidget(this))
{
    ui->setupUi(this);

    ui->mainLayout->setStretchFactor(ui->controlLayout, 4);
    ui->mainLayout->setStretchFactor(ui->gridLayout, 6);
    ui->gridLayout->addWidget(grid);
}

MainWindow::~MainWindow()
{
    delete ui;
}
