#ifndef LINECHARTWIDGET_H
#define LINECHARTWIDGET_H

#include <QtCharts>
#include <QList>
#include <QPoint>
#include <QTime>
#include "IDataChart.h"
#include "RangeSlider.h"


class LineChartWidget : public IDataChart
{
//    Q_OBJECT
public:
    LineChartWidget();
    virtual ~LineChartWidget();

//IDataChart
    /**
    * @brief	返回图表中所有仪器ID;
    * @return	仪器ID列表;
    */
    virtual QStringList GetLegendIds() const;

    /**
    * @brief	根据输入的图例ID，返回该图例下的所有数据ID;
    * @param	strLegendId: [in]，图例ID;
    * @return	数据ID列表;
    */
    virtual QStringList GetDataIds(const QString& strLegendId);

    /**
    * @brief	图形控件启动绘制;
    * @return	true: 成功;
    *			false: 失败;
    */
    virtual bool StartDraw();

    /**
    * @brief	图形控件停止绘制;
    * @return	void;
    */
    virtual void StopDraw();

    /**
    * @brief	向图形控件添加图例;
    * @note		如果图形控件口已经存在相同图例ID，则替换原图例信息及数据;
    * @param	stLegend: [in]，该图例包含的基本信息;
    * @param	lstDataInfos: [in]，该图例的数据信息列表，包含基本信息及数据列表;
    * @return	void;
    */
    virtual void AddLegend(const LEGEND_INFO_t& stLegend, const QList<DATA_INFO_t>& lstDataInfos);

    /**
    * @brief	删除图形控件中的某图例;
    * @param	strLegendId: [in]，需要删除图例的ID;
    * @return	void;
    */
    virtual void DeleteLegend(const QString& strLegendId);

    /**
    * @brief	实始化图形控件中的图例数据;
    * @note		如果图形控件口已经存在相同图例ID，则替换原图例中已存在的数据;
    * @param	strLegendId: [in]，图例的ID;
    * @param	lstDataInfos: [in]，该图例的数据信息列表，包含基本信息及数据列表;
    * @return	true: 初始化成功;
    *			false: 初始化失败或图形控件中不存在该图例ID;
    */
    virtual bool InitData(const QString& strLegendId, const QList<DATA_INFO_t>& lstDataInfos);

    /**
    * @brief	向图形控件中的图例追加新数据;
    * @param	strLegendId: [in]，图例的ID;
    * @param	strDataId: [in]，数据的ID;
    * @param	lstDataValues: [in]，需要追加的新数据列表;
    * @return	true: 数据追加成功;
    *			false: 数据追加失败或图形控件中不存在该图例ID/数据ID;
    */
    virtual bool AppendData(const QString& strLegendId, const QString& strDataId, const QList<DATA_POINT_t>& lstDataValues);

    /**
    * @brief	移除图形控件中的数据;
    * @param	strLegendId: [in]，需要移除图例的ID;
    * @param	strDataId: [in]，需要移除数据的ID;
    * @return	void;
    */
    virtual void DeleteData(const QString& strLegendId, const QString strDataId);

    /**
    * @brief	刷新图形控件某数据;
    * @param	strLegendId: [in]，需要刷新图例的ID;
    * @param	strDataId: [in]，需要刷新数据的ID;
    * @return	void;
    */
    virtual void RefreshData(const QString& strLegendId, const QString& strDataId);

    /**
    * @brief	刷新图形控件某图例;
    * @param	strLegendId: [in]，需要刷新图例的ID;
    * @return	void;
    */
    virtual void RefreshLegend(const QString& strLegendId);

    /**
    * @brief	刷新图形控件的所有图例及数据;
    * @return	void;
    */
    virtual void RefreshAll();

    /**
    * @brief	隐藏图形控件某数据;
    * @param	strLegendId: [in]，需要隐藏图例的ID;
    * @param	strDataId: [in]，需要隐藏数据的ID;
    * @return	void;
    */
    virtual void HideData(const QString& strLegendId, const QString& strDataId);

    /**
    * @brief	隐藏图形控件某图例;
    * @param	strLegendId: [in]，需要隐藏图例的ID;
    * @return	void;
    */
    virtual void HideLegend(const QString& strLegendId);

    /**
    * @brief	隐藏图形控件的所有图例及数据;
    * @return	void;
    */
    virtual void HideAll();

