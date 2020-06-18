#include <cmath>

#include <QPainter>
#include <QMouseEvent>
#include <QTimer>

#include "gridwidget.h"
#include "gamelogic.h"

GridWidget::GridWidget(QWidget* parent) : QWidget(parent), randNumGenerator((std::random_device())()), randDistribution(1, 10)
{
    setTransparency();
    setTimer();
    createGrid(lastDefaultPattern);
}

GridWidget::~GridWidget()
{
    delete timer;
    deleteGrid();
}

int GridWidget::getRowCount() const
{
    return rowCount;
}

void GridWidget::setRowCount(const int& nRows)
{
    deleteGrid();
    rowCount = nRows;
    createGrid(lastDefaultPattern);
    update();
}

int GridWidget::getColumnCount() const
{
    return columnCount;
}

void GridWidget::setColumnCount(const int& nColumns)
{
    deleteGrid();
    columnCount = nColumns;
    createGrid(lastDefaultPattern);
    update();
}

int GridWidget::getGenerationCount() const
{
    return generationCount;
}

void GridWidget::setGenerationCount(const int& nGenerations)
{
    generationCount = nGenerations;
}

int GridWidget::getTimerInterval() const
{
    return timer->interval();
}

void GridWidget::setTimerInterval(const int& msec)
{
    timer->setInterval(msec);
}

QColor GridWidget::getUniverseBorderColour() const
{
    return universeBorderColour;
}

void GridWidget::setUniverseBorderColour(const QColor& colour)
{
    universeBorderColour = colour;
}

qreal GridWidget::getUniverseBorderThickness() const
{
    return universeBorderThickness;
}

void GridWidget::setUniverseBorderThickness(const qreal& thickness)
{
    universeBorderThickness = thickness;
}

QColor GridWidget::getUniverseFieldColour() const
{
    return universeFieldColour;
}

void GridWidget::setUniverseFieldColour(const QColor& colour)
{
    universeFieldColour = colour;
}

QColor GridWidget::getCellFieldColour() const
{
    return cellFieldColour;
}

void GridWidget::setCellFieldColour(const QColor& colour)
{
    cellFieldColour = colour;
}

qreal GridWidget::getCellGridMargin() const
{
    return cellGridMargin;
}

void GridWidget::setCellGridMargin(const qreal& margin)
{
    cellGridMargin = margin;
}

bool GridWidget::getDoEvolve() const
{
    return doEvolve;
}

void GridWidget::setDoEvolve(const bool& cmd)
{
    doEvolve = cmd;
}

void GridWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    paintUniverseBorder(painter);
    paintCellGrid(painter);
}

void GridWidget::mousePressEvent(QMouseEvent* event)
{
    int rowIdx = static_cast<int>(std::floor((event->y() - 0.75 * universeBorderThickness) / calcCellHeight()));
    int columnIdx = static_cast<int>(std::floor((event->x() - 0.75 * universeBorderThickness) / calcCellWidth()));
    grid[rowIdx][columnIdx] ^= 1;
    update();
}

void GridWidget::paintUniverseBorder(QPainter& painter)
{
    QRect universeBorder(0, 0, width(), height());
    painter.setBrush(QBrush(universeFieldColour));
    painter.fillRect(universeBorder, painter.brush());
    painter.setPen(QPen(universeBorderColour, universeBorderThickness));
    painter.drawRect(universeBorder);
}

void GridWidget::paintCellGrid(QPainter& painter)
{
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx)
        {
            if (grid[rowIdx][columnIdx] == 1)
            {
                qreal cellLeftIdx = 0.75 * universeBorderThickness + calcCellWidth() * columnIdx + cellGridMargin;
                qreal cellTopIdx = 0.75 * universeBorderThickness + calcCellHeight() * rowIdx + cellGridMargin;
                QRect cellField(cellLeftIdx, cellTopIdx, calcCellWidth() - cellGridMargin, calcCellHeight() - cellGridMargin);
                painter.setBrush(QBrush(cellFieldColour));
                painter.fillRect(cellField, painter.brush());
            }
        }
    }
}

void GridWidget::deleteGrid()
{
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        delete[] grid[rowIdx];
    }
    delete[] grid;
}

void GridWidget::createGrid(cellPopulationOption pattern)
{
    lastDefaultPattern = pattern;

    if (pattern == Empty)
    {
        createEmptyGrid();
    }
    else if (pattern == Filled)
    {
        createFilledGrid();
    }
    else if (pattern == Chequered)
    {
        createChequeredGrid();
    }
    else if (pattern == Random)
    {
        createRandomGrid();
    }
}

void GridWidget::createEmptyGrid()
{
    grid = new int*[rowCount];
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        grid[rowIdx] = new int[columnCount];
        std::fill(grid[rowIdx], grid[rowIdx] + columnCount, 0);
    }
}

void GridWidget::createFilledGrid()
{
    grid = new int*[rowCount];
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        grid[rowIdx] = new int[columnCount];
        std::fill(grid[rowIdx], grid[rowIdx] + columnCount, 1);
    }
}

void GridWidget::createChequeredGrid()
{
    grid = new int*[rowCount];
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        grid[rowIdx] = new int[columnCount];
        for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx)
        {
            grid[rowIdx][columnIdx] = ((rowIdx + columnIdx) & 1) ? 0 : 1;
        }
    }
}

void GridWidget::createRandomGrid()
{
    grid = new int*[rowCount];
    for (int rowIdx = 0; rowIdx < rowCount; ++rowIdx)
    {
        grid[rowIdx] = new int[columnCount];
        for (int columnIdx = 0; columnIdx < columnCount; ++columnIdx)
        {
            grid[rowIdx][columnIdx] = randomCellStateGenerator();
        }
    }
}

int GridWidget::randomCellStateGenerator()
{
    int randNum = randDistribution(randNumGenerator);
    return (randNum <= 5) ? 0 : 1;
}

void GridWidget::setTimer()
{
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer, SIGNAL(timeout()), this, SLOT(evolveOnce()));
}

void GridWidget::evolveContinuous()
{
    timer->start();
    emit universeSizeAdjustable(false);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, true);
}

void GridWidget::stopEvolve()
{
    timer->stop();
    emit universeSizeAdjustable(true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void GridWidget::setTransparency()
{
    universeBorderColour.setAlpha(255);
    universeFieldColour.setAlpha(255);
    cellFieldColour.setAlpha(255);
}

qreal GridWidget::calcUniverseWidth()
{
    return width() - 1.5 * universeBorderThickness;
}

qreal GridWidget::calcUniverseHeight()
{
    return height() - 1.5 * universeBorderThickness;
}

qreal GridWidget::calcCellWidth()
{
    return calcUniverseWidth() / columnCount;
}

qreal GridWidget::calcCellHeight()
{
    return calcUniverseHeight() / rowCount;
}

void GridWidget::evolveOnce()
{
    evolveNextGeneration(grid, rowCount, columnCount);
    emit generationCountChanged(++generationCount);
    update();
}

void GridWidget::toggleEvolveDecision()
{
    doEvolve = !doEvolve;

    if (doEvolve)
    {
        evolveContinuous();
    }
    else
    {
        stopEvolve();
    }
}
