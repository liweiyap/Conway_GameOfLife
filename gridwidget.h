#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

namespace Ui { class gridwidget; }

class GridWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ getRowCount WRITE setRowCount DESIGNABLE true)
    Q_PROPERTY(int columnCount READ getColumnCount WRITE setColumnCount DESIGNABLE true)
    Q_PROPERTY(QColor universeBorderColour READ getUniverseBorderColour WRITE setUniverseBorderColour DESIGNABLE true)
    Q_PROPERTY(qreal universeBorderThickness READ getUniverseBorderThickness WRITE setUniverseBorderThickness DESIGNABLE true)
    Q_PROPERTY(QColor universeFieldColour READ getUniverseFieldColour WRITE setUniverseFieldColour DESIGNABLE true)
    Q_PROPERTY(QColor cellFieldColour READ getCellFieldColour WRITE setCellFieldColour DESIGNABLE true)

public:
    explicit GridWidget(QWidget* parent = nullptr);
    ~GridWidget();

    int getRowCount() const;

    int getColumnCount() const;
    void setColumnCount(const int nColumnss);

    QColor getUniverseBorderColour() const;
    void setUniverseBorderColour(const QColor colour);

    qreal getUniverseBorderThickness() const;
    void setUniverseBorderThickness(const qreal thickness);

    QColor getUniverseFieldColour() const;
    void setUniverseFieldColour(const QColor colour);

    QColor getCellFieldColour() const;
    void setCellFieldColour(const QColor colour);

public slots:
    void setRowCount(const int& nRows);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    /* game settings */
    int rowCount = 20;
    int columnCount = 20;
    int** grid;

    void createGrid();
    void deleteGrid();

    /* design settings */
    QColor universeBorderColour = "#3873b3";
    qreal universeBorderThickness = 8.0;
    QColor universeFieldColour = Qt::white;
    QColor cellFieldColour = Qt::black;

    qreal calcUniverseWidth();
    qreal calcUniverseHeight();
    qreal calcCellWidth();
    qreal calcCellHeight();

    void paintUniverseBorder(QPainter& painter);
    void paintCellGrid(QPainter& painter);
};

#endif // GRIDWIDGET_H
