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
    Q_PROPERTY(bool doEvolve READ getDoEvolve WRITE setDoEvolve DESIGNABLE true)
    Q_PROPERTY(int generationCount READ getGenerationCount WRITE setGenerationCount DESIGNABLE true)

public:
    explicit GridWidget(QWidget* parent = nullptr);
    ~GridWidget();

    int getRowCount() const;
    int getColumnCount() const;
    int getGenerationCount() const;

    QColor getUniverseBorderColour() const;
    void setUniverseBorderColour(const QColor& colour);

    qreal getUniverseBorderThickness() const;
    void setUniverseBorderThickness(const qreal& thickness);

    QColor getUniverseFieldColour() const;
    void setUniverseFieldColour(const QColor& colour);

    QColor getCellFieldColour() const;
    void setCellFieldColour(const QColor& colour);

    bool getDoEvolve() const;
    void setDoEvolve(const bool& cmd);

    enum cellPopulationOption
    {
        Empty,
        Filled,
        Chequered,
        Random
    };

public slots:
    void setRowCount(const int& nRows);
    void setColumnCount(const int& nColumns);
    void setGenerationCount(const int& nGenerations);

    void createGrid(cellPopulationOption pattern);
    void deleteGrid();

    void stopEvolve();

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

signals:
    void generationCountChanged(const int& nGenerations);
    void universeSizeNotAdjustable(const bool& cmd);
    void universeSizeAdjustable(const bool& cmd);

private:
    /* game settings */
    int rowCount = 20;
    int columnCount = 20;
    int** grid;
    QTimer* timer;
    bool doEvolve = false;
    int generationCount = 0;

    void setTimer();
    void evolveContinuous();
    int randomCellStateGenerator();

    void createEmptyGrid();
    void createFilledGrid();
    void createChequeredGrid();
    void createRandomGrid();

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
    void toggleEvolveDecision();
};

#endif // GRIDWIDGET_H
