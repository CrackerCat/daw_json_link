// The MIT License (MIT)
//
// Copyright (c) 2019 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <daw/daw_benchmark.h>
#include <fstream>
#include <iostream>
#include <streambuf>
#include <string_view>
#include <vector>

#include "daw/json/daw_json_iterator.h"
#include "daw/json/daw_json_link.h"
#include "daw/json/impl/daw_memory_mapped.h"

struct coordinate_t {
	double x;
	double y;
	double z;
	// ignore string name
	// ignore object opts
};

namespace symbols_coordinate_t {
	constexpr static char const x[] = "x";
	constexpr static char const y[] = "y";
	constexpr static char const z[] = "z";
} // namespace symbols_coordinate_t
auto describe_json_class( coordinate_t ) noexcept {
	using namespace daw::json;
#ifdef __cpp_nontype_template_parameter_class
	return class_description_t<json_number<"x">, json_number<"y">,
	                           json_number<"z">>{};
#else
	return class_description_t<json_number<symbols_coordinate_t::x>,
	                           json_number<symbols_coordinate_t::y>,
	                           json_number<symbols_coordinate_t::z>>{};
#endif
}

struct coordinates_t {
	std::vector<coordinate_t> coordinates;
};

namespace symbols_coordinates_t {
	constexpr static char const coordinates[] = "coordinates";
}

auto describe_json_class( coordinates_t ) noexcept {
	using namespace daw::json;
#ifdef __cpp_nontype_template_parameter_class
	return class_description_t<
	  json_array<"coordinates", std::vector<coordinate_t>,
	             json_class<no_name, coordinate_t>>>{};
#else
	return class_description_t<
	  json_array<symbols_coordinates_t::coordinates, std::vector<coordinate_t>,
	             json_class<no_name, coordinate_t>>>{};
#endif
}

int main( int argc, char **argv ) {
	using namespace daw::json;
	std::ios_base::sync_with_stdio( false );

	if( argc < 2 ) {
		std::cerr << "Must supply a filename to open\n";
		exit( 1 );
	}

	auto const json_data = daw::memory_mapped_file<>( argv[1] );
	auto const json_sv = std::string_view( json_data.data( ), json_data.size( ) );

	using iterator_t =
	  daw::json::json_array_iterator<json_class<no_name, coordinate_t>, true>;

	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	size_t sz = 0U;

	// first will be json_array_iterator to the array coordinates in root object
	for( auto first = iterator_t( json_sv, "coordnates" ); first != iterator_t( );
	     ++first ) {
		auto const c = *first;
		++sz;
		x += c.x;
		y += c.y;
		z += c.z;
	}

	auto const dsz = static_cast<double>( sz );
	std::cout << x / dsz << '\n';
	std::cout << y / dsz << '\n';
	std::cout << z / dsz << '\n';
}