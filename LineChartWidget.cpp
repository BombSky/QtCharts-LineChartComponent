#include "LineChartWidget.h"
#include <iostream>
using namespace std;


LineChartWidget::LineChartWidget()
{
//    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::lowerValueChanged, this, &LineChartWidget::InItRangeXAxisControlTwoSpinBox);
    pLineChart     = new QChart;
    pLineChartView = new QChartView(pLineChart);
    pTimeFormat    = new QString;
    pValueXaxisStyle = new QValueAxis;
    pXaxisStyle     = new QDateTimeAxis;
    pLineSeriesAndIDList = new QList<LEGEND_DATA_INFO*>;
    *pTimeFormat = "yyyy/MM/dd hh:mm:ss";
//    m_pEcale                              在SetXAxisScale唯一取外部对象地址
//    InItLineChart();                      在SetXAxisScale唯一调用
//    InItRangeXAxisControlTwoSpinBox();    //在SetXAxisScale唯一调用
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
//        SetXAxisMin();
        pValueXaxisStyle->setMin(pValueXaxisStyle->max()-XaxisRange);
    }
}

//时间轴模式，只须执行这一条
void LineChartWidget::SetXAxisQDateTimeType()
{
    SetXAxisStyle(pXaxisStyle);
    pXaxisStyle->setFormat(*pTimeFormat);
}

void LineChartWidget::InitXAxisQDateTimeRange(const qint64 &startTime, const qint64 &lastTime)
{
    displayLower = startTime;
    lineMinTime = displayLower;
    SetXaxisRange(10);
    if(lastTime > (displayLower + XaxisRange * TimeStep * 1000))
        displayupper = lastTime;
    else
        lineMaxTime = displayLower + XaxisRange * TimeStep * 1000;
    displayupper = lineMaxTime;
    XAxisUpdate();
}

//时间轴
void LineChartWidget::XAxisQDateTimeAdaptive()
{
    pXaxisStyle->setMin(QDateTime::fromMSecsSinceEpoch(displayLower));
    pXaxisStyle->setMax(QDateTime::fromMSecsSinceEpoch(displayupper));
    SetYAxisAdaptive();
}

//两轴通用
void LineChartWidget::SetXaxisRange(int rangInt)
{
//    qDebug() << (displayupper - displayLower) / TimeStep / 1000;
    XaxisRange = rangInt;
//    SetXAxisMin();
}

void LineChartWidget::XAxisUpdate()
{
    qint64 a = lineMaxTime - displayupper;
    displayupper += a;
    displayLower += a;
    XAxisQDateTimeAdaptive();
}

void LineChartWidget::SetLowerXAxis(int percent)
{
    qint64 overallLength = lineMaxTime - lineMinTime;
    float percentF = ((float)percent / (float)100);
    qint64 b = (overallLength * percentF);
    b = b / TimeStep / 1000;
    qDebug() << b;
    displayLower = lineMinTime + b * 1000;
    XAxisQDateTimeAdaptive();
}

void LineChartWidget::SetUpperXAxis(int percent)
{
    qint64 overallLength = lineMaxTime - lineMinTime;
    qint64 b = overallLength * (((float)100 - (float)percent) / (float)100);
    b = b / TimeStep / 1000;
    qDebug() << b;
    displayupper = lineMaxTime - b * 1000;
    XAxisQDateTimeAdaptive();
}

//Y轴
void LineChartWidget::SetYAxisStyle()
{
    pYaxisStyle = new QValueAxis;
    SetYAxisAdaptive();
    pYaxisStyle->setLabelsColor(QColor(255,255,255));
    pYaxisStyle->setLinePenColor(QColor(54,105,115));
    pYaxisStyle->setLabelFormat("%d");
    pYaxisStyle->setGridLineVisible(true);
    pYaxisStyle->setGridLineColor(QColor(255,255,255,7));
    pYaxisStyle->setTickCount(16);
//    pYaxisStyle->setMinorTickCount(0);
    pLineChart->addAxis(pYaxisStyle, Qt::AlignLeft);//居左
}

