#include "LineChartWidget.h"
#include <iostream>
using namespace std;


LineChartWidget::LineChartWidget()
{
//    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::lowerValueChanged, this, &LineChartWidget::SetXAxisMin);
    pLineChart     = new QChart;
    pLineChartView = new QChartView(pLineChart);
    pTimeFormat    = new QString;
    pValueXaxisStyle = new QValueAxis;
    pXaxisStyle     = new QDateTimeAxis;
    pLineSeriesAndIDList = new QList<LEGEND_DATA_INFO*>;
    *pTimeFormat = "yyyy/MM/dd hh:mm:ss";
//    m_pEcale                              在SetXAxisScale唯一取外部对象地址
//    InItLineChart();                      在SetXAxisScale唯一调用
//    InItRangeXAxisControlTwoSpinBox();    在SetXAxisScale唯一调用
}


LineChartWidget::~LineChartWidget()
{


}

//在SetXAxisScale唯一调用
void LineChartWidget::InItLineChart()
{
    pLineChart->legend()->setVisible(false);    //隐藏图例
    pLineChart->setBackgroundVisible(false);

    if(AXIS_X_SCALE_INT == *m_pEcale)
    {
        SetXAxisIntType();
        qDebug() << "int轴模式";
    }
    else
    {
        SetXAxisQDateTimeType();
        qDebug() << "时间轴轴模式";
    }
    SetYAxisStyle();
    pVLayoutLineChart = new QVBoxLayout();
    pVLayoutLineChart->addWidget(pLineChartView);
}

//在SetXAxisScale唯一调用
void LineChartWidget::InItRangeXAxisControlTwoSpinBox()
{
    pRangeXAxisControlTwoSpinBox = new RangeSlider(Qt::Horizontal,RangeSlider::Option::DoubleHandles, nullptr);
    pVLayoutLineChart->addWidget(pRangeXAxisControlTwoSpinBox);
    pRangeXAxisControlTwoSpinBox->SetRange(0, 100);
    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::lowerValueChanged, this, &LineChartWidget::SetLowerXAxis);
    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::upperValueChanged, this, &LineChartWidget::SetUpperXAxis);
}

template<typename T>
void LineChartWidget::SetXAxisStyle(T t1)
{
    XaxisRange = 20;
//    SetXAxisQDateTimeType();
    t1 ->setLinePenColor(QColor(54,105,115));       //坐标轴颜色
//    t1 ->setLabelsColor(QColor(49,52,59));          //字体颜色
    t1 ->setLabelsColor(QColor(255,255,255));          //字体颜色
//    t1 ->setLabelsVisible(false);                 //不显示x轴刻度
    t1 ->setGridLineVisible(false);//网格
    pLineChart->addAxis(t1, Qt::AlignBottom);
}

//int轴模式，只须执行这一条
void LineChartWidget::SetXAxisIntType()
{
    SetXAxisStyle(pValueXaxisStyle);
    pValueXaxisStyle->setRange(0, 20);
    pValueXaxisStyle->setGridLineVisible(false);
    XAxisIntAdqptive(0);
}

void LineChartWidget::XAxisIntAdqptive(const qint64 &newMaxTime)
{
    if(newMaxTime >= pValueXaxisStyle->max())
    {
        pValueXaxisStyle->setMax(newMaxTime + 1);
        SetXAxisMin();
    }
}

//时间轴模式，只须执行这一条
void LineChartWidget::SetXAxisQDateTimeType()
{
    SetXAxisStyle(pXaxisStyle);
    pXaxisStyle->setFormat(*pTimeFormat);
}

void LineChartWidget::InitXAxisQDateTimeRange(const qint64 &startTime)
{
    displayLower = startTime;
    pXaxisStyle->setRange
    (
        QDateTime::fromMSecsSinceEpoch(displayLower),
        QDateTime::fromMSecsSinceEpoch(displayLower + (qint64)XaxisRange * (qint64)TimeStep * 1000)
    );
}

