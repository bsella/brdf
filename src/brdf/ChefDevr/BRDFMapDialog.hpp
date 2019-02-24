#include <QVBoxLayout>
#include <QDialogButtonBox>

namespace ChefDevr{
    
    template <typename Scalar>
	BRDFMapDialog<Scalar>::BRDFMapDialog(
        const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel,
        QWidget* parent):
        
        QDialog(parent)
    {
		
        QVBoxLayout *vbl = new QVBoxLayout;
		QDialogButtonBox* buttons = new QDialogButtonBox(this);
		view = std::unique_ptr<BRDFMapView<Scalar>>(new BRDFMapView<Scalar>(brdfModel));
		buttons->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
		buttons->setWindowFlags(Qt::Widget);

		view->setFixedSize(512,512);
		view->setInteractive(true);
		
		vbl->setMargin(2);
		vbl->addWidget(view.get());
		vbl->addWidget(buttons);
		setLayout(vbl);

		connect(buttons,SIGNAL(accepted()),this,SLOT(accept()));
		connect(buttons,SIGNAL(rejected()),this,SLOT(reject()));
		setFixedSize(minimumSize());
	}

	template <typename Scalar>
	BRDFMapDialog<Scalar>::~BRDFMapDialog(){}

	template <typename Scalar>
	QPointF BRDFMapDialog<Scalar>::getBRDFPos(
        const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel)
    {
		BRDFMapDialog<Scalar> diag(brdfModel);
		//if(diag.exec() && diag.scene && diag.scene->selected)
		//	return diag.scene->selected->pos();
		if(diag.exec() && diag.view->scene->selected)
			return diag.view->scene->selected->pos()/512.f*4;
		throw BRDFMapDialogException("No point were selected");
	}
}
