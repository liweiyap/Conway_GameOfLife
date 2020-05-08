#include <cmath>

#include <QPainter>
#include <QMouseEvent>

#include "gridwidget.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellFieldColour.setAlpha(255);

    grid = new int*[getRowCount()];
    for (size_t rowIdx = 0; rowIdx < getRowCount(); ++rowIdx)
    {
        grid[rowIdx] = new int[getColumnCount()];
        for (size_t columnIdx = 0; columnIdx < getColumnCount(); ++columnIdx)
        {
            grid[rowIdx][columnIdx] = ((rowIdx + columnIdx) & 1) ? 0 : 1;
        }
    }
}

GridWidget::~GridWidget()
{
    for (size_t rowIdx = 0; rowIdx < getRowCount(); ++rowIdx)
    {
        delete[] grid[rowIdx];
    }
    delete[] grid;
}

size_t GridWidget::getRowCount() const
{
    return rowCount;
}

void GridWidget::setRowCount(const size_t nRows)
{
    rowCount = nRows;
}

size_t GridWidget::getColumnCount() const
{
    return columnCount;
}

void GridWidget::setColumnCount(const size_t nColumns)
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

    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(getUniverseFieldColour()));
    painter.fillRect(universeBorder, painter.brush());
    painter.setPen(QPen(getUniverseBorderColour(), getUniverseBorderThickness()));
    painter.drawRect(universeBorder);

    for (size_t rowIdx = 0; rowIdx < getRowCount(); ++rowIdx)
    {
        for (size_t columnIdx = 0; columnIdx < getColumnCount(); ++columnIdx)
        {
            if (grid[rowIdx][columnIdx] == 1)
            {
                qreal cellLeftIdx = 0.75 * getUniverseBorderThickness() + calcCellWidth() * columnIdx;
                qreal cellTopIdx = 0.75 * getUniverseBorderThickness() + calcCellHeight() * rowIdx;
                QRect cellField(cellLeftIdx, cellTopIdx, calcCellWidth(), calcCellHeight());
                painter.setBrush(QBrush(getCellFieldColour()));
                painter.fillRect(cellField, painter.brush());
            }
        }
    }
}

void GridWidget::mousePressEvent(QMouseEvent* event)
{
    size_t rowIdx = static_cast<size_t>(std::floor((event->y() - 0.75 * getUniverseBorderThickness()) / calcCellHeight()));
    size_t columnIdx = static_cast<size_t>(std::floor((event->x() - 0.75 * getUniverseBorderThickness()) / calcCellWidth()));
    grid[rowIdx][columnIdx] ^= 1;
    update();
}

qreal GridWidget::calcUniverseWidth()
{
    return width() - 1.5 * getUniverseBorderThickness();
}

qreal GridWidget::calcUniverseHeight()
{
    return height() - 1.5 * getUniverseBorderThickness();
}

qreal GridWidget::calcCellWidth()
{
    return calcUniverseWidth() / getRowCount();
}

qreal GridWidget::calcCellHeight()
{
    return calcUniverseHeight() / getColumnCount();
}
