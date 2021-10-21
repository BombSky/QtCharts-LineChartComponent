#ifndef DYNAMICSCROLLINGEFFECT_H
#define DYNAMICSCROLLINGEFFECT_H
#include <QtCharts>
//#include <lineseries>

class DynamicScrollingEffect
{
public:

    DynamicScrollingEffect();

    QChart *Chart;
    QLineSeries *lineseries;
    QDateTimeAxis *dataAxisX;
    QValueAxis *axisY;

};

#endif // DYNAMICSCROLLINGEFFECT_H
