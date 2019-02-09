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

    BRDFMapScene::~BRDFMapScene(){
        delete selected;
    }

    void BRDFMapScene::addPoint(const std::string& name, float x, float y){
    	BRDFMapPoint *p = new BRDFMapPoint(name, Qt::red);
    	p->setPos(x*512,y*512);
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
    void BRDFMapScene::setSelectedPoint(float x, float y){
        if(!selected){
            selected = new BRDFMapPoint("Selection", Qt::green);
            addItem(selected);
        }
            selected->setPos(x*512,y*512);
    }
//##########################BRDFMapView########################################

    BRDFMapView::BRDFMapView(QWidget* parent):QGraphicsView(parent){
        scene= new BRDFMapScene();
        setScene(scene);
    }
    BRDFMapView::~BRDFMapView(){}

    static QPointF tmpPos;
    static bool click;

    void BRDFMapView::mousePressEvent(QMouseEvent*e){
        tmpPos= e->pos()+sceneRect().topLeft();
        click=true;
    }
    void BRDFMapView::mouseReleaseEvent(QMouseEvent*e){
        QGraphicsView::mouseReleaseEvent(e);
        const QPointF tmp= mapToScene(e->pos())/512;
        if(click && tmp.x()>-1 && tmp.x()<1 && tmp.y()>-1 && tmp.y()<1)
            scene->setSelectedPoint(tmp.x(),tmp.y());
    }
    void BRDFMapView::mouseMoveEvent(QMouseEvent*e){
        setSceneRect(QRectF(tmpPos-e->pos(),sceneRect().size()));
        click=false;
    }

} // namespace ChefDevr
