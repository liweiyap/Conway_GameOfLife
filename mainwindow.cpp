#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gridwidget.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , grid(new GridWidget(this))
{
    ui->setupUi(this);

    setLayout();
    ui->gridLayout->addWidget(grid);

    setRowCountSlider();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLayout()
{
    ui->mainLayout->setStretchFactor(ui->controlLayout, 4);
    ui->mainLayout->setStretchFactor(ui->gridLayout, 6);
}

void MainWindow::setRowCountSlider()
{
    ui->rowCountSlider->setMaximum(50);
    ui->rowCountSlider->setMinimum(1);
    ui->rowCountSlider->setValue(20);
    ui->rowCountSlider->setTickPosition(QSlider::TicksBelow);

    connect(ui->rowCountSlider, SIGNAL(valueChanged(int)), grid, SLOT(setRowCount(const int&)));
}
