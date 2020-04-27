#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

namespace Ui { class gridwidget; }

class GridWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(size_t rowCount READ getRowCount WRITE setRowCount DESIGNABLE true)
    Q_PROPERTY(size_t columnCount READ getColumnCount WRITE setColumnCount DESIGNABLE true)
    Q_PROPERTY(QColor universeBorderColour READ getUniverseBorderColour WRITE setUniverseBorderColour DESIGNABLE true)
    Q_PROPERTY(qreal universeBorderThickness READ getUniverseBorderThickness WRITE setUniverseBorderThickness DESIGNABLE true)
    Q_PROPERTY(QColor universeFieldColour READ getUniverseFieldColour WRITE setUniverseFieldColour DESIGNABLE true)
    Q_PROPERTY(QColor cellFieldColour READ getCellFieldColour WRITE setCellFieldColour DESIGNABLE true)

public:
    explicit GridWidget(QWidget* parent = nullptr);
    ~GridWidget();

    size_t getRowCount() const;
    void setRowCount(const size_t nRows);

    size_t getColumnCount() const;
    void setColumnCount(const size_t nColumnss);

    QColor getUniverseBorderColour() const;
    void setUniverseBorderColour(const QColor colour);

    qreal getUniverseBorderThickness() const;
    void setUniverseBorderThickness(const qreal thickness);

    QColor getUniverseFieldColour() const;
    void setUniverseFieldColour(const QColor colour);

    QColor getCellFieldColour() const;
    void setCellFieldColour(const QColor colour);

protected:
    void paintEvent(QPaintEvent* event);

private:
    /* game settings */
    size_t rowCount = 20;
    size_t columnCount = 20;
    int** grid;

    /* design settings */
    QColor universeBorderColour = "#3873b3";
    qreal universeBorderThickness = 8.0;
    QColor universeFieldColour = Qt::white;
    QColor cellFieldColour = Qt::black;
};

#endif // GRIDWIDGET_H
