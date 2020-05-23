#include <cmath>

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include "gridwidget.h"
#include "gamelogic.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{
    setTransparency();
    setTimer();
    createChequeredGrid();
}

GridWidget::~GridWidget()
{
    deleteGrid();
}

int GridWidget::getRowCount() const
{
    return rowCount;
}

void GridWidget::setRowCount(const int& nRows)
{
    deleteGrid();
    rowCount = nRows;
    createChequeredGrid();
    update();
}

int GridWidget::getColumnCount() const
{
    return columnCount;
}

void GridWidget::setColumnCount(const int& nColumns)
{
    deleteGrid();
    columnCount = nColumns;
    createChequeredGrid();
    update();
}

QColor GridWidget::getUniverseBorderColour() const
{
    return universeBorderColour;
}

void GridWidget::setUniverseBorderColour(const QColor& colour)
{
    universeBorderColour = colour;
}

qreal GridWidget::getUniverseBorderThickness() const
{
    return universeBorderThickness;
}

void GridWidget::setUniverseBorderThickness(const qreal& thickness)
{
    universeBorderThickness = thickness;
}

QColor GridWidget::getUniverseFieldColour() const
{
    return universeFieldColour;
}

void GridWidget::setUniverseFieldColour(const QColor& colour)
{
    universeFieldColour = colour;
}

QColor GridWidget::getCellFieldColour() const
{
    return cellFieldColour;
}

void GridWidget::setCellFieldColour(const QColor& colour)
{
    cellFieldColour = colour;
}

void GridWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    paintUniverseBorder(painter);
    paintCellGrid(painter);
}

void GridWidget::mousePressEvent(QMouseEvent* event)
{
    int rowIdx = static_cast<int>(std::floor((event->y() - 0.75 * universeBorderThickness) / calcCellHeight()));
    int columnIdx = static_cast<int>(std::floor((event->x() - 0.75 * universeBorderThickness) / calcCellWidth()));
    grid[rowIdx][columnIdx] ^= 1;
    update();
}

void GridWidget::paintUniverseBorder(QPainter& painter)
{
    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(universeFieldColour));
    painter.fillRect(universeBorder, painter.brush());
    painter.setPen(QPen(universeBorderColour, universeBorderThickness));
    painter.drawRect(universeBorder);
}

void GridWidget::paintCellGrid(QPainter& painter)
{
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx)
        {
            if (grid[rowIdx][columnIdx] == 1)
            {
                qreal cellLeftIdx = 0.75 * universeBorderThickness + calcCellWidth() * columnIdx;
                qreal cellTopIdx = 0.75 * universeBorderThickness + calcCellHeight() * rowIdx;
                QRect cellField(cellLeftIdx, cellTopIdx, calcCellWidth(), calcCellHeight());
                painter.setBrush(QBrush(cellFieldColour));
                painter.fillRect(cellField, painter.brush());
            }
        }
    }
}

void GridWidget::deleteGrid()
{
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        delete[] grid[rowIdx];
    }
    delete[] grid;
}

void GridWidget::createChequeredGrid()
{
    grid = new int*[rowCount];
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        grid[rowIdx] = new int[columnCount];
        for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx)
        {
            grid[rowIdx][columnIdx] = ((rowIdx + columnIdx) & 1) ? 0 : 1;
        }
    }
}

void GridWidget::setTimer()
{
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(evolveOnce()));
}

void GridWidget::setTransparency()
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellFieldColour.setAlpha(255);
}

qreal GridWidget::calcUniverseWidth()
{
    return width() - 1.5 * universeBorderThickness;
}

qreal GridWidget::calcUniverseHeight()
{
    return height() - 1.5 * universeBorderThickness;
}

qreal GridWidget::calcCellWidth()
{
    return calcUniverseWidth() / columnCount;
}

qreal GridWidget::calcCellHeight()
{
    return calcUniverseHeight() / rowCount;
}

void GridWidget::evolveOnce()
{
    evolveNextGeneration(grid, rowCount, columnCount);
    update();
}

void GridWidget::evolveContinuous()
{
    timer->start();
}
