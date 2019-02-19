#ifndef BRDF_RECONSTRUCTION_MODEL_H
#define BRDF_RECONSTRUCTION_MODEL_H

/**
 * @file BRDFReconstructionModel.h
 */

#include <iostream>
#include <fstream>

#include <string>
#include <memory>

#include "MERLReader.h"
#include "BRDFReconstructed.h"
#include "Parametrisation.h"
#include "types.h"

#include <QThread>
#include <QObject>

namespace ChefDevr
{
    class ProgressInterface : public QObject
    {
        Q_OBJECT
    signals:
        void initRange(int min, int max);
        void progressChanged(int progress);
    };
    
    /**
     * @brief The class that allows reconstruction of BRDFs in the BRDF Explorer format
     * @tparam Scalar The type of the values used to reconstruct a BRDF.
     * The precision of this type is crucial to reconstruct an accurate BRDF from the latent space.
     */
    template <typename Scalar>
    class BRDFReconstructionModel : public ProgressInterface
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
        ~BRDFReconstructionModel() = default;
        
        virtual void init() = 0;
        
        /**
         * @brief Constructs a BRDF from its latent coordinates
         * @param x the first coordinate of the BRDF in the latent space
         * @param y the second coordinate of the BRDF in the latent space
         * @return the reconstructed BRDF
         */
        BRDFReconstructed<Scalar>* createBRDFFromLSCoord (Scalar x, Scalar y) const;

        class BRDFReconstructionModelError : public std::runtime_error {
        public:
            explicit BRDFReconstructionModelError(const std::string &message_error) :
            runtime_error{message_error} {}
        };
        
        inline const Vector<Scalar>& getX() const { return X; }
        
        inline const std::vector<std::string>& getBrdfNames() const { return brdfNames; }
        
        inline int getBrdfNumber() const { return brdfNames.size(); }
    
    protected:
        /** 
         * @brief Latent variables column vector
         * 
         * Each stack of dim elements makes a latent variable
         */
        Vector<Scalar> X;
        
        /**
         * @brief List of brdf names
         */
        std::vector<std::string> brdfNames;
        
        /**
         * @brief The mean brdf substracted from Z
         */
        RowVector<Scalar> meanBRDF;
        
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
        std::unique_ptr<BRDFReconstructor<Scalar>> brdfReconstructor;
        
        std::string brdfFolderPath;
    };
    
    template <typename Scalar>
    class BRDFModelInitThread : public QThread
    {
    public:
        BRDFModelInitThread (std::unique_ptr<BRDFReconstructionModel<Scalar>>& _brdfModel) :
            
            QThread(),
            brdfModel(_brdfModel)
        {}
        
    protected:
        void run() override{
            brdfModel->init();
        }
            
        std::unique_ptr<BRDFReconstructionModel<Scalar>>& brdfModel;
    };
}// namespace ChefDevr

#include "BRDFReconstructionModel.hpp"

#endif
