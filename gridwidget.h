#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>

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

    QColor getUniverseBorderColour() const;
    void setUniverseBorderColour(const QColor& colour);

    qreal getUniverseBorderThickness() const;
    void setUniverseBorderThickness(const qreal& thickness);

    QColor getUniverseFieldColour() const;
    void setUniverseFieldColour(const QColor& colour);

    QColor getCellFieldColour() const;
    void setCellFieldColour(const QColor& colour);

public slots:
    void setRowCount(const int& nRows);
    void setColumnCount(const int& nColumns);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    /* game settings */
    int rowCount = 20;
    int columnCount = 20;
    int** grid;
    QTimer* timer;

    void createChequeredGrid();
    void deleteGrid();
    void setTimer();

    /* design settings */
    QColor universeBorderColour = "#3873b3";
    qreal universeBorderThickness = 8.0;
    QColor universeFieldColour = Qt::white;
    QColor cellFieldColour = Qt::black;

    void setTransparency();

    qreal calcUniverseWidth();
    qreal calcUniverseHeight();
    qreal calcCellWidth();
    qreal calcCellHeight();

    void paintUniverseBorder(QPainter& painter);
    void paintCellGrid(QPainter& painter);

private slots:
    void evolveOnce();
    void evolveContinuous();
};

#endif // GRIDWIDGET_H
