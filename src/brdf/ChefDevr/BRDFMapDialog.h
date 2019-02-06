#ifndef BRDFDIALOG_H
#define BRDFDIALOG_H

#include <QDialog>
#include "BRDFMapScene.h"
#include "BRDFReconstructed.h"

namespace ChefDevr{
	class BRDFMapDialog : public QDialog{
		Q_OBJECT
	public:
		explicit BRDFMapDialog(QWidget* parent= nullptr);
		~BRDFMapDialog()override;
		static QPointF getBRDFPos();
	private:
		BRDFMapScene* scene=nullptr;
	};
}

#endif