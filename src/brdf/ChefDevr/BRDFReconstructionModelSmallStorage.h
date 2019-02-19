#ifndef __BRDF_RECONSTRUCTION_MODEL_SMALL_STORAGE__H
#define __BRDF_RECONSTRUCTION_MODEL_SMALL_STORAGE__H

#include "BRDFReconstructionModel.h"

namespace ChefDevr
{
    template <typename Scalar>
    class BRDFReconstructionModelSmallStorage : public BRDFReconstructionModel<Scalar>
    {
    public:
        BRDFReconstructionModelSmallStorage(std::string paramtrzFilePath, std::string brdfFolderPath);
        
        void init() override;
    private:
        /**
         * @brief the list of BRDF filePaths in the order in which they were read
         */
        std::vector<std::string> brdf_filePaths;
    };
}

#include "BRDFReconstructionModelSmallStorage.hpp"

#endif // __BRDF_RECONSTRUCTION_MODEL_SMALL_STORAGE__H
