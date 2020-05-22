#include <cmath>

#include <QPainter>
#include <QMouseEvent>

#include "gridwidget.h"
#include <iostream>

GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellFieldColour.setAlpha(255);

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

GridWidget::~GridWidget()
{
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        delete[] grid[rowIdx];
    }
    delete[] grid;
}

int GridWidget::getRowCount() const
{
    return rowCount;
}

void GridWidget::setRowCount(const int nRows)
{
    rowCount = nRows;
    resetGrid();
    update();
}

int GridWidget::getColumnCount() const
{
    return columnCount;
}

void GridWidget::setColumnCount(const int nColumns)
{
    columnCount = nColumns;
}

QColor GridWidget::getUniverseBorderColour() const
{
    return universeBorderColour;
}

void GridWidget::setUniverseBorderColour(const QColor colour)
{
    universeBorderColour = colour;
}

qreal GridWidget::getUniverseBorderThickness() const
{
    return universeBorderThickness;
}

void GridWidget::setUniverseBorderThickness(const qreal thickness)
{
    universeBorderThickness = thickness;
}

QColor GridWidget::getUniverseFieldColour() const
{
    return universeFieldColour;
}

void GridWidget::setUniverseFieldColour(const QColor colour)
{
    universeFieldColour = colour;
}

QColor GridWidget::getCellFieldColour() const
{
    return cellFieldColour;
}

void GridWidget::setCellFieldColour(const QColor colour)
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
    size_t rowIdx = static_cast<size_t>(std::floor((event->y() - 0.75 * universeBorderThickness) / calcCellHeight()));
    size_t columnIdx = static_cast<size_t>(std::floor((event->x() - 0.75 * universeBorderThickness) / calcCellWidth()));
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

void GridWidget::resetGrid()
{
    for (int rowIdx = 0; rowIdx < getRowCount(); ++rowIdx)
    {
        delete[] grid[rowIdx];
    }
    delete[] grid;

    grid = new int*[getRowCount()];
    for (int rowIdx = 0; rowIdx < getRowCount(); ++rowIdx)
    {
        grid[rowIdx] = new int[getColumnCount()];
        for (int columnIdx = 0; columnIdx < getColumnCount(); ++columnIdx)
        {
            grid[rowIdx][columnIdx] = ((rowIdx + columnIdx) & 1) ? 0 : 1;
        }
    }
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
    return calcUniverseWidth() / rowCount;
}

qreal GridWidget::calcCellHeight()
{
    return calcUniverseHeight() / columnCount;
}
