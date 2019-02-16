#include "BRDFReconstructed.h"

namespace ChefDevr
{
    BRDFReconstructed::BRDFReconstructed(int _numBRDFSamples, float* _brdfData) : BRDFMeasuredMERL()
    {
        BRDFMeasuredMERL::initBRDFData(_brdfData, _numBRDFSamples);
    }
}
