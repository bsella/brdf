#include "BRDFMapDisplay.h"
#include "BRDFMapPoint.h"
#include <QPainter>
#include <QMouseEvent>

#include <iostream>

namespace ChefDevr
{
    BRDFMapScene::BRDFMapScene():QGraphicsScene(){
        _background= QPixmap("./images/map.bmp");
        addPoint("test",0,0);
    }

    BRDFMapScene::~BRDFMapScene(){}

    void BRDFMapScene::addPoint(const std::string& name, float x, float y){
    	BRDFMapPoint *p = new BRDFMapPoint(name, Qt::red,false);
    	p->setPos(x,y);
    	addItem(p);
    }
    void BRDFMapScene::drawBackground (QPainter*p, const QRectF& rect){
        p->drawPixmap(-512,-512,1024,1024,_background);
    }
    void BRDFMapScene::drawForeground (QPainter*, const QRectF& rect){

    }
    // void BRDFMapScene::mousePressEvent   (QGraphicsSceneMouseEvent*e){
    //     QGraphicsScene::mousePressEvent(e);
    // }
    // void BRDFMapScene::mouseReleaseEvent (QGraphicsSceneMouseEvent*e){
    //     QGraphicsScene::mouseReleaseEvent(e);
    // }
    void BRDFMapScene::keyPressEvent   (QKeyEvent*){

    }
    void BRDFMapScene::keyReleaseEvent (QKeyEvent*){

    }
//##########################BRDFMapView########################################

    BRDFMapView::BRDFMapView(QWidget* parent):QGraphicsView(parent){
        scene= new BRDFMapScene();
        setScene(scene);
        setSceneRect(scene->sceneRect());
    }
    BRDFMapView::~BRDFMapView(){}

    static QPointF tmpPos;

    void BRDFMapView::mousePressEvent(QMouseEvent*e){
        tmpPos= e->pos()+sceneRect().topLeft();
    }
    void BRDFMapView::mouseReleaseEvent(QMouseEvent*e){
        QGraphicsView::mouseReleaseEvent(e);
    }
    void BRDFMapView::mouseMoveEvent(QMouseEvent*e){
        setSceneRect(QRectF(tmpPos-e->pos(),sceneRect().size()));
    }

} // namespace ChefDevr
