#include "BRDFMapDisplay.h"
#include "BRDFMapPoint.h"
#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include <iostream>

namespace ChefDevr
{
    static QFont _font;
    BRDFMapScene::BRDFMapScene():QGraphicsScene(), _background(QPixmap("./images/map.bmp")){
        _font.setBold(true);
    }

    BRDFMapScene::~BRDFMapScene(){
        delete selected;
    }

    void BRDFMapScene::addPoint(const std::string& name, float x, float y){
        BRDFMapPoint *p = new BRDFMapPoint(name, Qt::red);
        p->setPos(x*512,y*512);
        addItem(p);
    }
    void BRDFMapScene::drawBackground (QPainter*p, const QRectF&){
        p->drawPixmap(-512,-512,1024,1024,_background);
    }
    void BRDFMapScene::drawForeground (QPainter*p, const QRectF&){
        for(const auto& i : items()){
            BRDFMapPoint* point= (BRDFMapPoint*)i;
            if(point==selected) continue;
            if(ctrlPressed || point == BRDFMapPoint::hover){
                p->setPen(QPen(Qt::white));
                p->setFont(_font);
                p->drawText(point->pos(), QString::fromStdString(point->name().substr(0,point->name().size()-7)));
                p->setPen(QPen(Qt::black));
            }
        }
    }
    void BRDFMapScene::keyPressEvent   (QKeyEvent*e){
        ctrlPressed= (e->modifiers() & Qt::ControlModifier);
        update();
    }
    void BRDFMapScene::keyReleaseEvent (QKeyEvent*e){
        ctrlPressed= (e->modifiers() & Qt::ControlModifier);
        update();
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

    static QPointF clickPos;
    static bool click, press;

    void BRDFMapView::mousePressEvent(QMouseEvent*e){
        clickPos= e->pos();
        press = click=true;
    }
    void BRDFMapView::mouseReleaseEvent(QMouseEvent*e){
        press=false;
        const QPointF tmp= mapToScene(e->pos())/512;
        if(click && tmp.x()>-1 && tmp.x()<1 && tmp.y()>-1 && tmp.y()<1)
            scene->setSelectedPoint(tmp.x(),tmp.y());
    }
    void BRDFMapView::mouseMoveEvent(QMouseEvent*e){
        if(press){
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + clickPos.x()-e->pos().x());
            verticalScrollBar()->setValue( verticalScrollBar()->value()    + clickPos.y()-e->pos().y());
            clickPos=e->pos();
        }
        click=false;
        QGraphicsView::mouseMoveEvent(e);
    }

} // namespace ChefDevr
