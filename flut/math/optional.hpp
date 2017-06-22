#pragma once

#include <limits>
#include <type_traits>

namespace flut
{
	template< typename T, typename E = void > struct optional
	{
		using value_type = T;
		optional() : has_value_( false ) {}
		optional( const T& v ) : value_( v ), has_value_( true ) {}
		optional( T&& v ) : value_( std::move( v ) ), has_value_( true ) {}
		optional< T, E >& operator=( const T& v ) { value_ = v; has_value_ = true; return *this; }
		optional< T, E >& operator=( T&& v ) { value_ = std::move( v ); has_value_ = true; return *this; }
		operator bool() const { return has_value_; }
		const T& operator*() const { return value_; }
		T value_;
		bool has_value_;
	};

	template< typename T > struct optional< T, typename std::enable_if< std::is_integral<T>::value >::type >
	{
		using value_type = T;
		optional() : value_( num_const<T>::rare() ) {}
		optional( const T& v ) : value_( v ) {}
		optional< T >& operator=( const T& v ) { value_ = v; return *this; }
		operator bool() const { return value_ != num_const<T>::rare(); }
		const T& operator*() const { return value_; }
		T value_;
	};

	template< typename T > struct optional< T, typename std::enable_if< std::is_floating_point<T>::value >::type >
	{
		using value_type = T;
		optional() : value_( std::numeric_limits<T>::quiet_NaN() ) {}
		optional( const T& v ) : value_( v ) {}
		optional< T >& operator=( const T& v ) { value_ = v; return *this; }
		operator bool() const { return value_ == value_; }
		const T& operator*() const { return value_; }
		T value_;
	};

	using optional_int = optional< int >;
	using optional_size = optional< size_t >;
	using optional_float = optional< float >;
	using optional_double = optional< double >;
}
