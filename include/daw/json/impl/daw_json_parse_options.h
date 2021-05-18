// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#pragma once

#include "version.h"

#include <daw/cpp_17.h>
#include <daw/daw_hide.h>
#include <daw/daw_traits.h>

#include <ciso646>
#include <cstddef>
#include <cstdint>
#include <tuple>
#include <utility>

namespace daw::json {
	inline namespace DAW_JSON_VER {
		namespace json_details {
			using policy_options_t = std::uint32_t;

			template<typename>
			inline constexpr unsigned policy_bits_width = 0;

			template<typename>
			inline constexpr auto default_policy_value = [] {
				struct unknown_policy {};
				return unknown_policy{ };
			}( );

		} // namespace json_details

		/***
		 * Allow for different optimizations.  Currently only the compile_time path
		 * is fully supported. The others may offer faster parsing. The default is
		 * compile_time, it provides constexpr parsing and generally is faster
		 * currently.
		 */
		enum class ExecModeTypes : unsigned {
			compile_time,
			runtime, /* testing */
			simd     /* testing */
		};         // 2bits

		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<ExecModeTypes> = 2;

			template<>
			inline constexpr auto default_policy_value<ExecModeTypes> =
			  ExecModeTypes::compile_time;
		} // namespace json_details

		/***
		 * Input is a zero terminated string.  If this cannot be detected, you can
		 * specify it here.  Offers some optimization possibilities in the parser.
		 * Default is no, to try and detect, but use the safer assumption that the
		 * buffer does not end in zero.
		 */
		enum class ZeroTerminatedString : unsigned { no, yes }; // 1bit
		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<ZeroTerminatedString> = 1;

