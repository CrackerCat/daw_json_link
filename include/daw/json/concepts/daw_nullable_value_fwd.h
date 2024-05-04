// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#pragma once

#include "daw/json/impl/version.h"

#include <daw/daw_is_detected.h>

#include <cstddef>
#include <type_traits>

namespace daw::json {
	inline namespace DAW_JSON_VER {
		namespace concepts {
			namespace nullable_impl {
#if not defined( DAW_HAS_GCC ) or DAW_HAS_GCC_VER_GTE( 12, 0 )
				template<typename T, typename... Args>
				using is_list_constructible_test =
				  decltype( T{ std::declval<Args>( )... } );
#else
				template<typename T, typename... Args>
				using is_list_constructible_test =
				  decltype( std::declval<void ( * )( T )>( )(
				    { std::declval<Args>( )... } ) );
#endif
				template<typename T, typename... Args>
				inline constexpr bool is_list_constructible_v =
				  daw::is_detected_v<is_list_constructible_test, T, Args...>;

				template<typename T, typename... Args>
				inline constexpr bool is_nullable_value_type_constructible_v =
				  std::is_constructible_v<T, Args...> or
				  is_list_constructible_v<T, Args...>;

			} // namespace nullable_impl

			struct construct_nullable_with_value_t {
				explicit construct_nullable_with_value_t( ) = default;
			};
			inline constexpr auto construct_nullable_with_value =
			  construct_nullable_with_value_t{ };

			struct construct_nullable_with_pointer_t {
				explicit construct_nullable_with_pointer_t( ) = default;
			};
			inline constexpr auto construct_nullable_with_pointer =
			  construct_nullable_with_pointer_t{ };

			struct construct_nullable_with_empty_t {
				explicit construct_nullable_with_empty_t( ) = default;
			};
			inline constexpr auto construct_nullable_with_empty =
			  construct_nullable_with_empty_t{ };

			DAW_JSON_CPP23_STATIC_CALL_OP_DISABLE_WARNING
			/// @brief Readable values models an option/maybe/nullable type
			/// @tparam T The option type
			template<typename T, typename...>
			struct nullable_value_traits {

				/// @brief The type of the value stored in the nullable type
				using value_type = T;

				/// @brief The type of the nullable type
				using nullable_type = T;

				/// @brief Can this type be read
				static constexpr bool is_nullable = false;

				/// @brief read the value in the nullable type
				/// @return A value_type with the current value
				/// @pre has_value( ) == true
				inline constexpr value_type read( T const &v ) const noexcept {
					return v;
				}
				/// @brief Construct a value in nullable type and return it
				DAW_JSON_CPP23_STATIC_CALL_OP inline constexpr nullable_type
				operator( )( construct_nullable_with_value_t )
				  DAW_JSON_CPP23_STATIC_CALL_OP_CONST
				  noexcept( std::is_nothrow_default_constructible_v<value_type> ) {
					return value_type{ };
				}
				/// @brief Return an empty nullable type
				template<typename... Args,
				         std::enable_if_t<
				           nullable_impl::is_nullable_value_type_constructible_v<
				             nullable_type, Args...>,
				           std::nullptr_t> = nullptr>
				DAW_JSON_CPP23_STATIC_CALL_OP constexpr nullable_type
				operator( )( construct_nullable_with_empty_t,
				             Args &&...args ) DAW_JSON_CPP23_STATIC_CALL_OP_CONST
				  noexcept( std::is_nothrow_constructible_v<nullable_type, Args...> ) {
					if constexpr( std::is_constructible_v<nullable_type, Args...> ) {
						return T( DAW_FWD( args )... );
					} else {
						return T{ DAW_FWD( args )... };
					}
				}
				/// @brief Check the state of the nullable type for a value
				static constexpr bool has_value( T const & ) noexcept {
					return true;
				}
			};
			DAW_JSON_CPP23_STATIC_CALL_OP_ENABLE_WARNING

			/// @brief Determines the type stored inside T
			template<typename T>
			using nullable_value_type_t =
			  typename nullable_value_traits<T>::value_type;

			/// @brief Is T a nullable type
			template<typename T>
			inline constexpr bool is_nullable_value_v =
			  nullable_value_traits<T>::is_nullable;

			/// @brief Check if nullable value has a value
			template<typename T>
			constexpr bool nullable_value_has_value( T const &opt ) {
				return nullable_value_traits<T>::has_value( opt );
			}

			/// @brief Read value from a non-empty nullable value
			/// @pre nullable_value_traits<T>::has_value( ) == true
			template<typename T>
			constexpr auto const &nullable_value_read( T const &opt ) {
				return nullable_value_traits<T>::read( opt );
			}

			template<typename T, typename... Args>
			inline constexpr bool is_nullable_value_constructible_v =
			  is_nullable_value_v<T> and
			  std::is_invocable_v<nullable_value_traits<T>,
			                      construct_nullable_with_value_t, Args...>;

			template<typename T, typename... Args>
			inline constexpr bool is_nullable_pointer_constructible_v =
			  is_nullable_value_v<T> and
			  std::is_invocable_v<nullable_value_traits<T>,
			                      construct_nullable_with_pointer_t, Args...>;

			template<typename T, typename... Args>
			inline constexpr bool is_nullable_value_nothrow_constructible_v =
			  is_nullable_value_constructible_v<T, Args...> and
			  std::is_nothrow_invocable_v<nullable_value_traits<T>,
			                              construct_nullable_with_value_t, Args...>;

			template<typename T>
			inline constexpr bool is_nullable_empty_constructible_v =
			  is_nullable_value_v<T> and
			  std::is_invocable_v<nullable_value_traits<T>,
			                      construct_nullable_with_empty_t>;

			template<typename T>
			inline constexpr bool is_nullable_empty_nothrow_constructible_v =
			  is_nullable_empty_constructible_v<T> and
			  std::is_nothrow_invocable_v<nullable_value_traits<T>,
			                              construct_nullable_with_empty_t>;
		} // namespace concepts
	} // namespace DAW_JSON_VER
} // namespace daw::json
