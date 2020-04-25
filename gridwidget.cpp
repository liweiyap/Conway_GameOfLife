#include <QPainter>

#include "gridwidget.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{
    universeBorderColour.setAlpha(255);
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

void GridWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QRect universeBorder(0, 0, width(), height());
    painter.setPen(QPen(getUniverseBorderColour(), getUniverseBorderThickness()));
    painter.drawRect(universeBorder);
}
