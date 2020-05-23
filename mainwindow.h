#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gridwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    GridWidget* grid;

    void setLayout();
    void setRowCountSlider();
    void setColumnCountSlider();
    void setEvolveOnceButton();
    void setStartOrStopEvolvingButton();
    void setEmptyGridButton();
    void setFilledGridButton();
    void setChequeredGridButton();
    void setRandomGridButton();

    void editStartOrStopEvolvingButtonHelper(const char* cmd);

private slots:
    void setRowCountInfo(const int& nRows);
    void setColumnCountInfo(const int& nColumns);
    void editStartOrStopEvolvingButton();

    void resetGrid();
};
#endif // MAINWINDOW_H
