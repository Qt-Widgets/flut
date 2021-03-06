#pragma once

#include <vector>
#include "flut/math/vec3.hpp"
#include "flut/system/log.hpp"
#include "flut/buffer/interpolation.hpp"
#include "flut/buffer/data_header.hpp"
#include "flut/buffer/circular_frame_buffer.hpp"
#include "flut/circular_deque.hpp"
#include "flut/storage.hpp"

namespace flut
{
	void buffer_test()
	{
		// circular_deque test
		circular_deque< int > cd( 10 );
		for ( int i = 0; i < 30; ++i )
		{
			cd.push_back( i );
			if ( cd.size() == 10 )
			{
				FLUT_TEST( cd.front() == i - 9 );
				cd.pop_front();
			}
		}

		// circular_deque test
		cd.clear();
		cd.reserve( 0 );
		for ( int i = 0; i < 30; ++i )
		{
			cd.push_front( i );
			if ( cd.size() == 20 )
			{
				FLUT_TEST( cd.back() == i - 19 );
				cd.pop_back();
			}
		}

		// regular buffer test
		storage< float, string > buf( 0 );

		//regular_ring_buffer< double, 100, void > ringbuf( 20 );
		for ( int i = 0; i < 10; ++i )
			buf.add_channel( stringf( "channel%d", i ) );

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
