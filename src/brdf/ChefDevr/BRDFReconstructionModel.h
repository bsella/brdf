#ifndef BRDF_RECONSTRUCTION_MODEL_H
#define BRDF_RECONSTRUCTION_MODEL_H

/**
 * @file BRDFReconstructionModel.h
 */

#include <string>

#include "BRDFReconstructed.h"
#include "Parametrisation.h"
#include "types.h"

#include <iostream>
#include <fstream>

namespace ChefDevr
{
    /**
     * @brief The class that allows reconstruction of BRDFs in the BRDF Explorer format
     * @tparam Scalar The type of the values used to reconstruct a BRDF.
     * The precision of this type is crucial to reconstruct an accurate BRDF from the latent space.
     */
    template <typename Scalar>
    class BRDFReconstructionModel
    {
    public:
        
        /**
         * @brief Constructor
         * @param paramtrzFilePath The path of the file that constains the parametrisation data
         * @param brdfFolderPath The path of the folder where BRDF files are located
         * 
         * Loads K_minus1, X and Z from parametrisation data file
         */
        BRDFReconstructionModel(std::string paramtrzFilePath, std::string brdfFolderPath);
        ~BRDFReconstructionModel() {}
        
        /**
         * @brief Constructs a BRDF from its latent coordinates
         * @param x the first coordinate of the BRDF in the latent space
         * @param y the second coordinate of the BRDF in the latent space
         * @return the reconstructed BRDF
         */
        BRDFReconstructed createBRDFFromLSCoord (Scalar x, Scalar y);

        class BRDFReconstructionModelError : public std::runtime_error {
        public:
            explicit BRDFReconstructionModelError(const std::string &message_error) :
            runtime_error{message_error} {}
        };
        /** 
         * @brief Latent variables column vector
         * 
         * Each stack of dim elements makes a latent variable
         */
        Vector<Scalar> X;

        std::vector<std::string> brdfNames;
    
    private:        
        /**
         * @brief The BRDF matrix
         *
         * Each column contains the values of one BRDF
         */
        Matrix<Scalar> Z;
        
        /**
         * @brief the matrix allowing to reconstruct a BRDF from its latent coordinates
         *
         * This is the inverse covariance matrix of the latent variables.
         * The latent variables are the BRDFs taken as reference in the latent space.
         */
        Matrix<Scalar> K_minus1;
        
        
        /** 
         * @brief Dimension of the latent space
         */
        unsigned int dim;
        
        /**
         * @brief The object that does BRDF reconstruction computations
         */
        //BRDFReconstructor brdfReconstructor;

        RowVector<Scalar> read_brdf(unsigned int num_coefficientsNeeded, const char *filePath);

    };
}// namespace ChefDevr

#include "BRDFReconstructionModel.hpp"

#endif
