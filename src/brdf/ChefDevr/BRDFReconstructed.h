#ifndef BRDF_RECONSTRUCTED_H
#define BRDF_RECONSTRUCTED_H

#include <fstream>

#include "BRDFMeasuredMERL.h"
#include "Parametrisation.h"
#include "MERLReader.h"
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
        * @brief Save a BRDF in a file
        * @param path the path of file where the BRDF will be saved
        *
        * The file's format is the same as the MERL DataBase
        */
        void saveAsBRDF(const std::string& path) const;

    };
} // namespace ChefDevr

#include "BRDFReconstructed.hpp"

#endif
