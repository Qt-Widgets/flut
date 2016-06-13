#pragma once

#include <vector>
#include "flut/math/vec3.hpp"
#include "flut/system/log.hpp"
#include "flut/buffer/interpolation.hpp"
#include "flut/buffer/buffer_base.hpp"
#include "flut/buffer/regular_buffer.hpp"
#include "flut/buffer/regular_ring_buffer.hpp"

namespace flut
{
	void buffer_test()
	{
		// regular buffer test
		regular_buffer< double, string > regbuf( 0 );
		//regular_ring_buffer< double, 100, void > ringbuf( 20 );
		for ( int i = 0; i < 10; ++i )
			regbuf.add_channel( stringf( "channel%d", i ) );

		// more tests
		std::vector< std::pair< double, math::vec3 > > buf_test;
		buf_test.push_back( std::make_pair( 0, math::vec3( 1, 0, 0 ) ) );
		buf_test.push_back( std::make_pair( 1, math::vec3( 0, 1, 0 ) ) );
		buf_test.push_back( std::make_pair( 3, math::vec3( 0, 1, 2 ) ) );
		for ( int d = -10; d < 40; ++d )
			log::trace( 0.1 * d, ": ", interpolated_value( buf_test, 0.1 * d ) );

		// more tests
		std::vector< math::vec3 > buf_test2;
		buf_test2.push_back( math::vec3( 1, 0, 0 ) );
		buf_test2.push_back( math::vec3( 0, 1, 0 ) );
		buf_test2.push_back( math::vec3( 0, 1, 2 ) );
		for ( int d = -10; d < 40; ++d )
			log::trace( 0.1 * d, ": ", interpolated_value( buf_test2, 0.1 * d ) );

	}
}
