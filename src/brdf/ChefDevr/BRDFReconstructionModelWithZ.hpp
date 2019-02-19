#include "BRDFReconstructionModelWithZ.h"
#include "ParametrisationWithZ.h"
#include "Parametrisation.h"
#include "MERLReader.h"

namespace ChefDevr
{
    template <typename Scalar>
    BRDFReconstructionModelWithZ<Scalar>::BRDFReconstructionModelWithZ(
        std::string paramtrzFilePath,
        std::string brdfFolderPath):
        
        BRDFReconstructionModel<Scalar>(paramtrzFilePath, brdfFolderPath)
    {
    }
    
    template <typename Scalar>
    void BRDFReconstructionModelWithZ<Scalar>::init()
    {
        using BRDFRecType = BRDFReconstructorWithZ<Scalar>;
        const auto& brdfNames(BRDFReconstructionModel<Scalar>::brdfNames);
        auto& reconstructor(BRDFReconstructionModel<Scalar>::brdfReconstructor);
        auto& meanBRDF(BRDFReconstructionModel<Scalar>::meanBRDF);
        const auto& K_minus1(BRDFReconstructionModel<Scalar>::K_minus1);
        const auto& X(BRDFReconstructionModel<Scalar>::X);
        const auto& dim(BRDFReconstructionModel<Scalar>::dim);
        const auto& brdfFolderPath(BRDFReconstructionModel<Scalar>::brdfFolderPath);
        int progress(0);
        
        uint num_brdfs = brdfNames.size();
        ProgressInterface::initRange(0, num_brdfs+1);
        Z.resize(num_brdfs, MERLReader::num_coefficientsBRDF);
        ProgressInterface::progressChanged(progress);
        
        for (unsigned int i = 0; i < num_brdfs; ++i) {
            Z.row(i) = MERLReader::read_brdf<Scalar>((brdfFolderPath+"/"+brdfNames[i]).c_str());
            ProgressInterface::progressChanged(++progress);
        }
        centerMat<Scalar>(Z, meanBRDF);
        
        reconstructor = std::unique_ptr<BRDFRecType>(new BRDFRecType(Z, K_minus1, X, meanBRDF, dim));
        ProgressInterface::progressChanged(++progress);
        for (unsigned int i(0); i < 5; ++i)
        {
            std::cout << "Reconstruction error for " << brdfNames[i] <<  " : " << reconstructor->reconstructionError(i) << std::endl;
        }
        std::cout << std::endl;
    }
    
}
