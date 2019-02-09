#include "BRDFMapPoint.h"

#include <QPainter>

namespace ChefDevr{
	BRDFMapPoint::BRDFMapPoint(const std::string& name, QColor clr): _name(name), _clr(clr){}
	BRDFMapPoint::~BRDFMapPoint(){}

	QRectF BRDFMapPoint::boundingRect()const{
		return QRectF(-5,-5,10,10);
	}

	void BRDFMapPoint::paint(QPainter* pnt, const QStyleOptionGraphicsItem*, QWidget*){
		QRectF r= boundingRect();
		pnt->setPen(QPen(Qt::black,3));
		pnt->drawLine(r.x(), r.y(), r.x()+r.width(), r.y()+r.height());
		pnt->drawLine(r.x()+r.width(), r.y(), r.x(), r.y()+r.height());
		pnt->setPen(QPen(_clr,2));
		pnt->drawLine(r.x(), r.y(), r.x()+r.width(), r.y()+r.height());
		pnt->drawLine(r.x()+r.width(), r.y(), r.x(), r.y()+r.height());
	}

	void BRDFMapPoint::hoverEnterEvent(QGraphicsSceneHoverEvent*){

	}
	void BRDFMapPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent*){

	}
}