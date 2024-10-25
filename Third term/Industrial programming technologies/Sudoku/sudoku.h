#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <QMouseEvent>

using namespace std;

struct CellData {
    int mainNumber;
    bool isGenerated;
    bool draftNumbers[9];
};

QT_BEGIN_NAMESPACE
namespace Ui { class Sudoku; }
QT_END_NAMESPACE

class Sudoku : public QMainWindow {
    Q_OBJECT

public:
    explicit Sudoku(QWidget *parent = nullptr);
    ~Sudoku();
    void updateFieldData();
    void generateEmptyField();
    void resetSudoku();
    void cellClicked(int row, int col);
    void checkSolution();

private slots:
    void updateTime();

private:
    Ui::Sudoku *ui;
    QTimer *timer;
    QTime startTime;
    vector<vector<CellData>> grid;
};

class CellLabel : public QLabel {
    Q_OBJECT

public:
    CellLabel(QWidget *parent = nullptr) : QLabel(parent) {}
    void setCoordinates(int r, int c) {
        row = r;
        col = c;
    }

signals:
    void clicked(int row, int col);

protected:
    void mousePressEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit clicked(row, col);
        }
        QLabel::mousePressEvent(event);
    }

private:
    int row, col;
};

#endif // SUDOKU_H
