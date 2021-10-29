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
    QString timeformat = "yyyy/MM/dd hh:mm:ss";
    intTime64 = QDateTime::fromString("2021/10/22 00:00:00", timeformat).toMSecsSinceEpoch();
//    c = 604800;
    c = 1000;
    testLegend.id = "Legend1";
    testData.timeStamp = intTime64;
//    qDebug() << "inMain:" << QDateTime::fromMSecsSinceEpoch(intTime64);
//    testData.timeStamp = 0;
    testData.value     = 0;
    testDataList.append(testData);

    intTime64 += c;
    testData.timeStamp = intTime64;
//    qDebug() << "inMain:" << QDateTime::fromMSecsSinceEpoch(intTime64);
//    testData.timeStamp = 1;
    testData.value     = 10;
    testDataList.append(testData);


    intTime64 += c;
    testData.timeStamp = intTime64;
    intTime64 += c;
//    qDebug() << "inMain:" << QDateTime::fromMSecsSinceEpoch(intTime64);
//    testData.timeStamp = 2;
    testData.value     = 5;
    testDataList.append(testData);

    testData.timeStamp = intTime64;
    intTime64 += c;
//    qDebug() << "inMain:" << QDateTime::fromMSecsSinceEpoch(intTime64);
//    testData.timeStamp = 3;
    testData.value     = 20;
    testDataList.append(testData);

    testDataINFO.values = testDataList;
    testDataINFO.id = "data1";
    testDataINFOList.append(testDataINFO);
//    testDataINFO.values = testData;
    bs.InitData("data1", testDataINFOList);
    testDataINFOList.clear();
//==================================================================
    testDataList.clear();
    testLegend.id = "Legend2";

    intTime64 = QDateTime::fromString("2021/10/22 00:00:00", timeformat).toMSecsSinceEpoch();
    testData.timeStamp = intTime64;
    intTime64 += c;
//    testData.timeStamp = 0;
    testData.value     = 20;
    testDataList.append(testData);

    testData.timeStamp = intTime64;
    intTime64 += c;
//    testData.timeStamp = 1;
    testData.value     = 5;
    testDataList.append(testData);

    testData.timeStamp = intTime64;
    intTime64 += c;
//    testData.timeStamp = 2;
    testData.value     = 10;
    testDataList.append(testData);

    testData.timeStamp = intTime64;
    intTime64 += c;
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
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(timePushButton()));

    a = QDateTime::fromString("2021/10/22 00:00:00", timeformat);
    b = 4;

    ui->widget->setLayout(bs.pVLayoutLineChart);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DrawLine()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    testDataList.clear();
    intTime64 += c;
    testData.timeStamp = intTime64;
//    testData.timeStamp = b;
    b++;
    testData.value = qrand() % 30;
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



void MainWindow::timePushButton()
{
    if(ui->pushButton->text() == "STOP")
    {
        timer->stop();
        ui->pushButton->setText("START");
        bs.ChangeLineSeriesColor("data2",QColor(00,211,255));
    }
    else
    {
        timer->start();
        ui->pushButton->setText("STOP");
        bs.ChangeLineSeriesColor("data2",QColor(255,211,255));
    }
//    (ui->pushButton->text() == "STOP") ? timer->stop() : timer->start();
//    (ui->pushButton->text() == "STOP") ? ui->pushButton->setText("START") : timer->start();
}

