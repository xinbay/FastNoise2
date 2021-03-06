#pragma once
#include "Generator.h"

namespace FastNoise
{
    class DomainWarp : public virtual Modifier<>
    {
    public:        
        void SetWarpFrequency( float value ) { mWarpFrequency = value; }
        void SetWarpAmplitude( float value ) { mWarpAmplitude = value; } 
        float GetWarpFrequency() { return mWarpFrequency; }
        float GetWarpAmplitude() { return mWarpAmplitude; } 

    protected:
        float mWarpFrequency = 0.5f;
        float mWarpAmplitude = 1.0f;

        FASTNOISE_METADATA_ABSTRACT( Modifier<> )
        
            Metadata( const char* className ) : Modifier<>::Metadata( className )
            {
                memberVariables.emplace_back( "Warp Frequency", 0.5f, &SetWarpFrequency );
                memberVariables.emplace_back( "Warp Amplitude", 1.0f, &SetWarpAmplitude );
            }
        };
    };

    class DomainWarpGradient : public virtual DomainWarp
    {
        FASTNOISE_METADATA( DomainWarp )
            using DomainWarp::Metadata::Metadata;
        };        
    };
}
