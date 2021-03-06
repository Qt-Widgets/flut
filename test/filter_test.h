#pragma once

#include "flut/math/math.hpp"
#include "flut/storage.hpp"
#include "flut/filter.hpp"
#include <fstream>

namespace flut
{
	inline float filter_test_function( float x )
	{
		float y = 0.0f;
		for ( int i = 1; i <= 8; ++i )
			y += sin( x * 2 * float_pi * i * i ) / i;
		return y;
	}

	void filter_test()
	{
		storage< float > sto;
		auto f1 = make_lowpass_butterworth_2nd_order( 0.05f ); // 50Hz
		auto f2 = make_lowpass_butterworth_2nd_order( 0.02f ); // 20Hz
		auto f3 = make_lowpass_butterworth_2nd_order( 0.01f ); // 10Hz
		auto f4 = make_lowpass_butterworth_2nd_order( 0.005f ); // 5Hz
		for ( float x = 0; x < 2; x += 0.001f ) // 1000Hz
		{
			sto.add_frame();
			auto s = filter_test_function( x );
			sto[ "signal" ] = s;
			sto[ "f1" ] = f1( s );
			sto[ "f2" ] = f2( s );
			sto[ "f3" ] = f3( s );
			sto[ "f4" ] = f4( s );
		}
		
		std::ofstream( "X:/filter_test.txt" ) << sto;
	}
}
