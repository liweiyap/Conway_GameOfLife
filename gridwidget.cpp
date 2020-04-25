#include <QPainter>

#include "gridwidget.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent)
{
    setUniverseBorderColour("#3873b3");
    setUniverseBorderThickness(6.0);
}

QColor GridWidget::getUniverseBorderColour() const
{
    return universeBorderColour;
}

void GridWidget::setUniverseBorderColour(const QColor colour)
{
    universeBorderColour = colour;
    universeBorderColour.setAlpha(255);
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
