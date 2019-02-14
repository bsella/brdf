#include "BRDFMapDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>

namespace ChefDevr{

    const BRDFReconstructionModel<double> BRDFMapDialog::brdfModel("data/paramtrzData","brdfs3000");

	BRDFMapDialog::BRDFMapDialog(QWidget*parent):QDialog(parent){
		QVBoxLayout *vbl = new QVBoxLayout;
		QDialogButtonBox* buttons= new QDialogButtonBox(this);
		view= new BRDFMapView(&brdfModel);
		buttons->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
		buttons->setWindowFlags(Qt::Widget);

		view->setFixedSize(512,512);
		view->setInteractive(true);
		
		vbl->setMargin(2);
		vbl->addWidget(view);
		vbl->addWidget(buttons);
		setLayout(vbl);

		connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
		connect(buttons,SIGNAL(rejected()),this,SLOT(reject()));
		setFixedSize(minimumSize());
	}

	BRDFMapDialog::~BRDFMapDialog(){
		delete view;
	}

	QPointF BRDFMapDialog::getBRDFPos(){
		BRDFMapDialog diag;
		//if(diag.exec() && diag.scene && diag.scene->selected)
		//	return diag.scene->selected->pos();
		diag.exec();
		return QPointF(2,2);
	}
}
