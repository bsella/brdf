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
    }
    
    template <typename Scalar>
    void BRDFReconstructionModelSmallStorage<Scalar>::init()
    {
        using BRDFRecType = BRDFReconstructorSmallStorage<Scalar>;
        const auto& brdfNames(BRDFReconstructionModel<Scalar>::brdfNames);
        RowVector<Scalar>& meanBRDF(BRDFReconstructionModel<Scalar>::meanBRDF);
        auto& reconstructor(BRDFReconstructionModel<Scalar>::brdfReconstructor);
        const Matrix<Scalar>& K_minus1(BRDFReconstructionModel<Scalar>::K_minus1);
        const Vector<Scalar>& X(BRDFReconstructionModel<Scalar>::X);
        const auto& dim(BRDFReconstructionModel<Scalar>::dim);
        const auto& brdfFolderPath(BRDFReconstructionModel<Scalar>::brdfFolderPath);
        int progress(0);
        
        uint num_brdfs = brdfNames.size();
        ProgressInterface::initRange(0, num_brdfs+1);
        ProgressInterface::progressChanged(progress);
        
        for (unsigned int i = 0; i < num_brdfs; ++i) {
            const std::string filePath = brdfFolderPath+"/"+brdfNames[i];
            brdf_filePaths.push_back(filePath);
            meanBRDF += MERLReader::read_brdf<Scalar>(filePath.c_str());
            ProgressInterface::progressChanged(++progress);
        }
        meanBRDF /= num_brdfs;
        
        reconstructor = std::unique_ptr<BRDFRecType>(new BRDFRecType(K_minus1, X, meanBRDF, dim, brdf_filePaths));
        ProgressInterface::progressChanged(++progress);
        for (unsigned int i(0); i < 5; ++i)
        {
            std::cout << "Reconstruction error for " << brdfNames[i] <<  " : " << reconstructor->reconstructionError(i) << std::endl;
        }
        std::cout << std::endl;
        
    }
}
