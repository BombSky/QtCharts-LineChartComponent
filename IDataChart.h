#ifndef _IDATACHART_H_
#define _IDATACHART_H_

#pragma once

#include "QDataChartDef.h"

#include <QWidget>
using namespace DataChart;
class IDataChart : public QWidget
{
	Q_OBJECT
public:
	virtual ~IDataChart() = default;

	/**
	* @brief	����ͼ������������ID;
	* @return	����ID�б�;
	*/
	virtual QStringList GetLegendIds() const = 0;

	/**
	* @brief	���������ͼ��ID�����ظ�ͼ���µ���������ID;
	* @param	strLegendId: [in]��ͼ��ID;
	* @return	����ID�б�;
	*/
    virtual QStringList GetDataIds(const QString& strLegendId) = 0;	//		���������

	/**
	* @brief	ͼ�οؼ���������;
	* @return	true: �ɹ�;
	*			false: ʧ��;
	*/
	virtual bool StartDraw() = 0;

	/**
	* @brief	ͼ�οؼ�ֹͣ����;
	* @return	void;
	*/
	virtual void StopDraw() = 0;

	/**
	* @brief	��ͼ�οؼ����ͼ��;
	* @note		���ͼ�οؼ����Ѿ�������ͬͼ��ID�����滻ԭͼ����Ϣ������;
	* @param	stLegend: [in]����ͼ�������Ļ�����Ϣ;
	* @param	lstDataInfos: [in]����ͼ����������Ϣ�б�����������Ϣ�������б�;
	* @return	void;
	*/
	virtual void AddLegend(const LEGEND_INFO_t& stLegend, const QList<DATA_INFO_t>& lstDataInfos) = 0;

	/**
	* @brief	ɾ��ͼ�οؼ��е�ĳͼ��;
	* @param	strLegendId: [in]����Ҫɾ��ͼ����ID;
	* @return	void;
	*/
	virtual void DeleteLegend(const QString& strLegendId) = 0;

	/**
	* @brief	ʵʼ��ͼ�οؼ��е�ͼ������;
	* @note		���ͼ�οؼ����Ѿ�������ͬͼ��ID�����滻ԭͼ�����Ѵ��ڵ�����;
	* @param	strLegendId: [in]��ͼ����ID;
	* @param	lstDataInfos: [in]����ͼ����������Ϣ�б�����������Ϣ�������б�;
	* @return	true: ��ʼ���ɹ�;
	*			false: ��ʼ��ʧ�ܻ�ͼ�οؼ��в����ڸ�ͼ��ID;
	*/
	virtual bool InitData(const QString& strLegendId, const QList<DATA_INFO_t>& lstDataInfos) = 0;
    /**
    * @brief	ʵʼ��ͼ�οؼ��е�ͼ������;
    * @note		���ͼ�οؼ����Ѿ�������ͬͼ��ID�����滻ԭͼ�����Ѵ��ڵ�����;
    * @param	strLegendId: [in]��ͼ����ID;
    * @param	lstDataInfos: [in]����ͼ����������Ϣ�б�����������Ϣ�������б�;
    * @param	LineSeriesColor: [in]������Ҫˢ�µ���ɫ;
    * @return	true: ��ʼ���ɹ�;
    *			false: ��ʼ��ʧ�ܻ�ͼ�οؼ��в����ڸ�ͼ��ID;
    */
    virtual bool InitData(const QString& strLegendId, const QList<DATA_INFO_t>& lstDataInfos, const QColor &InItLineSeriesColor) = 0;

    /**
    * @brief	�޸�������ɫ;
    * @note		�������Ӧ��lineseries�滻ԭ������ɫ�����û���򷵻�false;
    * @param	strDataId: [in]����Ҫˢ�����ݵ�ID;
    * @param	LineSeriesColor: [in]������Ҫˢ�µ���ɫ;
    * @return	true: �޸ĳɹ�;
    *			false: �޸�ʧ��;
    */
    virtual bool ChangeLineSeriesColor(const QString& strDataId, const QColor &LineSeriesColor) = 0;

