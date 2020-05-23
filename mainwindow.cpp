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
    setColumnCountSlider();
}

MainWindow::~MainWindow()
{
    delete grid;
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
    connect(ui->rowCountSlider, SIGNAL(valueChanged(int)), this, SLOT(setRowCountInfo(const int&)));
}

void MainWindow::setColumnCountSlider()
{
    ui->columnCountSlider->setMaximum(50);
    ui->columnCountSlider->setMinimum(1);
    ui->columnCountSlider->setValue(20);
    ui->columnCountSlider->setTickPosition(QSlider::TicksBelow);

    connect(ui->columnCountSlider, SIGNAL(valueChanged(int)), grid, SLOT(setColumnCount(const int&)));
    connect(ui->columnCountSlider, SIGNAL(valueChanged(int)), this, SLOT(setColumnCountInfo(const int&)));
}

void MainWindow::setRowCountInfo(const int& nRows)
{
    int newStrLen = snprintf(NULL, 0, "No. of rows: %d", nRows) + 1;
    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "No. of rows: %d", nRows);

    QString newStr = buffer;
    ui->rowCountSliderInfo->setText(newStr);
}

void MainWindow::setColumnCountInfo(const int& nColumns)
{
    int newStrLen = snprintf(NULL, 0, "No. of columns: %d", nColumns) + 1;
    char buffer[newStrLen];
    snprintf(buffer, newStrLen, "No. of columns: %d", nColumns);

    QString newStr = buffer;
    ui->columnCountSliderInfo->setText(newStr);
}
