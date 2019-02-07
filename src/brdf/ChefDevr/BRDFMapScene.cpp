#include "BRDFMapScene.h"


namespace ChefDevr
{
    BRDFMapScene::BRDFMapScene(const std::string& filePath, QWidget* parent):QGraphicsScene(){
    }

    BRDFMapScene::~BRDFMapScene(){
    }

    void BRDFMapScene::addPoint(const std::string& name, float x, float y){
    	BRDFMapPoint *p = new BRDFMapPoint(name, Qt::red,false);
    	p->setPos(x,y);
    	addItem(p);
    }
    void BRDFMapScene::drawBackground (QPainter*, const QRectF& rect){

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
} // namespace ChefDevr