void LineChartWidget::SetYAxisAdaptive()
{
    setLineMaxAndMin();
    pYaxisStyle ->setRange(m_minValue, m_maxValue);
}

LineChartWidget::LEGEND_DATA_INFO* LineChartWidget::FindDataID(QString Refer)
{
    if(nullptr != pLineSeriesAndIDList)
        foreach(LEGEND_DATA_INFO *i, *pLineSeriesAndIDList)
        if(i->DataID == Refer)
            return i;
    return nullptr;
}

void LineChartWidget::DataPointToLineSeries(QLineSeries* pLineSeries, QList<QPointF> *pThisLineSeriesPointList,const QList<DATA_POINT_t>* inputPointList)
{
    QPointF *newPointF;
    foreach(DATA_POINT_t DATA_POINT , *inputPointList)
    {
        newPointF = new QPointF(DATA_POINT.timeStamp, DATA_POINT.value);
        pLineSeries->append(*newPointF);
        pThisLineSeriesPointList->append(*newPointF);
    }
}

void LineChartWidget::AddLineSeriesInLineSeriesAndIDList(QString LegendID, QString DataID, QList<DATA_POINT_t>* DataPointList)
{
    QLineSeries *pLineSeries = new QLineSeries();
    QList<QPointF> *pLineSeriesPointList = new QList<QPointF>;
    DataPointToLineSeries(pLineSeries, pLineSeriesPointList, DataPointList);
    LEGEND_DATA_INFO* pLineSeriesIDList = new LEGEND_DATA_INFO(LegendID, DataID, pLineSeries, pLineSeriesPointList);
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

void LineChartWidget::setLineMaxAndMin()
{
    setLineMax();
    setLineMin();
}

void LineChartWidget::setLineMax()
{
    float maxValue = 0;
    QList<QPointF>::Iterator j;
    foreach (LEGEND_DATA_INFO *i, *pLineSeriesAndIDList)
    {
        j = i->pLineSeriesPointList->begin();
//        qDebug() << "1.displayupper: " << displayupper << " " << (qint64)j->x();
        while (i->pLineSeriesPointList->end() != j && displayupper != (qint64)j->x())
        {
//            qDebug() << "2.displayLower: " << displayLower << " " << (qint64)j->x();
            if (displayLower == (qint64)j->x())
            {
                while(i->pLineSeriesPointList->end() != j && displayupper != (qint64)j->x())
                {
//                    qDebug() << j->y();
                    if(maxValue < j->y())            maxValue = (qint64)j->y();
//                    if(minValue > j->y())       minValue = (qint64)j->y();
//                    qDebug() << displayupper << " " << (qint64)j->x();
//                    if (displayupper != (qint64)j->x())
                    ++j;
                }
                if (i->pLineSeriesPointList->end() == j) break;
//                qDebug() << j->y();
                if(maxValue < j->y())                 maxValue = (qint64)j->y();
//                if(minValue > j->y())            minValue = (qint64)j->y();
//                qDebug() << displayupper << " " << (qint64)j->x();
            }
            if (displayupper != (qint64)j->x()) ++j;
        }
    }
//    qDebug() << QDateTime::fromMSecsSinceEpoch(displayLower);
    m_maxValue = maxValue;
}
void LineChartWidget::setLineMin()
{
    float minValue = m_maxValue;
    QList<QPointF>::Iterator j;
    foreach (LEGEND_DATA_INFO *i, *pLineSeriesAndIDList)
    {
        j = i->pLineSeriesPointList->begin();
        while (i->pLineSeriesPointList->end() != j && displayupper != (qint64)j->x())
        {
            if (displayLower == (qint64)j->x())
            {
                while(i->pLineSeriesPointList->end() != j && displayupper != (qint64)j->x())
                {
                    if(minValue > j->y())       minValue = (qint64)j->y();
                    ++j;
                }
                if (i->pLineSeriesPointList->end() == j) break;
                if(minValue > j->y())            minValue = (qint64)j->y();
            }
            if (displayupper != (qint64)j->x()) ++j;
        }
    }
    m_minValue = minValue;
}




