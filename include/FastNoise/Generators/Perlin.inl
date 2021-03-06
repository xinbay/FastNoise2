#include "FastSIMD/InlInclude.h"

#include "Perlin.h"
#include "CoherentHelpers.inl"

template<typename FS>
class FS_T<FastNoise::Perlin, FS> : public virtual FastNoise::Perlin, public FS_T<FastNoise::Generator, FS>
{
public:
    virtual float32v FS_VECTORCALL Gen( int32v seed, float32v x, float32v y ) final
    {
        float32v xs = FS_Floor_f32( x );
        float32v ys = FS_Floor_f32( y );

        int32v x0 = FS_Convertf32_i32( xs ) * int32v( Primes::X );
        int32v y0 = FS_Convertf32_i32( ys ) * int32v( Primes::Y );
        int32v x1 = x0 + int32v( Primes::X );
        int32v y1 = y0 + int32v( Primes::Y );

        float32v xf0 = xs = x - xs;
        float32v yf0 = ys = y - ys;
        float32v xf1 = xf0 - float32v( 1 );
        float32v yf1 = yf0 - float32v( 1 );

        xs = InterpQuintic( xs );
        ys = InterpQuintic( ys );

        return Lerp(
               Lerp( GetGradientDot( HashPrimes( seed, x0, y0 ), xf0, yf0 ), GetGradientDot( HashPrimes( seed, x1, y0 ), xf1, yf0 ), xs),
               Lerp( GetGradientDot( HashPrimes( seed, x0, y1 ), xf0, yf1 ), GetGradientDot( HashPrimes( seed, x1, y1 ), xf1, yf1 ), xs), ys);
    }

    virtual float32v FS_VECTORCALL Gen( int32v seed, float32v x, float32v y, float32v z ) final
    {
        float32v xs = FS_Floor_f32( x );
        float32v ys = FS_Floor_f32( y );
        float32v zs = FS_Floor_f32( z );

        int32v x0 = FS_Convertf32_i32( xs ) * int32v( Primes::X );
        int32v y0 = FS_Convertf32_i32( ys ) * int32v( Primes::Y );
        int32v z0 = FS_Convertf32_i32( zs ) * int32v( Primes::Z );
        int32v x1 = x0 + int32v( Primes::X );
        int32v y1 = y0 + int32v( Primes::Y );
        int32v z1 = z0 + int32v( Primes::Z );

        float32v xf0 = xs = x - xs;
        float32v yf0 = ys = y - ys;
        float32v zf0 = zs = z - zs;
        float32v xf1 = xf0 - float32v( 1 );
        float32v yf1 = yf0 - float32v( 1 );
        float32v zf1 = zf0 - float32v( 1 );

        xs = InterpQuintic( xs );
        ys = InterpQuintic( ys );
        zs = InterpQuintic( zs );

        return Lerp( Lerp(
               Lerp( GetGradientDot( HashPrimes( seed, x0, y0, z0 ), xf0, yf0, zf0 ), GetGradientDot( HashPrimes( seed, x1, y0, z0 ), xf1, yf0, zf0 ), xs),
               Lerp( GetGradientDot( HashPrimes( seed, x0, y1, z0 ), xf0, yf1, zf0 ), GetGradientDot( HashPrimes( seed, x1, y1, z0 ), xf1, yf1, zf0 ), xs), ys),
               Lerp(
               Lerp( GetGradientDot( HashPrimes( seed, x0, y0, z1 ), xf0, yf0, zf1 ), GetGradientDot( HashPrimes( seed, x1, y0, z1 ), xf1, yf0, zf1 ), xs),
               Lerp( GetGradientDot( HashPrimes( seed, x0, y1, z1 ), xf0, yf1, zf1 ), GetGradientDot( HashPrimes( seed, x1, y1, z1 ), xf1, yf1, zf1 ), xs), ys), zs);
    }
};
