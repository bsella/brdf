#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QScrollBar>

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
        if(click)
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

    template <typename Scalar>
    void BRDFMapView<Scalar>::wheelEvent(QWheelEvent*e){
        static float current_scale = 1.f;
        if(e->delta()>0){
            if(zoom<30){
                scale(1.1,1.1);
                zoom++;
                current_scale*=1.1;
                scene->setFontSize(20/current_scale);
            }
        }
        else
            if(zoom>-7){
                scale(1/1.1,1/1.1);
                zoom--;
                current_scale/=1.1;
                scene->setFontSize(20/current_scale);
            }
    }
}
