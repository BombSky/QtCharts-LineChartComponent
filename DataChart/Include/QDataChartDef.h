#ifndef _QDATACHARTDEF_H_
#define _QDATACHARTDEF_H_

#pragma once

#include <QString>
#include <QColor>

namespace DataChart
{
	enum AXIS_X_SCALE_e
	{
		AXIS_X_SCALE_MINUTE,
		AXIS_X_SCALE_HOUR,
		AXIS_X_SCALE_WEEK,
		AXIS_X_SCALE_MONTH
	};

	struct DATA_POINT_t
	{	
        qint64 timeStamp;				// ʱ���(������);
		float value;				// ���ֵ(������);
	};

	struct LEGEND_INFO_t
	{
		QString id;					// ����ID;
		QString name;				// ��������;
		QString from;				// ����λ��;
		QString type;				// ��������;
	};

	struct DATA_INFO_t
	{
        QString id;					// ����ID;
		QString name;				// �������;
		QColor foreColor;			// ����ͼ��ǰ��ɫ;
		float threshold;			// ���淧ֵ;
		QList<DATA_POINT_t> values; // ��������ֵ;
	};
}
#endif 
