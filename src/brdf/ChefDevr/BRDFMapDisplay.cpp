#include "BRDFMapDisplay.h"
#include "BRDFMapPoint.h"
#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
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

    BRDFMapView::BRDFMapView(const BRDFReconstructionModel<double>* model, QWidget* parent):QGraphicsView(parent){
        scene= new BRDFMapScene;
        setScene(scene);
        for(int i=0; i<model->brdfNames.size();i++)
            scene->addPoint(model->brdfNames[i], model->X[2*i], model->X[2*i+1]);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    }
    BRDFMapView::~BRDFMapView(){}

    static QPointF tmpPos, clickPos;
    static bool click;

    void BRDFMapView::mousePressEvent(QMouseEvent*e){
        tmpPos= e->pos()+sceneRect().topLeft();
        clickPos= e->pos();
        click=true;
    }
    void BRDFMapView::mouseReleaseEvent(QMouseEvent*e){
        QGraphicsView::mouseReleaseEvent(e);
        const QPointF tmp= mapToScene(e->pos())/512;
        if(click && tmp.x()>-1 && tmp.x()<1 && tmp.y()>-1 && tmp.y()<1)
            scene->setSelectedPoint(tmp.x(),tmp.y());
    }
    void BRDFMapView::mouseMoveEvent(QMouseEvent*e){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() + clickPos.x()-e->pos().x());
        verticalScrollBar()->setValue( verticalScrollBar()->value()    + clickPos.y()-e->pos().y());
        clickPos=e->pos();
        click=false;
    }

} // namespace ChefDevr
