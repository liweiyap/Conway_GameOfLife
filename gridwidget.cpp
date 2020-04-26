#include <QPainter>

#include "gridwidget.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);

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

void GridWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(getUniverseFieldColour()));
    painter.fillRect(universeBorder, painter.brush());
    painter.setPen(QPen(getUniverseBorderColour(), getUniverseBorderThickness()));
    painter.drawRect(universeBorder);

    qreal universeWidth = width() - 1.5 * getUniverseBorderThickness();
    qreal universeHeight = height() - 1.5 * getUniverseBorderThickness();
    qreal cellWidth = universeWidth / getRowCount();
    qreal cellHeight = universeHeight / getColumnCount();

    for (size_t rowIdx = 0; rowIdx < getRowCount(); ++rowIdx)
    {
        for (size_t columnIdx = 0; columnIdx < getColumnCount(); ++columnIdx)
        {
            if (grid[rowIdx][columnIdx] == 1)
            {
                qreal cellLeftIdx = 0.75 * getUniverseBorderThickness() + cellWidth * columnIdx;
                qreal cellTopIdx = 0.75 * getUniverseBorderThickness() + cellHeight * rowIdx;
                QRect cellBorder(cellLeftIdx, cellTopIdx, cellWidth, cellHeight);
                painter.setBrush(QBrush(Qt::black));
                painter.fillRect(cellBorder, painter.brush());
            }
        }
    }
}
