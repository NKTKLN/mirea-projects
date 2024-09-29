#ifndef TABLES_H
#define TABLES_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Tables;
}
QT_END_NAMESPACE

class Tables : public QMainWindow
{
    Q_OBJECT

public:
    Tables(QWidget *parent = nullptr);
    ~Tables();

private slots:
    void setRowsClicked();
    void setRandomDataClicked();
    void minClicked();
    void avgClicked();
    void maxClicked();
    void tableCellChanged(int row, int collumn);
    void searchClicked();
    void sortClicked();

private:
    Ui::Tables *ui;
    QList<QString> dataList;
};
#endif // TABLES_H
