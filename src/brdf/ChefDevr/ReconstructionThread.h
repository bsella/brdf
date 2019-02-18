#ifndef RECONSTRUCTIONTHREAD_H
#define RECONSTRUCTIONTHREAD_H

#include "ChefDevr/WaitingDisplay.h"

template <typename Scalar>
class RThread : public QThread
{
public:
    RThread(ChefDevr::BRDFReconstructed<Scalar>* &_brdf,
            const ChefDevr::BRDFReconstructionModel<Scalar>* _brdfModel,
            const QPointF& _p) :

            QThread(),
            brdf(_brdf),
            brdfModel(_brdfModel),
            p(_p){}

protected:
    void run() override{
        brdf = brdfModel->createBRDFFromLSCoord(p.x(), p.y());
    }
    ChefDevr::BRDFReconstructed<Scalar>* &brdf;
    const ChefDevr::BRDFReconstructionModel<Scalar>* brdfModel;
    const QPointF& p;
};

#endif //RECONSTRUCTIONTHREAD_H
