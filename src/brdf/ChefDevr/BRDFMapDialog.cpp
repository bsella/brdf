#include "BRDFMapDialog.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDialogButtonBox>

namespace ChefDevr{
	BRDFMapDialog::BRDFMapDialog(QWidget*parent):QDialog(parent){
		QVBoxLayout *vbl = new QVBoxLayout;
		QGraphicsView* mapview= new QGraphicsView;
		QDialogButtonBox* buttons= new QDialogButtonBox(this);
		buttons->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
		buttons->setWindowFlag(Qt::Widget);

		mapview->setFixedSize(512,512);

		//Initialize Scene
		//scene=
		//mapview->setScene(scene);

		vbl->setMargin(2);
		vbl->addWidget(mapview);
		vbl->addWidget(buttons);
		setLayout(vbl);

		connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
		connect(buttons,SIGNAL(rejected()),this,SLOT(reject()));
		setFixedSize(minimumSize());
	}

	BRDFMapDialog::~BRDFMapDialog(){}

	// static BRDFReconstructed* BRDFMapDialog::getBRDF(){
		// return nullptr;
	// }
}