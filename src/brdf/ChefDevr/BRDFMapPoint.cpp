#include "BRDFMapPoint.h"

#include <QPainter>
#include <QGraphicsScene>

namespace ChefDevr{
	BRDFMapPoint* BRDFMapPoint::hover = nullptr;
	BRDFMapPoint::BRDFMapPoint(): _name(""), _clr(Qt::white), visible(false){
		setFlags(QGraphicsItem::ItemIgnoresTransformations);
	}
	BRDFMapPoint::BRDFMapPoint(const std::string& name, QColor clr): _name(name), _clr(clr),visible(true){
		setFlags(QGraphicsItem::ItemIgnoresTransformations);
		setAcceptHoverEvents(true);
	}
	BRDFMapPoint::~BRDFMapPoint(){}

	QRectF BRDFMapPoint::boundingRect()const{
		return QRectF(-5,-5,10,10);
	}

	void BRDFMapPoint::paint(QPainter* pnt, const QStyleOptionGraphicsItem*, QWidget*){
		if(visible){
			QRectF r= boundingRect();
			pnt->setPen(QPen(Qt::black,3));
			pnt->drawLine(r.x(), r.y(), r.x()+r.width(), r.y()+r.height());
			pnt->drawLine(r.x()+r.width(), r.y(), r.x(), r.y()+r.height());
			pnt->setPen(QPen(_clr,2));
			pnt->drawLine(r.x(), r.y(), r.x()+r.width(), r.y()+r.height());
			pnt->drawLine(r.x()+r.width(), r.y(), r.x(), r.y()+r.height());
		}
	}

	void BRDFMapPoint::hoverEnterEvent(QGraphicsSceneHoverEvent*){
		hover=this;
		scene()->update();
	}
	void BRDFMapPoint::hoverLeaveEvent(QGraphicsSceneHoverEvent*){
		hover=nullptr;
		scene()->update();
	}
}