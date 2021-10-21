#include "LineChartWidget.h"
#include <iostream>
using namespace std;


LineChartWidget::LineChartWidget()
{
    InItLineChart();
    InItRangeXAxisControlTwoSpinBox();
//    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::lowerValueChanged, this, &LineChartWidget::SetXAxisMin);
}


LineChartWidget::~LineChartWidget()
{


}

void LineChartWidget::InItLineChart()
{
    pLineChart     = new QChart;
    pLineChartView = new QChartView(pLineChart);
    pLineSeriesAndIDList = new QList<LEGEND_DATA_INFO*>;
    pLineChart->legend()->setVisible(false);    //隐藏图例
    pLineChart->setBackgroundVisible(false);
    SetXAxisStyle();
    SetYAxisStyle();
    pVLayoutLineChart = new QVBoxLayout();
    pVLayoutLineChart->addWidget(pLineChartView);
}

void LineChartWidget::InItRangeXAxisControlTwoSpinBox()
{
    pRangeXAxisControlTwoSpinBox = new RangeSlider(Qt::Horizontal,RangeSlider::Option::DoubleHandles, nullptr);
    pVLayoutLineChart->addWidget(pRangeXAxisControlTwoSpinBox);
    pRangeXAxisControlTwoSpinBox->SetRange(0, 100);
    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::lowerValueChanged, this, &LineChartWidget::SetLowerXAxis);
    connect(pRangeXAxisControlTwoSpinBox, &RangeSlider::upperValueChanged, this, &LineChartWidget::SetUpperXAxis);
}

void LineChartWidget::SetXAxisStyle()
{
    XaxisStyle     = new QDateTimeAxis;
    XaxisStyle->setRange
    (
        QDateTime::fromString("00:00","mm:ss"),
        QDateTime::fromString("00:20","mm:ss")
    );
    XaxisRange = 19;
    XAxisAdaptive(QDateTime::fromString("00:00","mm:ss").toMSecsSinceEpoch());
    XaxisStyle ->setLinePenColor(QColor(54,105,115));       //坐标轴颜色
//    XaxisStyle ->setLabelsColor(QColor(49,52,59));          //字体颜色
    XaxisStyle ->setLabelsColor(QColor(255,255,255));          //字体颜色
//    XaxisStyle ->setLabelsVisible(false);                 //不显示x轴刻度
    XaxisStyle->setFormat("mm:ss");
    XaxisStyle ->setGridLineVisible(false);//网格
    pLineChart->addAxis(XaxisStyle, Qt::AlignBottom);
}

void LineChartWidget::SetYAxisStyle()
{
    YaxisStyle     = new QValueAxis;
    YaxisStyle ->setRange(0,30);
    YaxisStyle ->setLabelsColor(QColor(255,255,255));
    YaxisStyle ->setLinePenColor(QColor(54,105,115));
    YaxisStyle ->setLabelFormat("%d");
    YaxisStyle ->setGridLineVisible(true);
    YaxisStyle ->setGridLineColor(QColor(255,255,255,7));
    YaxisStyle ->setTickCount(16);
    YaxisStyle ->setMinorTickCount(0);
    pLineChart->addAxis(YaxisStyle, Qt::AlignLeft);//居左
}

LineChartWidget::LEGEND_DATA_INFO* LineChartWidget::FindDataID(QString Refer)
{
    if(nullptr != pLineSeriesAndIDList)
        foreach(LEGEND_DATA_INFO *i, *pLineSeriesAndIDList)
        if(i->DataID == Refer)
            return i;
    return nullptr;
}

void * LineChartWidget::DataPointToLineSeries(QLineSeries* pLineSeries,const QList<DATA_POINT_t>* inputPointList)
{
    foreach(DATA_POINT_t DATA_POINT , *inputPointList)
        pLineSeries->append(QPointF(DATA_POINT.timeStamp, DATA_POINT.value));
}

void LineChartWidget::AddLineSeriesInLineSeriesAndIDList(QString LegendID, QString DataID, QList<DATA_POINT_t>* DataPointList)
{
    QLineSeries *pLineSeries = new QLineSeries();
    DataPointToLineSeries(pLineSeries, DataPointList);
    LEGEND_DATA_INFO* pLineSeriesIDList = new LEGEND_DATA_INFO(LegendID, DataID, pLineSeries);
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

void LineChartWidget::AddInpLineChartAll()
{

    foreach(LEGEND_DATA_INFO* i , *pLineSeriesAndIDList)
    {
        pLineChart->addSeries(i->pLineSeriesList);
        pLineChart->setAxisX(XaxisStyle, i->pLineSeriesList);
        pLineChart->setAxisY(YaxisStyle, i->pLineSeriesList);
    }
}

void LineChartWidget::XAxisAdaptive(const qint64 &newMaxTime)
{
    QDateTime newMaxTimePoint;
    newMaxTimePoint.setMSecsSinceEpoch(newMaxTime);
    QDateTime XAxisMaxTime = QDateTime(XaxisStyle->max());
    if (newMaxTimePoint >= XAxisMaxTime)
    {
        XaxisStyle->setMax(newMaxTimePoint);
        SetXAxisMin();
    }
}

void LineChartWidget::SetXAxisMin()
{
    XaxisStyle->setMin(XaxisStyle->max().addSecs(-XaxisRange));
}

void LineChartWidget::SetXaxisRange(int rangInt)
{
    XaxisRange = rangInt;
    qDebug() << XaxisRange;
    SetXAxisMin();
}

void LineChartWidget::SetLowerXAxis(int percent)
{
    double a = percent;
    a = -(a / 100);
    if(100 != percent)
    {
        XaxisStyle->setMin(XaxisStyle->max());
    }
    qDebug() << a;
//    qDebug() << percent;
}

void LineChartWidget::SetUpperXAxis(int percent)
{
    if(100 != percent)
    {

    }
}









