#ifndef BRDF_RECONSTRUCTED_H
#define BRDF_RECONSTRUCTED_H

#include "BRDFMeasuredMERL.h"
#include "Parametrisation.h"
/**
 * @file BRDFReconstructed.h
 */


namespace ChefDevr
{
    /**
    * @brief A reconstructed BRDF, in the original space
    * Manipulable with BRDF Explorer
    */
    template <typename Scalar>
    class BRDFReconstructed : public BRDFMeasuredMERL {
    public:
        /**
         * @brief Constructor
         * @param _numBRDFSamples Number of samples for the brdf
         * @param _brdfData Data of the brdf
         * 
         * _brdfData should be allocated and contain the brdf data by the time
         * the constructor is called.
         * The object takes ownership of the pointer
         */
        BRDFReconstructed(int _numBRDFSamples, const Scalar* _brdfData);
        
        /**
        * @brief Save the BRDF in a file
        *
        * The file's format is the same as the MERL DataBase
        */
        void saveAsBRDF();

    private:
    };
} // namespace ChefDevr

#include "BRDFReconstructed.hpp"

#endif
