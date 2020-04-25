#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

namespace Ui { class gridwidget; }

class GridWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor universeBorderColour READ getUniverseBorderColour WRITE setUniverseBorderColour DESIGNABLE true)
    Q_PROPERTY(qreal universeBorderThickness READ getUniverseBorderThickness WRITE setUniverseBorderThickness DESIGNABLE true)

public:
    explicit GridWidget(QWidget* parent = nullptr);
    ~GridWidget() = default;

    QColor getUniverseBorderColour() const;
    void setUniverseBorderColour(const QColor colour);

    qreal getUniverseBorderThickness() const;
    void setUniverseBorderThickness(const qreal thickness);

protected:
    void paintEvent(QPaintEvent* event);

private:
    QColor universeBorderColour = "#3873b3";
    qreal universeBorderThickness = 6.0;
};

#endif // GRIDWIDGET_H
