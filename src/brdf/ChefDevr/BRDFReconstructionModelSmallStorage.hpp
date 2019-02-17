#include "BRDFReconstructionModelSmallStorage.h"
#include "ParametrisationSmallStorage.h"
#include "MERLReader.h"

namespace ChefDevr
{
    template <typename Scalar>
    BRDFReconstructionModelSmallStorage<Scalar>::BRDFReconstructionModelSmallStorage(
        std::string paramtrzFilePath,
        std::string brdfFolderPath):
        
        BRDFReconstructionModel<Scalar>(paramtrzFilePath, brdfFolderPath)
        {
            using BRDFRecType = BRDFReconstructorSmallStorage<Scalar>;
            const auto& brdfNames(BRDFReconstructionModel<Scalar>::brdfNames);
            const auto& meanBRDF(BRDFReconstructionModel<Scalar>::meanBRDF);
            auto& reconstructor(BRDFReconstructionModel<Scalar>::brdfReconstructor);
            const auto& K_minus1(BRDFReconstructionModel<Scalar>::K_minus1);
            const auto& X(BRDFReconstructionModel<Scalar>::X);
            const auto& dim(BRDFReconstructionModel<Scalar>::dim);
            
            uint num_brdfs = brdfNames.size();
            
            for (unsigned int i = 0; i < num_brdfs; ++i) {
                meanBRDF += read_brdf((brdfFolderPath+"/"+brdfNames[i]).c_str());
                // clamp negative values to zero
            }
            meanBRDF /= num_brdfs;
            
            reconstructor = std::unique_ptr<BRDFRecType>(new BRDFRecType(K_minus1, X, meanBRDF, dim));
        }
}
