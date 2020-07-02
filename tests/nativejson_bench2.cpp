// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#if not defined( __cpp_constexpr_dynamic_alloc )
// constexpr dtor's are not available prior to c++20
#define DAW_JSON_NO_CONST_EXPR
#endif

#include "citm_test.h"
#include "geojson.h"
#include "twitter_test2.h"

#include "daw/json/daw_json_link.h"

#include <daw/daw_benchmark.h>
#include <daw/daw_memory_mapped_file.h>
#include <daw/daw_string_view.h>

#include <cstdlib>
#include <iostream>
#include <string>

#if defined( NDEBUG ) and not defined( DEBUG )
#define NUMRUNS 250
#else
#define NUMRUNS 10
#endif

int main( int argc, char **argv ) try {
	try {
		using namespace daw::json;
#if defined( NDEBUG ) and not defined( DEBUG )
		std::cout << "release run\n";
#else
		std::cout << "debug run\n";
#endif
		if( argc < 4 ) {
			std::cerr << "Must supply a filenames to open\n";
			std::cerr << "twitter citm canada\n";
			exit( 1 );
		}

		auto const json_data1 = daw::filesystem::memory_mapped_file_t<>( argv[1] );
		auto const json_data2 = daw::filesystem::memory_mapped_file_t<>( argv[2] );
		auto const json_data3 = daw::filesystem::memory_mapped_file_t<>( argv[3] );
		auto json_sv1 = std::string_view( json_data1.data( ), json_data1.size( ) );
		auto json_sv2 = std::string_view( json_data2.data( ), json_data2.size( ) );
		auto json_sv3 = std::string_view( json_data3.data( ), json_data3.size( ) );

		auto const sz = json_sv1.size( ) + json_sv2.size( ) + json_sv3.size( );
		std::cout << "Processing: " << daw::utility::to_bytes_per_second( sz )
		          << '\n';

		std::cout << std::flush;

		std::optional<daw::twitter::twitter_object_t> twitter_result{ };
		std::optional<daw::citm::citm_object_t> citm_result{ };
		std::optional<daw::geojson::Polygon> canada_result{ };
		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson_twitter bench", json_sv1.size( ),
		  [&twitter_result]( auto f1 ) {
			  twitter_result =
			    daw::json::from_json<daw::twitter::twitter_object_t>( f1 );
		  },
		  json_sv1 );
		daw::do_not_optimize( twitter_result );
		daw_json_assert( twitter_result, "Missing value -> twitter_result" );
		daw_json_assert( twitter_result->statuses.size( ) > 0,
		                 "Expected values: twitter_result is empty" );
		daw_json_assert(
		  twitter_result->statuses.front( ).user.id == "1186275104",
		  std::string( "Expected values: user_id had wrong value, "
		               "expected 1186275104.  Got " ) +
		    static_cast<std::string>( twitter_result->statuses.front( ).user.id ) );
		twitter_result.reset( );

		std::cout << std::flush;

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson_twitter bench trusted", json_sv1.size( ),
		  [&twitter_result]( auto f1 ) {
			  twitter_result =
			    daw::json::from_json<daw::twitter::twitter_object_t,
			                         NoCommentSkippingPolicyUnchecked>( f1 );
		  },
		  json_sv1 );
		daw::do_not_optimize( twitter_result );
		daw_json_assert( twitter_result, "Missing value" );
		daw_json_assert( twitter_result->statuses.size( ) > 0, "Expected values" );
		daw_json_assert( twitter_result->statuses.front( ).user.id == "1186275104",
		                 "Expected values" );
		twitter_result.reset( );

		std::cout << std::flush;

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson_citm bench", json_sv2.size( ),
		  [&citm_result]( auto f2 ) {
			  citm_result = daw::json::from_json<daw::citm::citm_object_t>( f2 );
		  },
		  json_sv2 );
		daw::do_not_optimize( citm_result );
		daw_json_assert( citm_result, "Missing value" );
		daw_json_assert( citm_result->areaNames.size( ) > 0, "Expected values" );
		daw_json_assert( citm_result->areaNames.count( 205706005 ) == 1,
		                 "Expected value" );
		daw_json_assert( citm_result->areaNames[205706005] == "1er balcon jardin",
		                 "Incorrect value" );
		citm_result.reset( );

		std::cout << std::flush;

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson_citm bench trusted", json_sv2.size( ),
		  [&citm_result]( auto f2 ) {
			  citm_result =
			    daw::json::from_json<daw::citm::citm_object_t,
			                         NoCommentSkippingPolicyUnchecked>( f2 );
		  },
		  json_sv2 );
		daw_json_assert( citm_result, "Missing value" );
		daw_json_assert( citm_result->areaNames.size( ) > 0, "Expected values" );
		daw_json_assert( citm_result->areaNames.count( 205706005 ) == 1,
		                 "Expected value" );
		daw_json_assert( citm_result->areaNames[205706005] == "1er balcon jardin",
		                 "Incorrect value" );
		citm_result.reset( );

		std::cout << std::flush;

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson_canada bench", json_sv3.size( ),
		  [&canada_result]( auto f3 ) {
			  canada_result = daw::json::from_json<daw::geojson::Polygon>(
			    f3, "features[0].geometry" );
		  },
		  json_sv3 );
		daw::do_not_optimize( canada_result );
		daw_json_assert( canada_result, "Missing value" );
		canada_result.reset( );

		std::cout << std::flush;

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson_canada bench trusted", json_sv3.size( ),
		  [&canada_result]( auto f3 ) {
			  canada_result = daw::json::from_json<daw::geojson::Polygon,
			                                       NoCommentSkippingPolicyUnchecked>(
			    f3, "features[0].geometry" );
		  },
		  json_sv3 );
		daw::do_not_optimize( canada_result );
		daw_json_assert( canada_result, "Missing value" );
		canada_result.reset( );

		std::cout << std::flush;

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson bench", sz,
		  [&]( auto f1, auto f2, auto f3 ) {
			  twitter_result =
			    daw::json::from_json<daw::twitter::twitter_object_t>( f1 );
			  citm_result = daw::json::from_json<daw::citm::citm_object_t>( f2 );
			  canada_result = daw::json::from_json<daw::geojson::Polygon>(
			    f3, "features[0].geometry" );
		  },
		  json_sv1, json_sv2, json_sv3 );

		std::cout << std::flush;

		daw::do_not_optimize( twitter_result );
		daw::do_not_optimize( citm_result );
		daw::do_not_optimize( canada_result );
		daw_json_assert( twitter_result, "Missing value" );
		daw_json_assert( twitter_result->statuses.size( ) > 0, "Expected values" );
		daw_json_assert( twitter_result->statuses.front( ).user.id == "1186275104",
		                 "Missing value" );
		daw_json_assert( citm_result, "Missing value" );
		daw_json_assert( citm_result->areaNames.size( ) > 0, "Expected values" );
		daw_json_assert( citm_result->areaNames.count( 205706005 ) == 1,
		                 "Expected value" );
		daw_json_assert( citm_result->areaNames[205706005] == "1er balcon jardin",
		                 "Incorrect value" );
		daw_json_assert( canada_result, "Missing value" );
		twitter_result.reset( );
		citm_result.reset( );
		canada_result.reset( );

		daw::bench_n_test_mbs<NUMRUNS>(
		  "nativejson bench trusted", sz,
		  [&]( auto f1, auto f2, auto f3 ) {
			  twitter_result =
			    daw::json::from_json<daw::twitter::twitter_object_t,
			                         NoCommentSkippingPolicyUnchecked>( f1 );
			  citm_result =
			    daw::json::from_json<daw::citm::citm_object_t,
			                         NoCommentSkippingPolicyUnchecked>( f2 );
			  canada_result = daw::json::from_json<daw::geojson::Polygon,
			                                       NoCommentSkippingPolicyUnchecked>(
			    f3, "features[0].geometry" );
		  },
		  json_sv1, json_sv2, json_sv3 );

		std::cout << std::flush;

		daw::do_not_optimize( twitter_result );
		daw::do_not_optimize( citm_result );
		daw::do_not_optimize( canada_result );

		daw_json_assert( twitter_result, "Missing value" );
		daw_json_assert( twitter_result->statuses.size( ) > 0, "Expected values" );
		daw_json_assert( twitter_result->statuses.front( ).user.id == "1186275104",
		                 "Missing value" );
		daw_json_assert( citm_result, "Missing value" );
		daw_json_assert( citm_result->areaNames.size( ) > 0, "Expected values" );
		daw_json_assert( citm_result->areaNames.count( 205706005 ) == 1,
		                 "Expected value" );
		daw_json_assert( citm_result->areaNames[205706005] == "1er balcon jardin",
		                 "Incorrect value" );
		daw_json_assert( canada_result, "Missing value" );
	} catch( daw::json::json_exception const &je ) {
		std::cerr << "Unexpected error while testing: " << je.reason( ) << '\n';
		exit( EXIT_FAILURE );
	}
} catch( daw::json::json_exception const &jex ) {
	std::cerr << "Exception thrown by parser: " << jex.reason( ) << std::endl;
	exit( 1 );
}