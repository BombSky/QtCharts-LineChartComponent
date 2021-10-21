#ifndef MYCHARTTEST_H
#define MYCHARTTEST_H

#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QTime>
#include <QtCore/QDebug>
#include <QPen>
#include<QPainter>
#include<QtCharts\QLegendMarker>
#include<qmath.h>



#include <QtCharts>
#include <QTimer>
#include<QPointF>     //点类
#include<QList>         //列表

QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QValueAxis;                 //引入这两个类而免于引入整个头文件的方法

QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class MyChartTest : public QChart
{
    Q_OBJECT
public:
    MyChartTest(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    QChartView* m_chartView;   //因为布局时其它函数会访问这个画布，所以设为public
    virtual ~MyChartTest();
    QList<QPointF> setdata();    //预留这个函数作为一个设置图表数据的接口，将外界数据传给图表
public slots:
    //	void handleTimeout();
    //几个操作数据的槽函数
    void addSeries(QList<QPointF> &data);     //新增一条曲线
    void removeSeries();                            //移出一条曲线
//    void connectMarkers();                   //连接图线与图例
//    void disconnectMarkers();               //断开图线与图例
    void handleMarkerClicked();           //占击图例时的处理函数
protected:
    void timerEvent(QTimerEvent *event)Q_DECL_OVERRIDE;  //定时器触发事件，重构
private:
    QTimer m_timer;     //定时器指针

    QChart * m_chart;     //图表组件，可理解为画笔，用它画曲线
    QList<QLineSeries *> m_serieslist;   //曲线列表，splineseries为光滑曲线

    QLineSeries *m_series;     //曲线指针
    QStringList m_titles;             //标题
    QValueAxis *axisX;             //x坐标轴
    QValueAxis *axisY;             //y坐标轴

    qreal m_step;
    qreal m_x;
    qreal m_y;
};

#endif // MYCHARTTEST_H
