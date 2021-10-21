#include "DynamicScrollingEffect.h"

DynamicScrollingEffect::DynamicScrollingEffect()
{
    Chart               = new QChart;//图表
    lineseries          = new QLineSeries;//折线图数据系列
    dataAxisX           = new QDateTimeAxis;//时间类型轴(用作X轴)
    axisY   = new QValueAxis;//数值类型轴（用作Y轴）
    //或者从1970年0:0:0到此时此刻的总ms数
    qint64 current_time_total_ms = QDateTime::currentMSecsSinceEpoch();
    lineseries->append(current_time_total_ms, 10);
    lineseries->append(current_time_total_ms+1, 5);
    lineseries->append(current_time_total_ms + 2, 8);

    Chart->addSeries(lineseries);  // 将 series 添加至图表中


    dataAxisX->setFormat("mm:ss:zzz");//设置X轴数据的显示格式（格式串的写法请参考QDateTime::toString的帮助文档）
    Chart->setAxisX(dataAxisX, lineseries);

    Chart->setAxisY(axisY);

    //下面是自己设置X轴的显示范围，参数必须转换为QDateTime。本例用的是，把从19700101的到此刻的ms数字转为QDateTime格式
    //Chart.axisX()->setRange(QDateTime::fromMSecsSinceEpoch(x_min),
    //                       QDateTime::fromMSecsSinceEpoch(x_max));

}
