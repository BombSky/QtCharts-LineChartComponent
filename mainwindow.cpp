#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//*******************************************************************
//    MyChartTest m_chart;
//    m_chart.setdata();
//    m_chart.m_chartView->setRenderHint(QPainter::Antialiasing);
//    QVBoxLayout *pVLayout = new QVBoxLayout(ui->widget);
//    pVLayout->addWidget(m_chart.m_chartView);
//*******************************************************************



//    QVBoxLayout *pVLayout = new QVBoxLayout(ui->widget);
//    pVLayout->addWidget(bs.pLineChartView);
    bs.SetXAxisScale(AXIS_X_SCALE_SECS);
    QString timeformat = "mm:ss";
//    dateTime = QDateTime::fromString("00:00", "hh:mm");

    testLegend.id = "Legend1";
    testData.timeStamp = dateTime.fromString("00:00", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 0;
    testData.value     = 0;
    testDataList.append(testData);
    testData.timeStamp = dateTime.fromString("00:01", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 1;
    testData.value     = 10;
    testDataList.append(testData);
    testData.timeStamp = dateTime.fromString("00:02", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 2;
    testData.value     = 5;
    testDataList.append(testData);
    testData.timeStamp = dateTime.fromString("00:03", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 3;
    testData.value     = 20;
    testDataList.append(testData);
    testDataINFO.values = testDataList;
    testDataINFO.id = "data1";
    testDataINFOList.append(testDataINFO);
//    testDataINFO.values = testData;

    testDataList.clear();
    testLegend.id = "Legend2";
    testData.timeStamp = dateTime.fromString("00:00", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 0;
    testData.value     = 20;
    testDataList.append(testData);
    testData.timeStamp = dateTime.fromString("00:01", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 1;
    testData.value     = 5;
    testDataList.append(testData);
    testData.timeStamp = dateTime.fromString("00:02", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 2;
    testData.value     = 10;
    testDataList.append(testData);
    testData.timeStamp = dateTime.fromString("00:03", timeformat).toMSecsSinceEpoch();
//    testData.timeStamp = 3;
    testData.value     = 0;
    testDataList.append(testData);
    testDataINFO.values = testDataList;
    testDataINFO.id = "data2";
    testDataINFOList.append(testDataINFO);

    bs.AddLegend(testLegend, testDataINFOList);
//    bs.AddInpLineChartAll();
    bs.pLineChartView->setRenderHint(QPainter::Antialiasing);


    timer = new QTimer;
    timer->start();
    timer->setInterval(1000);    //设置定时周期
    testDataList.clear();
    bs.StartDraw();
    connect(timer, SIGNAL(timeout()), this, SLOT(DrawLine()));

    a = QDateTime::fromString("00:04", timeformat);
    b = 4;

//    RangeSlider *rsH = new RangeSlider(Qt::Horizontal, RangeSlider::Option::DoubleHandles, nullptr);
//    pVLayout->addWidget(rsH);

//    ui->centralwidget->setLayout(bs.pVLayoutLineChart);
    ui->widget->setLayout(bs.pVLayoutLineChart);

//    bs.AddInpLineChartAll();
//    bs.pLineChartView->setRenderHint(QPainter::Antialiasing);
//    pVLayout->addWidget(bs.pLineChartView);


//    QDateTime dateTime2;
//    qint64 a = dateTime.toMSecsSinceEpoch();
//    qDebug() << dateTime2.fromMSecsSinceEpoch(a).toString() << dateTime.toString("hh:mm");
//    qDebug() << dateTime2.fromMSecsSinceEpoch(a).toString() << dateTime.toString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawLine()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    testDataList.clear();
    testData.timeStamp = a.toMSecsSinceEpoch();
//    testData.timeStamp = b;
    a = a.addSecs(1);
    b++;
    testData.value     = qrand() % 30;
    testDataList.append(testData);
    testDataINFO.values = testDataList;
    testDataINFO.id = "data2";
    testDataINFOList.append(testDataINFO);
    bs.AppendData("Legend2", "data2", testDataList);
//    qDebug() << a.toString();
}

void MainWindow::setRange()
{
}


