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
        using BRDFRecType = BRDFReconstructorWithZ<Scalar, float>;
        const auto& brdfNames(BRDFReconstructionModel<Scalar>::brdfNames);
        auto& reconstructor(BRDFReconstructionModel<Scalar>::brdfReconstructor);
        auto& meanBRDF(BRDFReconstructionModel<Scalar>::meanBRDF);
        const auto& K_minus1(BRDFReconstructionModel<Scalar>::K_minus1);
        const auto& X(BRDFReconstructionModel<Scalar>::X);
        const auto& dim(BRDFReconstructionModel<Scalar>::dim);
        
        uint num_brdfs = brdfNames.size();
        Z.resize(num_brdfs, MERLReader::num_coefficientsBRDF);
        
        for (unsigned int i = 0; i < num_brdfs; ++i) {
            Z.row(i) = MERLReader::read_brdf<Scalar>((brdfFolderPath+"/"+brdfNames[i]).c_str());
        }
        centerMat<Scalar>(Z, meanBRDF);
        
        reconstructor = std::unique_ptr<BRDFRecType>(new BRDFRecType(Z, K_minus1, X, meanBRDF, dim));
    }
}
