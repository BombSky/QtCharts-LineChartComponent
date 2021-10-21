#include "LineChartWidget.h"
#include <QString>

QStringList LineChartWidget::GetLegendIds() const
{
    QStringList LegendVessel;
    foreach(LEGEND_DATA_INFO *i , *pLineSeriesAndIDList)
        LegendVessel.append(i->LegendID);
    LegendVessel.removeDuplicates();
    return LegendVessel;
}

QStringList LineChartWidget::GetDataIds(const QString& strLegendId)
{
    return FindLegendList(strLegendId);
}

bool LineChartWidget::StartDraw()
{
    if(!m_pEcale)
    {
        qDebug() << "未初始化x轴类型";
        return false;       //未初始化X轴类型
    }
    if (AXIS_X_SCALE_WEEK == *m_pEcale)
        LineChartWidget::AddInpLineChartAll(pValueXaxisStyle);
    else
        LineChartWidget::AddInpLineChartAll(pXaxisStyle);
    return true;
}

void LineChartWidget::StopDraw()
{}

void LineChartWidget::AddLegend(const LEGEND_INFO_t &stLegend, const QList<DATA_INFO_t> &lstDataInfos)
{
    foreach(DATA_INFO_t DATA_INFO , lstDataInfos)
    {
        //替换DATA_INFO.id
        LEGEND_DATA_INFO* i = FindDataID(DATA_INFO.id);
        if(i != nullptr)
            pLineSeriesAndIDList->removeOne(i);
        //添加
        AddLineSeriesInLineSeriesAndIDList(stLegend.id, DATA_INFO.id, &DATA_INFO.values);
    }
}

void LineChartWidget::DeleteLegend(const QString& strLegendId)
{
    LEGEND_DATA_INFO* i = FindDataID(strLegendId);
    if(i != nullptr)
        pLineSeriesAndIDList->removeOne(i);
}

bool LineChartWidget::InitData(const QString& strLegendId, const QList<DATA_INFO_t>& lstDataInfos)
{
    pLineSeriesAndIDList->clear();
    foreach(DATA_INFO_t DATA_INFO , lstDataInfos)
        AddLineSeriesInLineSeriesAndIDList(strLegendId, DATA_INFO.id, &DATA_INFO.values);
    return true;
}

bool LineChartWidget::AppendData(const QString& strLegendId, const QString& strDataId, const QList<DATA_POINT_t>& lstDataValues)
{
    LEGEND_DATA_INFO* i = FindDataID(strDataId);
    if(i == nullptr)
        return false;
    QLineSeries *pLineSeries = i->pLineSeriesList;
    DataPointToLineSeries(pLineSeries, &lstDataValues);
    if (AXIS_X_SCALE_WEEK == *m_pEcale)
    {
        XAxisIntAdqptive(lstDataValues.begin()->timeStamp);
        return true;
    }
    XAxisQDateTimeAdaptive(lstDataValues.begin()->timeStamp);
    return true;
}
void LineChartWidget::DeleteData(const QString& strLegendId, const QString strDataId)
{}
void LineChartWidget::RefreshData(const QString& strLegendId, const QString& strDataId)
{}
void LineChartWidget::RefreshLegend(const QString& strLegendId)
{}
void LineChartWidget::RefreshAll()
{}
void LineChartWidget::HideData(const QString& strLegendId, const QString& strDataId)
{}
void LineChartWidget::HideLegend(const QString& strLegendId)
{}
void LineChartWidget::HideAll()
{}
void LineChartWidget::SetXAxisScale(const DataChart::AXIS_X_SCALE_e ecale)
{
    m_pEcale = &ecale;
    switch (ecale)
    {
    case AXIS_X_SCALE_MINUTE: *pTimeFormat = "hh:mm"; TimeStep = 60;    break;
    case AXIS_X_SCALE_HOUR:   *pTimeFormat = "dd:hh"; TimeStep = 3600;  break;
    case AXIS_X_SCALE_MONTH:  *pTimeFormat = "yy:MM"; TimeStep = 108000;break;
    case AXIS_X_SCALE_WEEK:   break;
    case AXIS_X_SCALE_SECS:   *pTimeFormat = "mm:ss"; TimeStep = 1;     break;
    }
    InItLineChart();
    InItRangeXAxisControlTwoSpinBox();
}
void LineChartWidget::SetInteractive(const bool bEnable)
{}
QImage LineChartWidget::SaveImage()
{}
void LineChartWidget::RestoreDefault()
{}
QString LineChartWidget::GetLastError()
{}
void LineChartWidget::SigLegendSelected(const QString strLegendId, const QString strDataId, const int nTimeStamp)
{}
