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
        qint64 timeStamp;				// 时间戳(横坐标);
		float value;				// 检测值(纵坐标);
	};

	struct LEGEND_INFO_t
	{
		QString id;					// 仪器ID;
		QString name;				// 仪器名称;
		QString from;				// 仪器位置;
		QString type;				// 仪器类型;
	};

	struct DATA_INFO_t
	{
        QString id;					// 数据ID;
		QString name;				// 规格名称;
		QColor foreColor;			// 数据图例前景色;
		float threshold;			// 超规阀值;
		QList<DATA_POINT_t> values; // 具体数据值;
	};
}
#endif 
