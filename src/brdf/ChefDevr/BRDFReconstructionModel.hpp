#include "BRDFReconstructionModel.h"

#include <iostream>
#include <string>
#include <fstream>
#include "MERLReader.h"

namespace ChefDevr
{
    template <typename Scalar>
    BRDFReconstructionModel<Scalar>::BRDFReconstructionModel(std::string paramtrzFilePath, std::string brdfFolderPath)
    {

        std::ifstream file_param(paramtrzFilePath);

        if (!file_param.is_open()){
            std::cerr << "Could not read file \"" << paramtrzFilePath<< "\"" << std::endl;
            return;
        }

        std::string line;

        std::getline(file_param, line);
        std::getline(file_param, line);
        std::getline(file_param, line);

        uint rows, cols;
        file_param >> rows >> cols;

        K_minus1 = Matrix<Scalar>(rows,cols);

        for (uint i = 0; i < rows; ++i)
            for (uint j = 0; j < cols; ++j)
                file_param >> K_minus1(i,j);

        std::getline(file_param, line);
        std::getline(file_param, line);
        
        uint nbBRDF;
        file_param >> nbBRDF >> dim;

        Scalar tmp;
        std::string brdf_filename;
        X = Vector<Scalar>(nbBRDF*dim);
        for (uint i = 0; i < nbBRDF; ++i) {
            file_param >> brdf_filename;
            brdfNames.emplace_back(brdf_filename);
            for(uint j=0; j<dim; j++){
                file_param >> tmp;
                X[i*dim+j] = tmp;
            }
        }
        
        meanBRDF.resize(MERLReader::num_coefficientsBRDF);
    }

    template <typename Scalar>
    BRDFReconstructed* BRDFReconstructionModel<Scalar>::createBRDFFromLSCoord (Scalar x, Scalar y) const
    {
        int numBRDFSamples(brdfReconstructor->getBRDFCoeffNb());
        float* brdfData = new float[numBRDFSamples];
        Eigen::Map<RowVector<float>> brdf(brdfData, numBRDFSamples);
        Vector<Scalar> coord; 
        coord << x, y;
        
        brdfReconstructor->reconstruct(brdf, coord);
        return new BRDFReconstructed(numBRDFSamples, brdfData);
    }


} // namespace ChevDevr
