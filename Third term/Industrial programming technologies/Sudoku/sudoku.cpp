#include <vector>
#include <cstdlib>
#include <ctime>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
#include "sudoku.h"
#include "./ui_sudoku.h"

using namespace std;
using namespace std::chrono;

const int N = 9;

Sudoku::Sudoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Sudoku) {
    ui->setupUi(this);
    timer = new QTimer(this);
    grid = vector<vector<CellData>>(N, vector<CellData>(N, {0, false, {false}}));
    generateEmptyField();

    connect(ui->pushButton_restart, &QPushButton::clicked, this, &Sudoku::resetSudoku);
    connect(ui->pushButton_check, &QPushButton::clicked, this, &Sudoku::checkSolution);
    connect(ui->spinBox_mainNumber, &QSpinBox::textChanged, this, &Sudoku::updateFieldData);
}

Sudoku::~Sudoku() {
    delete ui;
}

bool isSafe(vector<vector<CellData>>& grid, int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x].mainNumber == num || grid[x][col].mainNumber == num)
            return false;
    }
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol].mainNumber == num)
                return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<CellData>>& grid, int row, int col) {
    if (row == N - 1 && col == N)
        return true;
    if (col == N) {
        row++;
        col = 0;
    }
    if (grid[row][col].isGenerated)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col].mainNumber = num;
            grid[row][col].isGenerated = true;
            if (solveSudoku(grid, row, col + 1))
                return true;
            grid[row][col].mainNumber = 0;
            grid[row][col].isGenerated = false;
        }
    }
    return false;
}

void removeDigits(vector<vector<CellData>>& grid, int difficulty) {
    int removedCells = 0;
    switch (difficulty) {
    case 1: removedCells = 30; break;
    case 2: removedCells = 40; break;
    case 3: removedCells = 50; break;
    default: removedCells = 0;
    }

    srand(time(0));
    while (removedCells > 0) {
        int i = rand() % N;
        int j = rand() % N;
        if (grid[i][j].mainNumber != 0) {
            grid[i][j].mainNumber = 0;
            grid[i][j].isGenerated = false;
            removedCells--;
        }
    }
}

bool isSudokuSolved(const vector<vector<CellData>>& grid) {
    for (int row = 0; row < 9; ++row) {
        QVector<bool> seen(10, false);
        for (int col = 0; col < 9; ++col) {
            if (grid[row][col].mainNumber != 0) {
                if (seen[grid[row][col].mainNumber]) {
                    return false;
                }
                seen[grid[row][col].mainNumber] = true;
            } else {
                return false;
            }
        }
    }

    for (int col = 0; col < 9; ++col) {
        QVector<bool> seen(10, false);
        for (int row = 0; row < 9; ++row) {
            if (grid[row][col].mainNumber != 0) {
                if (seen[grid[row][col].mainNumber]) {
                    return false;
                }
                seen[grid[row][col].mainNumber] = true;
            } else {
                return false;
            }
        }
    }

    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            QVector<bool> seen(10, false);
            for (int row = startRow; row < startRow + 3; ++row) {
                for (int col = startCol; col < startCol + 3; ++col) {
                    if (grid[row][col].mainNumber != 0) {
                        if (seen[grid[row][col].mainNumber]) {
                            return false;
                        }
                        seen[grid[row][col].mainNumber] = true;
                    } else {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void Sudoku::resetSudoku() {
    grid = vector<vector<CellData>>(N, vector<CellData>(N, {0, false, {false}}));
    solveSudoku(grid, 0, 0);
    int difficulty = ui->spinBox_difficulty->value();
    removeDigits(grid, difficulty);
    updateFieldData();

    startTime = QTime::currentTime();

    if (timer) {
        timer->stop();
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Sudoku::updateTime);
    timer->start(1000);

    updateTime();
}

void Sudoku::generateEmptyField() {
    QGridLayout *layout = new QGridLayout(ui->field);
    int cellSize = 40;
    layout->setSpacing(0);

    for (int row = 0; row < N; ++row) {
        for (int col = 0; col < N; ++col) {
            CellLabel *cellLabel = new CellLabel();
            cellLabel->setFixedSize(cellSize, cellSize);
            cellLabel->setAlignment(Qt::AlignCenter);
            cellLabel->setStyleSheet("border: 1px solid black; font-size: 16px;");

            cellLabel->setCoordinates(row, col);

            connect(cellLabel, &CellLabel::clicked, this, &Sudoku::cellClicked);

            layout->addWidget(cellLabel, row, col);
        }
    }

    ui->field->setLayout(layout);
}

void Sudoku::updateFieldData() {
    QGridLayout *layout = qobject_cast<QGridLayout*>(ui->field->layout());
    if (layout) {
        for (int row = 0; row < N; ++row) {
            for (int col = 0; col < N; ++col) {
                QLabel *label = qobject_cast<QLabel*>(layout->itemAtPosition(row, col)->widget());
                if (label) {
                    if (grid[row][col].mainNumber != 0) {
                        if (grid[row][col].mainNumber == ui->spinBox_mainNumber->value()) {
                            label->setStyleSheet("border: 1px solid black; font-size: 16px; color: blue;");
                        } else {
                            label->setStyleSheet("border: 1px solid black; font-size: 16px;");
                        }
                        label->setText(QString::number(grid[row][col].mainNumber));
                    } else {
                        int lineCount = 0;
                        QString numbers = "";

                        for (int index = 0; index < 9; ++index) {
                            if (grid[row][col].draftNumbers[index]) {
                                if (lineCount == 3) {
                                    numbers += "\n";
                                    lineCount = 0;
                                }

                                numbers += QString::number(index+1);
                                lineCount += 1;
                            }
                        }
                        label->setStyleSheet("border: 1px solid black; font-size: 9px; color: red;");
                        label->setText(numbers);
                    }
                }
            }
        }
    }
}

void Sudoku::updateTime() {
    int elapsed = startTime.secsTo(QTime::currentTime());
    QTime displayTime(0, 0);
    displayTime = displayTime.addSecs(elapsed);
    ui->label_time->setText(displayTime.toString("hh:mm:ss"));
}

void Sudoku::cellClicked(int row, int col) {
    if (grid[row][col].isGenerated) return;

    if (ui->pushButton_draftMode->isChecked()) {
        grid[row][col].draftNumbers[ui->spinBox_mainNumber->value()-1] = true;
    } else {
        grid[row][col].mainNumber = ui->spinBox_mainNumber->value();
    }

    updateFieldData();
}

void Sudoku::checkSolution() {
    if (isSudokuSolved(grid)) {
        QMessageBox::information(this, "Victory", "Congratulations! You've solved the Sudoku!");
    } else {
        QMessageBox::warning(this, "Game Over", "The solution is incorrect. Try again.");
    }
}
