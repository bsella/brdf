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
            RowVector<Scalar>& meanBRDF(BRDFReconstructionModel<Scalar>::meanBRDF);
            auto& reconstructor(BRDFReconstructionModel<Scalar>::brdfReconstructor);
            const Matrix<Scalar>& K_minus1(BRDFReconstructionModel<Scalar>::K_minus1);
            const Vector<Scalar>& X(BRDFReconstructionModel<Scalar>::X);
            const auto& dim(BRDFReconstructionModel<Scalar>::dim);
            
            uint num_brdfs = brdfNames.size();
            
            for (unsigned int i = 0; i < num_brdfs; ++i) {
                const std::string filePath = brdfFolderPath+"/"+brdfNames[i];
                brdf_filePaths.push_back(filePath);
                meanBRDF += MERLReader::read_brdf<Scalar>(filePath.c_str());
                // clamp negative values to zero
            }
            meanBRDF /= num_brdfs;
            
            reconstructor = std::unique_ptr<BRDFRecType>(new BRDFRecType(K_minus1, X, meanBRDF, dim, brdf_filePaths));
        }
}
