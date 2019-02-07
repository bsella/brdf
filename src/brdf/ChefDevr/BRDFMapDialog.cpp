#include "BRDFMapDialog.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include <iostream>

namespace ChefDevr{
	BRDFMapDialog::BRDFMapDialog(QWidget*parent):QDialog(parent){
		QVBoxLayout *vbl = new QVBoxLayout;
		QGraphicsView* mapview= new QGraphicsView;
		QDialogButtonBox* buttons= new QDialogButtonBox(this);
		buttons->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
		buttons->setWindowFlag(Qt::Widget);

		mapview->setFixedSize(512,512);
		mapview->setDragMode(QGraphicsView::DragMode::ScrollHandDrag);
		mapview->setInteractive(true);
		//Initialize Scene
		scene= new BRDFMapScene("");
		scene->addPoint("test",0,0);
		mapview->setScene(scene);

		vbl->setMargin(2);
		vbl->addWidget(mapview);
		vbl->addWidget(buttons);
		setLayout(vbl);

		connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
		connect(buttons,SIGNAL(rejected()),this,SLOT(reject()));
		setFixedSize(minimumSize());
	}

	BRDFMapDialog::~BRDFMapDialog(){
		delete scene;
	}

	QPointF BRDFMapDialog::getBRDFPos(){
		BRDFMapDialog diag;
		if(diag.exec() && diag.scene && diag.scene->selected)
			return diag.scene->selected->pos();
		return QPointF(2,2);
	}
}