			template<>
			inline constexpr auto default_policy_value<ZeroTerminatedString> =
			  ZeroTerminatedString::no;
		} // namespace json_details

		/***
		 * Allow comments in JSON.  The supported modes are none, C++ style
		 * comments, and # hash style comments.  Default is none, no comments
		 * allowed
		 */
		enum class PolicyCommentTypes : unsigned { none, cpp, hash }; // 2bits
		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<PolicyCommentTypes> = 2;

			template<>
			inline constexpr auto default_policy_value<PolicyCommentTypes> =
			  PolicyCommentTypes::none;
		} // namespace json_details
		/***
		 * Enable all structure, buffer, and type checking.  The default is yes, but
		 * no still does some checking and can be faster.
		 */
		enum class CheckedParseMode : unsigned { yes, no }; // 1bit
		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<CheckedParseMode> = 1;

			template<>
			inline constexpr auto default_policy_value<CheckedParseMode> =
			  CheckedParseMode::yes;
		} // namespace json_details

		/***
		 * Allow the escape character '\' in names.  This forces a slower parser and
		 * is generally not needed.  The default is no, and the end of string
		 * matching only needs to look for a `"`, not skip `\"` in names.
		 */
		enum class AllowEscapedNames : unsigned { no, yes }; // 1bit
		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<AllowEscapedNames> = 1;

			template<>
			inline constexpr auto default_policy_value<AllowEscapedNames> =
			  AllowEscapedNames::no;
		} // namespace json_details

		/***
		 * Testing
		 * Use precise IEEE754 parsing of real numbers.  The default is no, and
		 * results is much faster parsing with very small errors of 0-2ulp.
		 */
		enum class IEEE754Precise : unsigned { no, yes }; // 1bit
		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<IEEE754Precise> = 1;

			template<>
			inline constexpr auto default_policy_value<IEEE754Precise> =
			  IEEE754Precise::no;
		} // namespace json_details

		/***
		 * If the hashes of all members being looked are unique, the lookup of names
		 * as they are found in the document stops at hash checking by default.  You
		 * can force a full string check by setting to yes.
		 */
		enum class ForceFullNameCheck : unsigned { no, yes }; // 1bit
		namespace json_details {
			template<>
			inline constexpr unsigned policy_bits_width<ForceFullNameCheck> = 1;

			template<>
			inline constexpr auto default_policy_value<ForceFullNameCheck> =
			  ForceFullNameCheck::no;
		} // namespace json_details
		/* *****************************************
		 * Implementation details
		 */
		namespace json_details {
			template<typename Policy, typename Policies>
			struct policy_bits_start_impl;

			template<typename Policy, typename... Policies>
			struct policy_bits_start_impl<Policy, std::tuple<Policies...>> {
				static constexpr auto idx =
				  traits::pack_index_of_v<Policy, Policies...>;
				static_assert( idx >= 0, "Policy is not registered" );
				using tp_policies = std::tuple<Policies...>;

				template<std::size_t Pos, int End>
				static constexpr unsigned do_step( ) {
					if constexpr( Pos >= static_cast<std::size_t>( End ) ) {
						return 0U;
					}
					return policy_bits_width<std::tuple_element_t<Pos, tp_policies>>;
				}

				template<std::size_t... Is>
				static constexpr unsigned calc( std::index_sequence<Is...> ) {
					return ( do_step<Is, idx>( ) + ... );
				}
			};

			using policy_list =
			  std::tuple<ExecModeTypes, ZeroTerminatedString, PolicyCommentTypes,
			             CheckedParseMode, AllowEscapedNames, IEEE754Precise,
			             ForceFullNameCheck>;

			template<typename Policy, typename Policies>
			inline constexpr unsigned basic_policy_bits_start =
			  policy_bits_start_impl<Policy, Policies>::template calc(
			    std::make_index_sequence<std::tuple_size_v<Policies>>{ } );

			template<typename Policy>
			inline constexpr unsigned policy_bits_start =
			  basic_policy_bits_start<Policy, policy_list>;

			template<typename Policy>
			inline constexpr bool is_policy_flag = policy_bits_width<Policy> > 0;

			template<typename Policy, typename... Policies>
			constexpr Policy get_policy_or( std::tuple<Policies...> const &pols ) {
				constexpr int const pack_idx =
				  daw::traits::pack_index_of_v<Policy, Policies...>;

				if constexpr( pack_idx != -1 ) {
					return std::get<static_cast<std::size_t>( pack_idx )>( pols );
				} else {
					return json_details::default_policy_value<Policy>;
				}
			}

			template<typename Policy>
			constexpr void set_bits( policy_options_t &value, Policy e ) {
				static_assert( is_policy_flag<Policy>,
				               "Only registered policy types are allowed" );
				unsigned new_bits = static_cast<unsigned>( e );
				constexpr unsigned mask = (1U << policy_bits_width<Policy>)-1U;
				new_bits &= mask;
				new_bits <<= policy_bits_start<Policy>;
				value &= ~mask;
				value |= new_bits;
			}

			template<typename Policy, typename... Policies>
			constexpr policy_options_t set_bits( policy_options_t value, Policy pol,
			                                     Policies... pols ) {
				static_assert( ( is_policy_flag<Policies> and ... ),
				               "Only registered policy types are allowed" );

				unsigned new_bits = static_cast<unsigned>( pol );
				constexpr unsigned mask = (1U << policy_bits_width<Policy>)-1U;
				new_bits &= mask;
				new_bits <<= policy_bits_start<Policy>;
				value &= ~mask;
				value |= new_bits;
				if constexpr( sizeof...( Policies ) > 0 ) {
					return set_bits( value, pols... );
				} else {
					return value;
				}
			}

			template<typename Policy>
			constexpr policy_options_t set_bits_for( Policy e ) {
				static_assert( is_policy_flag<Policy>,
				               "Only registered policy types are allowed" );
				policy_options_t new_bits = static_cast<unsigned>( e );
				new_bits <<= policy_bits_start<Policy>;
				return new_bits;
			}

			template<typename>
			struct default_policy_flag_t;

			template<typename... Policies>
			struct default_policy_flag_t<std::tuple<Policies...>> {
				static constexpr policy_options_t value =
				  ( set_bits_for<Policies>( default_policy_value<Policies> ) | ... );
			};

			/***
			 * The defaults for all known policies encoded as a policy_optionts_t
			 */
			inline static constexpr policy_options_t default_policy_flag =
			  default_policy_flag_t<policy_list>::value;

			template<typename Policy, typename Result = Policy>
			constexpr Result get_bits( policy_options_t value ) {
				static_assert( is_policy_flag<Policy>,
				               "Only registered policy types are allowed" );
				constexpr unsigned mask =
				  ( 1U << (policy_bits_start<Policy> + policy_bits_width<Policy>)) - 1U;
				value &= mask;
				value >>= policy_bits_start<Policy>;
				return static_cast<Result>( Policy{ value } );
			}

			template<std::size_t Idx, typename... Ts>
			using switch_t = std::tuple_element_t<Idx, std::tuple<Ts...>>;
		} // namespace json_details
		// ***********************************************

		/***
		 * Create the parser options flag for BasicParsePolicy
		 * @tparam Policies Policy types that satisfy the `is_policy_flag` trait.
		 * @param policies A list of parser options to change from the defaults.
		 * @return A policy_options_t that encodes the options for the parser
		 */
		template<typename... Policies>
		constexpr json_details::policy_options_t
		parse_options( Policies... policies ) {
			static_assert( ( json_details::is_policy_flag<Policies> and ... ),
			               "Only registered policy types are allowed" );
			auto result = json_details::default_policy_flag;
			if constexpr( sizeof...( Policies ) > 0 ) {
				result |= ( json_details::set_bits_for( policies ) | ... );
			}
			return result;
		}
	} // namespace DAW_JSON_VER
} // namespace daw::json