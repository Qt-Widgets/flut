#pragma once

#include "data_header.hpp"
#include "flut/system/assert.hpp"

namespace flut
{
	template< typename T, typename L = void >
	class circular_frame_buffer
	{
	public:
		circular_frame_buffer( size_t channels = 0, size_t frames = 0 ) : data( frames * channels ), num_frames( frames ), cur_frame( 0 ), header( channels ) {}
		~circular_frame_buffer() {}

		index_t add_frame() { return ++cur_frame; }
		size_t frame_count() { return cur_frame + 1; }

		void set_value( index_t channel, const T& value ) { data[ cur_frame * this->channel_count() + this->channel_count() ] = value; }

		const T* get_frame( index_t frame ) {
			flut_assert( frame >= frame_count() - num_frames && frame < frame_count() );
			return data[ ( frame % num_frames ) * this->channel_count() ];
		}

		T get_value( index_t frame, index_t channel ) {
			flut_assert( frame >= frame_count() - num_frames && frame < frame_count() && channel < this->channel_count() );
			return data[ ( frame % num_frames ) * this->channel_count() + channel ];
		}

		T get_interpolated_value( index_t frame0, index_t channel, T pos ) {
			flut_assert( frame0 >= frame_count() - num_frames && frame0 < frame_count() && channel < this->channel_count() );
			index_t ofs0 = ( frame0 % num_frames ) * this->channel_count() + channel;
			index_t ofs1 = ( ( frame0 + 1 ) % num_frames ) * this->channel_count() + channel;
			return ( T(1) - pos ) * data[ ofs0 ] + pos * data[ ofs1 ];
		}

	private:
		data_header< L > header;
        std::vector< T > data;
		size_t num_frames;
		index_t cur_frame;
	};
}