//时间轴
void LineChartWidget::XAxisQDateTimeAdaptive(const qint64 &newMaxTime)
{
    QDateTime newMaxTimePoint = QDateTime::fromMSecsSinceEpoch(newMaxTime);
    if (newMaxTimePoint >= pXaxisStyle->max())
    {
        pXaxisStyle->setMax(newMaxTimePoint.addSecs(1 * TimeStep));
        SetXAxisMin();
    }
    pYaxisStyle->setTickCount(XaxisRange-1);
//    pXaxisStyle->setTickCount(XaxisRange+1);
}

//两轴通用
void LineChartWidget::SetXAxisMin()
{
    //int轴模式
    if (AXIS_X_SCALE_INT == *m_pEcale)
        pValueXaxisStyle->setMin(pValueXaxisStyle->max()-XaxisRange);

    //时间轴模式
    else
        pXaxisStyle->setMin(pXaxisStyle->max().addSecs(-XaxisRange * TimeStep));
}

//两轴通用
void LineChartWidget::SetXaxisRange(int rangInt)
{
    XaxisRange = rangInt;
    SetXAxisMin();
}

void LineChartWidget::SetLowerXAxis(int percent)
{
//    double a = percent;
//    a = -(a / 100);
//    if(100 != percent)
//    {
//        XaxisStyle->setMin(XaxisStyle->max());
//    }
//    qDebug() << a;
//    SetXaxisRange(percent);
    qDebug() << percent;
}

void LineChartWidget::SetUpperXAxis(int percent)
{
    qDebug() << percent;
//    if(100 != percent)
//    {

//    }
}

//Y轴
void LineChartWidget::SetYAxisStyle()
{
    pYaxisStyle = new QValueAxis;

    pYaxisStyle ->setRange(0, 30);
//    pYaxisStyle->setMax(30);
//    pYaxisStyle->setMin(0);
//    yMax = 30;
//    yMin = 0;
    pYaxisStyle->setLabelsColor(QColor(255,255,255));
    pYaxisStyle->setLinePenColor(QColor(54,105,115));
    pYaxisStyle->setLabelFormat("%d");
    pYaxisStyle->setGridLineVisible(true);
    pYaxisStyle->setGridLineColor(QColor(255,255,255,7));
    pYaxisStyle->setTickCount(16);
    pYaxisStyle->setMinorTickCount(0);
//    pYaxisStyle->setMinorTickCount(0);
    pLineChart->addAxis(pYaxisStyle, Qt::AlignLeft);//居左
}

void LineChartWidget::SetYAxisAdaptive(DATA_POINT_t &newDATA_POINT)
{
//    if (YaxisMax < newDATA_POINT.value)
//    {
//        pYaxisStyle->setMax(newDATA_POINT.value);
//        YaxisMax = newDATA_POINT.value;
//    }
//    else if (YaxisMin > newDATA_POINT.value)
//    {
//        pYaxisStyle->setMin(newDATA_POINT.value);
//        YaxisMin = newDATA_POINT.value - 2;
//    }
//    pYaxisStyle = qobject_cast<QValueAxis *>(pLineChart->axes(Qt::Vertical).at(0));
//    pYaxisStyle->setMax(pYaxisStyle->max() * 1.01);
//    pYaxisStyle->setMin(pYaxisStyle->min() * 0.99);



}

LineChartWidget::LEGEND_DATA_INFO* LineChartWidget::FindDataID(QString Refer)
{
    if(nullptr != pLineSeriesAndIDList)
        foreach(LEGEND_DATA_INFO *i, *pLineSeriesAndIDList)
        if(i->DataID == Refer)
            return i;
    return nullptr;
}

{
    foreach(DATA_POINT_t DATA_POINT , *inputPointList)
    {
        pLineSeries->append(QPointF(DATA_POINT.timeStamp, DATA_POINT.value));
        SetYAxisAdaptive(DATA_POINT);
    }
}

void LineChartWidget::AddLineSeriesInLineSeriesAndIDList(QString LegendID, QString DataID, QList<DATA_POINT_t>* DataPointList)
{
    DataPointToLineSeries(pLineSeries, DataPointList);
    pLineSeriesAndIDList->append(pLineSeriesIDList);
}

QStringList LineChartWidget::FindLegendList(QString Refer)
{
    QStringList LegendVessel;
    foreach(LEGEND_DATA_INFO *i , *pLineSeriesAndIDList)
        if(Refer == i->LegendID)
            LegendVessel.append(i->LegendID);
    return LegendVessel;
}









