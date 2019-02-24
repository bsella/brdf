#ifndef BRDFDIALOG_H
#define BRDFDIALOG_H

#include <memory> 
#include <stdexcept>
#include <QDialog>
#include "BRDFMapDisplay.h"
#include "BRDFReconstructionModel.h"

namespace ChefDevr{
    
    template <typename Scalar>
	class BRDFMapDialog : public QDialog{
		
	public:
		explicit BRDFMapDialog(
            const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel,
            QWidget* parent= nullptr);
        
		~BRDFMapDialog()override;
		static QPointF getBRDFPos(const std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel);
        
        class BRDFMapDialogException : public std::runtime_error
        {
        public :
            explicit BRDFMapDialogException(const std::string& msg) : std::runtime_error(msg){}
        };
        
	private:
		std::unique_ptr<BRDFMapView<Scalar>> view;
	};
}

#include "BRDFMapDialog.hpp"

#endif
