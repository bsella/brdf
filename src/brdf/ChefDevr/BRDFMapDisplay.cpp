#include "BRDFMapDisplay.h"
#include "BRDFMapPoint.h"
#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include <iostream>

namespace ChefDevr
{
    static QFont _font;
    BRDFMapScene::BRDFMapScene(float norm):QGraphicsScene(),norm(norm), _background(QPixmap("./images/map.bmp")){
        _font.setBold(true);
    }

    BRDFMapScene::~BRDFMapScene(){
        delete selected;
    }

    void BRDFMapScene::addPoint(const std::string& name, float x, float y){
        BRDFMapPoint *p = new BRDFMapPoint(name, Qt::red);
        p->setPos(x/norm*512,y/norm*512);
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
        selected->setPos(x/norm*512, y/norm*512);
    }

} // namespace ChefDevr
