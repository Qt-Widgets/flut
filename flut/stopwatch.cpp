#include "stopwatch.hpp"

namespace flut
{
	void stopwatch::add_measure( const string& s )
	{
		auto now = timer_.seconds();
		auto iter = std::find_if( measures_.begin(), measures_.end(), [&]( measure_t& m ) { return m.first == s; } );
		if ( iter == measures_.end() )
			measures_.push_back( make_pair( s, now - epoch_ ) );
		else iter->second += now - epoch_;
		epoch_ = timer_.seconds();
		internal_measure_ += epoch_ - now;
	}

	flut::prop_node stopwatch::get_report( int decimals )
	{
		auto old_precision = set_to_str_precision( decimals );

		prop_node pn;
		for ( auto& m : measures_ )
			pn.push_back( m.first, m.second );
		pn.push_back( "internal", internal_measure_ );

		set_to_str_precision( old_precision );

		return pn;
	}
}
