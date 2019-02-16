#ifndef __BRDFReconstructionModelWithZ__H
#define __BRDFReconstructionModelWithZ__H

#include "BRDFReconstructionModel.h"

namespace ChefDevr
{
    template <typename Scalar>
    class BRDFReconstructionModelWithZ : public BRDFReconstructionModel<Scalar>
    {
    public:
        BRDFReconstructionModelWithZ(std::string paramtrzFilePath, std::string brdfFolderPath);
        
    private:
        /**
        * @brief BRDF data matrix 
        * BRDFs are stored in row major
        */
        Matrix<Scalar> Z;
    };
}

#include "BRDFReconstructionModelWithZ.hpp"

#endif //__BRDFReconstructionModelWithZ__H
