#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mycharttest.h"
#include "LineChartWidget.h"
#include "RangeSlider.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void DrawLine();
    void setRange();

private:
    QTimer *timer;
    int b;
    QDateTime dateTime;
    LineChartWidget bs;
    QList<DATA_INFO_t> testDataINFOList;
    QList<DATA_POINT_t> testDataList;
    DATA_POINT_t testData;
    DATA_INFO_t testDataINFO;
    LEGEND_INFO_t testLegend;
    QDateTime a;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