	/**
	* @brief	��ͼ�οؼ��е�ͼ��׷��������;
	* @param	strLegendId: [in]��ͼ����ID;
	* @param	strDataId: [in]�����ݵ�ID;
	* @param	lstDataValues: [in]����Ҫ׷�ӵ��������б�;
	* @return	true: ����׷�ӳɹ�;
	*			false: ����׷��ʧ�ܻ�ͼ�οؼ��в����ڸ�ͼ��ID/����ID;
	*/
	virtual bool AppendData(const QString& strLegendId, const QString& strDataId, const QList<DATA_POINT_t>& lstDataValues) = 0;

	/**
	* @brief	�Ƴ�ͼ�οؼ��е�����;
	* @param	strLegendId: [in]����Ҫ�Ƴ�ͼ����ID;
	* @param	strDataId: [in]����Ҫ�Ƴ����ݵ�ID;
	* @return	void;
	*/
	virtual void DeleteData(const QString& strLegendId, const QString strDataId) = 0;

	/**
	* @brief	ˢ��ͼ�οؼ�ĳ����;
	* @param	strLegendId: [in]����Ҫˢ��ͼ����ID;
	* @param	strDataId: [in]����Ҫˢ�����ݵ�ID;
	* @return	void;
	*/
	virtual void RefreshData(const QString& strLegendId, const QString& strDataId) = 0;

	/**
	* @brief	ˢ��ͼ�οؼ�ĳͼ��;
	* @param	strLegendId: [in]����Ҫˢ��ͼ����ID;
	* @return	void;
	*/
	virtual void RefreshLegend(const QString& strLegendId) = 0;

	/**
	* @brief	ˢ��ͼ�οؼ�������ͼ��������;
	* @return	void;
	*/
	virtual void RefreshAll() = 0;

	/**
	* @brief	����ͼ�οؼ�ĳ����;
	* @param	strLegendId: [in]����Ҫ����ͼ����ID;
	* @param	strDataId: [in]����Ҫ�������ݵ�ID;
	* @return	void;
	*/
	virtual void HideData(const QString& strLegendId, const QString& strDataId) = 0;

	/**
	* @brief	����ͼ�οؼ�ĳͼ��;
	* @param	strLegendId: [in]����Ҫ����ͼ����ID;
	* @return	void;
	*/
	virtual void HideLegend(const QString& strLegendId) = 0;

	/**
	* @brief	����ͼ�οؼ�������ͼ��������;
	* @return	void;
	*/
	virtual void HideAll() = 0;

	/**
	* @brief	����ͼ�οؼ����������С�̶�ֵ;
	* @param	eScale: [in]����С�̶�ֵ��ö��ֵ;
	* @return	void;
	*/
	virtual void SetXAxisScale(const DataChart::AXIS_X_SCALE_e eScale) = 0;

	/**
	* @brief	����ͼ�οؼ��Ƿ���Խ���;
	* @note		����Ϊfalse����겻����ͼ�οؼ����κ���ʾ���ݣ�ʮ�̶ֿ��߼��ı���ʾ��Χ�Ƚ�������;����Ϊtrue�����������н�������;
	* @param	bEnable: [in]������ʹ��ֵ;
	* @return	void;
	*/
	virtual void SetInteractive(const bool bEnable) = 0;

	/**
	* @brief	��ͼ�οؼ��ĵ�ǰ��ʾ�Ľ��汣��Ϊͼ��;
	* @return	���ر�����QImage����;
	*/
	virtual QImage SaveImage() = 0;

	/**
	* @brief	��ͼ��ؼ����������ûָ�ΪĬ������;
	* @note		���������С�̶�����ΪĬ��ֵ�����������һ������Ϊ���Χ;
	* @return	void;
	*/
	virtual void RestoreDefault() = 0;

	/**
	* @brief	��ȡͼ��ؼ����һ�γ��ֵĴ�����Ϣ;
	* @return	������Ϣ�ַ���;
	*/
	virtual QString GetLastError() = 0;

signals:
	/**
	* @brief	ͼ�οؼ���ĳͼ��/ĳ���ݱ�ѡ�еĴ������ź�;
	* @param	strLegendId: [out]����ѡ�е�ͼ��ID;
	* @param	strDataId: [out]����ѡ�е�����ID;
	* @param	nTimeStamp: [out]����ѡ�е����ݵ�ʱ���;
	* @return	void;
	*/
	void SigLegendSelected(const QString strLegendId, const QString strDataId, const int nTimeStamp);
};


#endif
