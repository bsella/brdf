#ifndef BRDFDIALOG_H
#define BRDFDIALOG_H

#include <QDialog>
#include "BRDFMapDisplay.h"
#include "BRDFReconstructionModel.h"

namespace ChefDevr{
	class BRDFMapDialog : public QDialog{
		Q_OBJECT
	public:
		explicit BRDFMapDialog(QWidget* parent= nullptr);
		~BRDFMapDialog()override;
		static QPointF getBRDFPos();
	private:
		BRDFMapView* view;
    	static const BRDFReconstructionModel<double> brdfModel;
	};
}

#endif