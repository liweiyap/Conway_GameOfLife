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
    Q_PROPERTY(QColor buttonTextColour READ getButtonTextColour WRITE setButtonTextColour DESIGNABLE true)

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    QColor getButtonTextColour() const;
    void setButtonTextColour(const QColor& colour);

private:
    Ui::MainWindow* ui;
    GridWidget* grid;

    QColor buttonTextColour = Qt::white;

    void setLayout();
    void setRowCountSlider();
    void setColumnCountSlider();
    void setGenerationSpeedSlider();
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
    void setGenerationCountInfo(const int& nGenerations);
    void editStartOrStopEvolvingButton();

    void resetGrid(GridWidget::cellPopulationOption pattern);
    void resetGenerationCount();
};
#endif // MAINWINDOW_H
