#include <algorithm>    // for max used inside SPD CPU code.
#include <cmath>        // for fabs, abs, sinf, sqrt, etc.
#include <string>       // for memset
#include <cfloat>       // for FLT_EPSILON
#include <FidelityFX/host/ffx_frameinterpolation.h>

#define FFX_CPU

#include <FidelityFX/gpu/ffx_core.h>
#include <FidelityFX/gpu/spd/ffx_spd.h>
#include <ffx_object_management.h>

#include "ffx_frameinterpolation_vpumod.h"

/*
void LoadTexture(const char* filename)
{
    // Load texture from file
    std::experimental::filesystem::path texturePath(filename);
    bool fileExists = filesystem::exists(texturePath);

    if (!fileExists)
    {
        // Error handling
        return;
    }
    else
    {
        // Load texture
        TextureDesc texDesc = {};
    }
}
*/

int main(int argc, char** argv)
{
    return 0;
}
