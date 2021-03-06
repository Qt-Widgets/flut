#pragma once

#include "flut/system/types.hpp"
#include "flut/timer.hpp"
#include "flut/prop_node.hpp"

#ifdef FLUT_COMP_MSVC
#	pragma warning( push )
#	pragma warning( disable: 4251 )
#endif

namespace flut
{
	class FLUT_API profiler
	{
	public:
		struct section
		{
			section( const char* n, size_t i, size_t pi ) : name( n ), id( i ), parent_id( pi ), total_time( 0 ), overhead( 0 ) {}
			const char* name;
			size_t id;
			size_t parent_id;
			nanoseconds_t total_time;
			nanoseconds_t overhead;
			nanoseconds_t epoch;
		};

		void reset();
		section* start_section( const char* name );
		void end_section();
		nanoseconds_t now() const { return timer_.nanoseconds(); }
		prop_node report();
		static profiler& instance() { return instance_; }

	private:
		profiler();
		void report_section( section* s, prop_node& pn );

		nanoseconds_t exclusive_time( section* s );
		nanoseconds_t total_overhead( section* s );
		section* root() { return &sections_.front(); }
		section* find_section( size_t id );
		section* find_section( const char* name, size_t parent_id );
		section* acquire_section( const char* name, size_t parent_id );
		section* add_section( const char* name, size_t parent_id );
		std::vector< section* > get_children( size_t parent_id );

		vector< section > sections_;
		timer timer_;
		static profiler instance_;
		section* current_section_;
		nanoseconds_t duration_of_now;
	};

	struct FLUT_API scoped_section_profiler
	{
		scoped_section_profiler( const char* name ) { profiler::instance().start_section( name ); }
		~scoped_section_profiler() { profiler::instance().end_section(); }
	};
}

#ifdef FLUT_COMP_MSVC
#	pragma warning( pop )
#endif
