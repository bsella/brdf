#ifndef BRDFMAPDISPLAY_H
#define BRDFMAPDISPLAY_H

/**
 * @file BRDFMapScene.h
 */

#include "BRDFMapPoint.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <string>

namespace ChefDevr
{
    /**
    * @brief Widget that allows choosing a BRDF by providing a latent space representation
    */
    class BRDFMapScene : public QGraphicsScene{
    public:
        explicit BRDFMapScene();
        ~BRDFMapScene () override;
    private:

        BRDFMapPoint* selected=nullptr;

        /**
        * @brief Background image of the BRDF space reduced
        * in a 2D image
        */
        QPixmap _background;

        /**
        * @brief Adds a point to the scene
        * 
        * @param name Name of the point
        * @param x x position of the point (between 0 and 1)
        * @param y y position of the point (between 0 and 1)
        */
        void addPoint(const std::string& name, float x, float y);

        /**
        * @brief Overriding the drawBackground function to
        * define how to draw the background on the scene
        * 
        * @param rect Rectangle in which the background
        * is drawn (depends on zoom and navigation). The
        * background is the BRDF space reduced in a 2D image
        */
        void drawBackground (QPainter*, const QRectF& rect) override;

        /**
        * @brief Overriding the drawForeground function to
        * define how to draw the foreground on the scene
        * 
        * @param rect Rectangle in which the foreground
        * is drawn (depends on zoom and navigation). The
        * foreground contains additional information like
        * isolines and the names of BRDFs
        */
        void drawForeground (QPainter*, const QRectF& rect) override;

        /**
        * @brief Handles the mousePress/Click event
        * @details Places a point on the scene
        */
        // void mousePressEvent   (QGraphicsSceneMouseEvent*) override;

        /**
        * @brief Handles the mouseRelease event
        * @details Confirms th click
        */
        // void mouseReleaseEvent (QGraphicsSceneMouseEvent*) override;

        /**
        * @brief Handles keypresses
        */
        void keyPressEvent   (QKeyEvent*) override;

        /**
        * @brief Confirms keypresses
        */
        void keyReleaseEvent (QKeyEvent*) override;
    };

    class BRDFMapView : public QGraphicsView{
    public:
        explicit BRDFMapView(QWidget* parent= nullptr);
        ~BRDFMapView();
    private:
        BRDFMapScene* scene=nullptr;
        void mousePressEvent  (QMouseEvent*);
        void mouseReleaseEvent(QMouseEvent*);
        void mouseMoveEvent   (QMouseEvent*);
    };
} // namespace ChefDevr

#endif // BRDFMAP_H
