

namespace ChefDevr
{
    template <typename Scalar>
    BRDFReconstructed<Scalar>::BRDFReconstructed(int _numBRDFSamples, const Scalar* _brdfData) : BRDFMeasuredMERL()
    {
        BRDFMeasuredMERL::initBRDFData(_brdfData, _numBRDFSamples);
    }

    template <typename Scalar>
    void BRDFReconstructed<Scalar>::saveAsBRDF(const std::string &path) const {
        std::ofstream file(path, ios::binary | ios::out | ios::trunc);

        if (!file.is_open()){
            std::cerr << "Could not create file \"" << path << "\"" << std::endl;
        } else {

            int dims[3]{
                    MERLReader::samplingResolution_thetaH,
                    MERLReader::samplingResolution_thetaD,
                    MERLReader::samplingResolution_phiD / 2};


            file.write(reinterpret_cast<char *>(&dims[0]), sizeof(int));
            file.write(reinterpret_cast<char *>(&dims[1]), sizeof(int));
            file.write(reinterpret_cast<char *>(&dims[2]), sizeof(int));

            for (unsigned int i(0); i < MERLReader::num_coefficientsBRDF; ++i) {
                double coefficient = brdfData[i];
                file.write(reinterpret_cast<char *>(&coefficient), sizeof(double));
            }

            file.close();
        }
    }

}
