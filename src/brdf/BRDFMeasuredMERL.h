/*
Copyright Disney Enterprises, Inc. All rights reserved.

This license governs use of the accompanying software. If you use the software, you
accept this license. If you do not accept the license, do not use the software.

1. Definitions
The terms "reproduce," "reproduction," "derivative works," and "distribution" have
the same meaning here as under U.S. copyright law. A "contribution" is the original
software, or any additions or changes to the software. A "contributor" is any person
that distributes its contribution under this license. "Licensed patents" are a
contributor's patent claims that read directly on its contribution.

2. Grant of Rights
(A) Copyright Grant- Subject to the terms of this license, including the license
conditions and limitations in section 3, each contributor grants you a non-exclusive,
worldwide, royalty-free copyright license to reproduce its contribution, prepare
derivative works of its contribution, and distribute its contribution or any derivative
works that you create.
(B) Patent Grant- Subject to the terms of this license, including the license
conditions and limitations in section 3, each contributor grants you a non-exclusive,
worldwide, royalty-free license under its licensed patents to make, have made,
use, sell, offer for sale, import, and/or otherwise dispose of its contribution in the
software or derivative works of the contribution in the software.

3. Conditions and Limitations
(A) No Trademark License- This license does not grant you rights to use any
contributors' name, logo, or trademarks.
(B) If you bring a patent claim against any contributor over patents that you claim
are infringed by the software, your patent license from such contributor to the
software ends automatically.
(C) If you distribute any portion of the software, you must retain all copyright,
patent, trademark, and attribution notices that are present in the software.
(D) If you distribute any portion of the software in source code form, you may do
so only under this license by including a complete copy of this license with your
distribution. If you distribute any portion of the software in compiled or object code
form, you may only do so under a license that complies with this license.
(E) The software is licensed "as-is." You bear the risk of using it. The contributors
give no express warranties, guarantees or conditions. You may have additional
consumer rights under your local laws which this license cannot change.
To the extent permitted under your local laws, the contributors exclude the
implied warranties of merchantability, fitness for a particular purpose and non-
infringement.
*/

#ifndef BRDF_MEASURED_MERL_H
#define BRDF_MEASURED_MERL_H

#include <string>
#include "BRDFBase.h"

#define BRDF_SAMPLING_RES_THETA_H       90
#define BRDF_SAMPLING_RES_THETA_D       90
#define BRDF_SAMPLING_RES_PHI_D         360

class BRDFMeasuredMERL : public BRDFBase, public GLContext
{
public:

    BRDFMeasuredMERL();
    virtual ~BRDFMeasuredMERL();

    bool loadMERLData( const char* filename );

protected:

    virtual void initGL();
    virtual std::string getBRDFFunction();

    virtual void adjustShaderPreRender( DGLShader* );
    
    /**
     * @brief Transforms MERL data to RGBA floats for rendering
     * Allocates brdfData
     * Sets brdfData and numBRDFSamples attributes
     * @param brdf MERL BRDF data
     * @param nbPtrValues Number of values allocated in the pointer
     * @return success
     */
    template <typename Scalar>
    bool initBRDFData(const Scalar* brdf, const int nbPtrValues);

protected:
    float* brdfData;

private:
    std::string brdfFunction;

    void createTBO();

    // IDs needed for the texture buffer object
    GLuint tbo;
    GLuint tex;

    int numBRDFSamples;
};

template <typename Scalar>
bool BRDFMeasuredMERL::initBRDFData(const Scalar* brdf, const int nbPtrValues)
{
    if (nbPtrValues != 3 * BRDF_SAMPLING_RES_THETA_H *
                            BRDF_SAMPLING_RES_THETA_D *
                            BRDF_SAMPLING_RES_PHI_D / 2)
    {
        fprintf(stderr, "Dimensions don't match\n");
        return false;
    }
    numBRDFSamples = nbPtrValues/3;
    
    // transform to RGBA floats
    brdfData = new float[ numBRDFSamples * 3 ];
    for( int i = 0; i < numBRDFSamples; ++i )
    {
            brdfData[i*3 + 0] = brdf[i*3 + 0];
            brdfData[i*3 + 1] = brdf[i*3 + 1];
            brdfData[i*3 + 2] = brdf[i*3 + 2];
    }
    return true;
}

#endif
