// The MIT License (MIT)
//
// Copyright (c) 2019-2020 Darrell Wright
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

#include "daw/json/daw_json_link.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>

namespace daw::cookbook_class1 {
	struct MyClass1 {
		std::string member_0;
		int member_1;
		bool member_2;
	};

	bool operator==( MyClass1 const &lhs, MyClass1 const &rhs ) {
		return std::tie( lhs.member_0, lhs.member_1, lhs.member_2 ) ==
		       std::tie( rhs.member_0, rhs.member_1, rhs.member_2 );
	}
} // namespace daw::cookbook_class1

namespace daw::json {
	template<>
	struct json_data_contract<daw::cookbook_class1::MyClass1> {
#if defined( __cpp_nontype_template_parameter_class )
		using type =
		  json_member_list<json_string<"member0">, json_number<"member1", int>,
		                   json_bool<"member2">>;
#else
		static inline constexpr char const member0[] = "member0";
		static inline constexpr char const member1[] = "member1";
		static inline constexpr char const member2[] = "member2";
		using type =
		  json_member_list<json_string<member0>, json_number<member1, int>,
		                   json_bool<member2>>;
#endif
		static inline auto
		to_json_data( daw::cookbook_class1::MyClass1 const &value ) {
			return std::forward_as_tuple( value.member_0, value.member_1,
			                              value.member_2 );
		}
	};
} // namespace daw::json

int main( ) {
	std::string_view data = R"(
{
  "member0": "this is a test",
  "member1": 314159,
  "member2": true
}
)";

	daw::cookbook_class1::MyClass1 const cls =
	  daw::json::from_json<daw::cookbook_class1::MyClass1>(
	    std::string_view( data.data( ), data.size( ) ) );

	daw_json_assert( cls.member_0 == "this is a test", "Unexpected value" );
	daw_json_assert( cls.member_1 == 314159, "Unexpected value" );
	daw_json_assert( cls.member_2 == true, "Unexpected value" );

	std::stringstream ss{};
	auto it = std::ostreambuf_iterator<char>( ss );

	(void)daw::json::to_json( cls, it );
	std::string const str = ss.str( );
	puts( str.c_str( ) );
}