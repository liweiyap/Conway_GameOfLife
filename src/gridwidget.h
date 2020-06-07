#ifndef GRIDWIDGET_H
#define GRIDWIDGET_H

#include <QWidget>
#include <random>

class GridWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int rowCount READ getRowCount WRITE setRowCount DESIGNABLE true)
    Q_PROPERTY(int columnCount READ getColumnCount WRITE setColumnCount DESIGNABLE true)
    Q_PROPERTY(QColor universeBorderColour READ getUniverseBorderColour WRITE setUniverseBorderColour DESIGNABLE true)
    Q_PROPERTY(qreal universeBorderThickness READ getUniverseBorderThickness WRITE setUniverseBorderThickness DESIGNABLE true)
    Q_PROPERTY(QColor universeFieldColour READ getUniverseFieldColour WRITE setUniverseFieldColour DESIGNABLE true)
    Q_PROPERTY(QColor cellFieldColour READ getCellFieldColour WRITE setCellFieldColour DESIGNABLE true)
    Q_PROPERTY(qreal cellGridMargin READ getCellGridMargin WRITE setCellGridMargin DESIGNABLE true)
    Q_PROPERTY(bool doEvolve READ getDoEvolve WRITE setDoEvolve DESIGNABLE true)
    Q_PROPERTY(int generationCount READ getGenerationCount WRITE setGenerationCount DESIGNABLE true)

public:
    explicit GridWidget(QWidget* parent = nullptr);
    ~GridWidget();

    int getRowCount() const;
    int getColumnCount() const;
    int getGenerationCount() const;
    int getTimerInterval() const;

    QColor getUniverseBorderColour() const;
    void setUniverseBorderColour(const QColor& colour);

    qreal getUniverseBorderThickness() const;
    void setUniverseBorderThickness(const qreal& thickness);

    QColor getUniverseFieldColour() const;
    void setUniverseFieldColour(const QColor& colour);

    QColor getCellFieldColour() const;
    void setCellFieldColour(const QColor& colour);

    qreal getCellGridMargin() const;
    void setCellGridMargin(const qreal& margin);

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
    void setTimerInterval(const int& msec);

    void createGrid(cellPopulationOption pattern);
    void deleteGrid();

    void stopEvolve();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void generationCountChanged(const int& nGenerations);
    void universeSizeAdjustable(const bool& cmd);

private:
    /* game settings */
    int rowCount = 20;
    int columnCount = 20;
    int** grid;
    QTimer* timer;
    bool doEvolve = false;
    int generationCount = 0;
    cellPopulationOption lastDefaultPattern = Chequered;
    std::mt19937 randNumGenerator;
    std::uniform_int_distribution<int> randDistribution;

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
    qreal cellGridMargin = 1.0;

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
