
#include <QPainter>
#include <QMouseEvent>
#include <QScrollBar>
#include <iostream>

namespace ChefDevr
{    
    template <typename Scalar>
    BRDFMapView<Scalar>::BRDFMapView(
        const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel,
        QWidget* parent):
        
        QGraphicsView(parent)
    {    
        scene = std::unique_ptr<BRDFMapScene>(new BRDFMapScene(4));
        setScene(scene.get());
        const auto& brdfNames(brdfModel->getBrdfNames());
        const auto& X(brdfModel->getX());
        for(int i=0; i < brdfNames.size(); i++)
            scene->addPoint(brdfNames[i], X[2*i], X[2*i+1]);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy  (Qt::ScrollBarAlwaysOff);
    }
    
    template <typename Scalar>
    BRDFMapView<Scalar>::~BRDFMapView(){}

    static QPointF clickPos;
    static bool click, press;

    template <typename Scalar>
    void BRDFMapView<Scalar>::mousePressEvent(QMouseEvent*e){
        clickPos= e->pos();
        press = click=true;
    }
    
    template <typename Scalar>
    void BRDFMapView<Scalar>::mouseReleaseEvent(QMouseEvent*e){
        press=false;
        const QPointF tmp= mapToScene(e->pos())/512;
        if(click && tmp.x()>-1 && tmp.x()<1 && tmp.y()>-1 && tmp.y()<1)
            scene->setSelectedPoint(tmp.x(),tmp.y());
    }
    
    template <typename Scalar>
    void BRDFMapView<Scalar>::mouseMoveEvent(QMouseEvent*e){
        if(press){
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + clickPos.x()-e->pos().x());
            verticalScrollBar()->setValue( verticalScrollBar()->value()    + clickPos.y()-e->pos().y());
            clickPos=e->pos();
        }
        click=false;
        QGraphicsView::mouseMoveEvent(e);
    }
}
