#include "BRDFReconstructionModel.h"

#include <iostream>
#include <string>
#include <fstream>

namespace ChefDevr
{
    template <typename Scalar>
    BRDFReconstructionModel<Scalar>::BRDFReconstructionModel(std::string paramtrzFilePath, std::string brdfFolderPath)
        : paramtrzFilePath(paramtrzFilePath),
          brdfFolderPath(brdfFolderPath)
    {

        std::ifstream file_param(paramtrzFilePath);

        if (!file_param.is_open()){
            std::cerr << "Could not create file \"" << paramtrzFilePath<< "\"" << std::endl;
        }

        std::string line;

        std::getline(file_param, line);
        std::getline(file_param, line);
        std::getline(file_param, line);

        uint rows, cols;
        file_param >> rows >> cols;

        dim = rows;

        K_minus1 = Matrix<Scalar>(rows,cols);

        for (uint i = 0; i < rows; ++i) {
            for (uint j = 0; j < cols; ++j) {
                file_param >> K_minus1(i,j);
            }
        }

        std::getline(file_param, line);
        std::getline(file_param, line);

        uint nbBRDF;
        file_param >> nbBRDF;

        std::string brdf_filename;
        Scalar x,y;
        std::vector<std::string> brdfs_filenames{};
        X = Vector<Scalar>(nbBRDF*2);
        for (uint i = 0; i < nbBRDF; ++i) {
            file_param >> brdf_filename >> x >> y;
            brdfs_filenames.emplace_back(brdf_filename);
            X[i*2] = x;
            X[i*2+1] = y;
        }

        uint num_brdfs = brdfs_filenames.size();
        const unsigned int num_coefficientsBRDF = 3 * 90 * 90 * 360 / 2;
        Matrix<Scalar> Z{num_brdfs, num_coefficientsBRDF};

        //const auto num_coefficients = num_brdfs * num_coefficientsBRDF;
        //stxxl::vector<Scalar, 1> Z_stxxl;
        //Z_stxxl.reserve(num_coefficients);

        //auto Z_iterator = Z_stxxl.begin();
        for (unsigned int i = 0; i < num_brdfs; ++i) {
            Z.row(i) = read_brdf(num_coefficientsBRDF, (brdfFolderPath+"/"+brdfs_filenames[i]).c_str());
            // clamp negative values to zero
            Z.row(i) = Z.row(i).cwiseMax(Scalar(0));

            //StreamType input{brdf.begin(), brdf.end()};
            //Z_iterator = stxxl::stream::materialize(input, Z_iterator);
        }

        std::cout << "X :" << X << std::endl;
        std::cout << "Km1 :" << K_minus1 << std::endl;
        //std::cout << "Z :" << Z << std::endl;
        std::cout << "dim :" << dim << std ::endl;

    }

    template <typename Scalar>
    RowVector<Scalar> BRDFReconstructionModel<Scalar>::read_brdf(const unsigned int num_coefficientsNeeded, const char *filePath) {
        FILE *file = std::fopen(filePath, "rb");
        if (!file) {
            throw BRDFReconstructionModelError{std::string{"The file "} + filePath + " could not have been opened"};
        }

        unsigned int dims[3];
        std::fread(dims, sizeof(unsigned int), 3, file);
        const unsigned int num_coefficients = dims[0] * dims[1] * dims[2] * 3;
        if (num_coefficients != num_coefficientsNeeded) {
            std::fclose(file);
            throw BRDFReconstructionModelError{std::string{"Dimensions don't match : "} + std::to_string(num_coefficients) + " is not equal to " + std::to_string(num_coefficientsNeeded)};
        }

        RowVector<Scalar> brdf{num_coefficients};
        std::fread(brdf.data(), sizeof(Scalar), num_coefficients, file);

        std::fclose(file);

        return brdf;
    }


    template <typename Scalar>
    BRDFReconstructed BRDFReconstructionModel<Scalar>::createBRDFFromLSCoord (Scalar x, Scalar y) {
        return BRDFReconstructed();
    }


} // namespace ChevDevr
