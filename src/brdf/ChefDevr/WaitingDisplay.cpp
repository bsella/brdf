#include "WaitingDisplay.h"
#include "waitingspinnerwidget.h"

#include <QLayout>
#include <QFormLayout>

namespace ChefDevr {

    WaitingDisplay::WaitingDisplay() :
            QDialog(0, Qt::FramelessWindowHint)
    {
        setAttribute(Qt::WA_TranslucentBackground);
        setParent(0);
        WaitingSpinnerWidget *spinner = new WaitingSpinnerWidget(this);

        spinner->setRoundness(70.0);
        spinner->setMinimumTrailOpacity(15.0);
        spinner->setTrailFadePercentage(70.0);
        spinner->setNumberOfLines(12);
        spinner->setLineLength(100);
        spinner->setLineWidth(50);
        spinner->setInnerRadius(100);
        spinner->setRevolutionsPerSecond(2);
        spinner->setColor(QColor(224, 100, 166));

        spinner->start(); // gets the show on the road!

        QLayout *layout = new QFormLayout();
        layout->addWidget(spinner);
        this->setLayout(layout);
    }
}


