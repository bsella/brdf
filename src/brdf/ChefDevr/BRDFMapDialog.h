#ifndef BRDFDIALOG_H
#define BRDFDIALOG_H

#include <QDialog>
#include "BRDFMapDisplay.h"
#include "BRDFReconstructionModel.h"
#include <memory> 

namespace ChefDevr{
    
    template <typename Scalar>
	class BRDFMapDialog : public QDialog{
		
	public:
		explicit BRDFMapDialog(
            const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel,
            QWidget* parent= nullptr);
        
		~BRDFMapDialog()override;
		static QPointF getBRDFPos(const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel);
	private:
		std::unique_ptr<BRDFMapView<Scalar>> view;
	};
}

#include "BRDFMapDialog.hpp"

#endif
