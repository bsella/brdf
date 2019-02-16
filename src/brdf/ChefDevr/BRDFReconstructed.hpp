 
namespace ChefDevr
{
    template <typename Scalar>
    BRDFReconstructed<Scalar>::BRDFReconstructed(int _numBRDFSamples, const Scalar* _brdfData) : BRDFMeasuredMERL()
    {
        BRDFMeasuredMERL::initBRDFData(_brdfData, _numBRDFSamples);
    }
}