    /**
    * @brief	设置图形控件横坐标的最小刻度值;
    * @param	eScale: [in]，最小刻度值的枚举值;
    * @return	void;
    */
    virtual void SetXAxisScale(const DataChart::AXIS_X_SCALE_e eScale);

    /**
    * @brief	设置图形控件是否可以交互;
    * @note		设置为false，鼠标不触发图形控件的任何显示数据，十字刻度线及改变显示范围等交互功能;设置为true，则启用所有交互功能;
    * @param	bEnable: [in]，交互使能值;
    * @return	void;
    */
    virtual void SetInteractive(const bool bEnable);

    /**
    * @brief	将图形控件的当前显示的界面保存为图像;
    * @return	返回保存后的QImage变量;
    */
    virtual QImage SaveImage();

    /**
    * @brief	将图像控件的所有设置恢复为默认设置;
    * @note		横坐标的最小刻度设置为默认值，横坐标左右滑动变更为最大范围;
    * @return	void;
    */
    virtual void RestoreDefault();

    /**
    * @brief	获取图像控件最后一次出现的错误信息;
    * @return	错误信息字符串;
    */
    virtual QString GetLastError();

signals:
    /**
    * @brief	图形控件中某图例/某数据被选中的触发此信号;
    * @param	strLegendId: [out]，被选中的图例ID;
    * @param	strDataId: [out]，被选中的数据ID;
    * @param	nTimeStamp: [out]，被选中的数据的时间戳;
    * @return	void;
    */
    void SigLegendSelected(const QString strLegendId, const QString strDataId, const int nTimeStamp);

public:
    QChart* pLineChart = nullptr;     //图表组件，可理解为画笔，用它画曲线
    QChartView* pLineChartView = nullptr;

    QValueAxis *pYaxisStyle = nullptr;             //y坐标轴
    QValueAxis *pValueXaxisStyle = nullptr;          //int类型轴(用作X轴)
    QDateTimeAxis *pXaxisStyle = nullptr;          //时间类型轴(用作X轴)
    int XaxisRange;
    int TimeStep;
    QVBoxLayout *pVLayoutLineChart = nullptr;
    RangeSlider *pRangeXAxisControlTwoSpinBox = nullptr;
    QString *pTimeFormat;
    const AXIS_X_SCALE_e *m_pEcale = nullptr;

    struct LEGEND_DATA_INFO
    {
        QString LegendID;					// 仪器ID;    会有很多重复的仪器ID
        QString DataID;                     // ID;
        QLineSeries *pLineSeriesList;
        LEGEND_DATA_INFO
            (QString  LegendID , QString DataID , QLineSeries *pLineSeriesList):
             LegendID(LegendID), DataID (DataID), pLineSeriesList(pLineSeriesList){}
    };
    QList<LEGEND_DATA_INFO*> *pLineSeriesAndIDList;
    template<typename T>void AddInpLineChartAll(T XAxis);
    void SetXaxisRange(int rangInt);

private:
    void InItLineChart();                     //初始化参数
    void InItRangeXAxisControlTwoSpinBox();

    template<typename T>void SetXAxisStyle(T t1);

    void SetXAxisIntType();
    void XAxisIntAdqptive(const qint64 &newMaxTime);

    void SetXAxisQDateTimeType();
    void XAxisQDateTimeAdaptive(const qint64 &newMaxTime);

    void SetXAxisMin();
    void SetYAxisStyle();
    LEGEND_DATA_INFO *FindDataID(QString Refer);
    QStringList FindLegendList(QString Refer);
    void DataPointToLineSeries(QLineSeries* pLineSeries,const QList<DATA_POINT_t>* inputPointList);
    void AddLineSeriesInLineSeriesAndIDList(QString LegendID, QString DataID, QList<DATA_POINT_t>* DataPointList);

public slots:
    void SetLowerXAxis(int percent);
    void SetUpperXAxis(int percent);
};

template<typename T>
void LineChartWidget::AddInpLineChartAll(T XAxis)
{
    foreach(LEGEND_DATA_INFO* i , *pLineSeriesAndIDList)
    {
        pLineChart->addSeries(i->pLineSeriesList);
        i->pLineSeriesList->attachAxis(XAxis);
        i->pLineSeriesList->attachAxis(pYaxisStyle);
    }
}

#endif // LINECHARTWIDGET_H
//双缓冲
//boost
