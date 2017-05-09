#include "objective.hpp"

#include "flut/math/math.hpp"

namespace flut
{
	bool objective::is_better( fitness_t a, fitness_t b ) const
	{
		return minimize() ? a < b : a > b;
	}

	flut::fitness_t objective::worst_fitness() const
	{
		return minimize() ? math::numeric_const< fitness_t >::max() : math::numeric_const< fitness_t >::lowest();
	}

	function_objective::function_objective( size_t d, function_t func, bool minimize, const param_vec_t& start, const param_vec_t& start_std, const param_vec_t& upper, const param_vec_t& lower ) :
	func_( func ),
	minimize_( minimize )
	{
		for ( size_t i = 0; i < d; ++i )
			param_info_.add( stringf( "%d", i ), start[ i ], start_std[ i ], i < lower.size() ? lower[ i ] : -1e15, i < lower.size() ? lower[ i ] : 1e15 );
	}
}