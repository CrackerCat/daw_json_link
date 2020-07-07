// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#pragma once

#include <cstdint>
#include <optional>
#include <string_view>
#include <tuple>
#include <vector>

#include <daw/json/daw_json_link.h>

#ifdef __GNUC__
#define DAW_HIDDEN __attribute__( ( visibility( "hidden" ) ) )
#else
#define DAW_HIDDEN
#endif

template<typename T>
struct opt_construct_a {
	constexpr std::optional<T> operator( )( ) const {
		return daw::construct_a<std::optional<T>>( );
	}

	template<typename... Args>
	constexpr std::optional<T> operator( )( Args &&... args ) const {
		return std::optional<T>(
		  daw::construct_a<T>( std::forward<Args>( args )... ) );
	}
};
namespace daw::twitter {
	struct metadata_t {
		std::string_view result_type;
		std::string_view iso_language_code;
	}; // metadata_t

	struct urls_element_t {
		std::string_view url;
		std::string_view expanded_url;
		std::string_view display_url;
		std::vector<std::string_view> indices;
	}; // urls_element_t

	struct url_t {
		std::vector<urls_element_t> urls;
	}; // url_t

	struct description_t {
		std::vector<urls_element_t> urls;
	}; // description_t

	struct entities_t {
		std::optional<url_t> url;
		std::optional<description_t> description;
	}; // entities_t

	struct user_t {
		std::string_view id;
		std::string_view id_str;
		std::string_view name;
		std::string_view screen_name;
		std::string_view location;
		std::string_view description;
		std::optional<std::string_view> url;
		entities_t entities;
		bool _jsonprotected;
		std::string_view followers_count;
		std::string_view friends_count;
		std::string_view listed_count;
		std::string_view created_at;
		std::string_view favourites_count;
		std::optional<std::string_view> utc_offset;
		std::optional<std::string_view> time_zone;
		bool geo_enabled;
		bool verified;
		std::string_view statuses_count;
		std::string_view lang;
		bool contributors_enabled;
		bool is_translator;
		bool is_translation_enabled;
		std::string_view profile_background_color;
		std::string_view profile_background_image_url;
		std::string_view profile_background_image_url_https;
		bool profile_background_tile;
		std::string_view profile_image_url;
		std::string_view profile_image_url_https;
		std::optional<std::string_view> profile_banner_url;
		std::string_view profile_link_color;
		std::string_view profile_sidebar_border_color;
		std::string_view profile_sidebar_fill_color;
		std::string_view profile_text_color;
		bool profile_use_background_image;
		bool default_profile;
		bool default_profile_image;
		bool following;
		bool follow_request_sent;
		bool notifications;
	}; // user_t

	struct hashtags_element_t {
		std::string_view text;
		std::vector<std::string_view> indices;
	}; // hashtags_element_t

	struct tweet_object_t {
		metadata_t metadata;
		std::string_view created_at;
		std::string_view id;
		std::string_view id_str;
		std::string_view text;
		std::string_view source;
		bool truncated;
		std::optional<std::string_view> in_reply_to_status_id;
		std::optional<std::string_view> in_reply_to_status_id_str;
		std::optional<std::string_view> in_reply_to_user_id;
		std::optional<std::string_view> in_reply_to_user_id_str;
		std::optional<std::string_view> in_reply_to_screen_name;
		user_t user;
		std::string_view retweet_count;
		std::string_view favorite_count;
		entities_t entities;
		bool favorited;
		bool retweeted;
		std::optional<bool> possibly_sensitive;
		std::string_view lang;
	}; // statuses_element_t

	struct user_mentions_element_t {
		std::string_view screen_name;
		std::string_view name;
		std::string_view id;
		std::string_view id_str;
		std::vector<std::string_view> indices;
	}; // user_mentions_element_t

	struct medium_t {
		std::string_view w;
		std::string_view h;
		std::string_view resize;
	}; // medium_t

	struct small_t {
		std::string_view w;
		std::string_view h;
		std::string_view resize;
	}; // small_t

	struct thumb_t {
		std::string_view w;
		std::string_view h;
		std::string_view resize;
	}; // thumb_t

	struct large_t {
		std::string_view w;
		std::string_view h;
		std::string_view resize;
	}; // large_t

	struct sizes_t {
		medium_t medium;
		small_t small_;
		thumb_t thumb;
		large_t large;
	}; // sizes_t

	struct media_element_t {
		std::string_view id;
		std::string_view id_str;
		std::vector<std::string_view> indices;
		std::string_view media_url;
		std::string_view media_url_https;
		std::string_view url;
		std::string_view display_url;
		std::string_view expanded_url;
		std::string_view type;
		sizes_t sizes;
	}; // media_element_t

	struct retweeted_status_t {
		metadata_t metadata;
		std::string_view created_at;
		std::string_view id;
		std::string_view id_str;
		std::string_view text;
		std::string_view source;
		bool truncated;
		std::optional<std::string_view> in_reply_to_status_id;
		std::optional<std::string_view> in_reply_to_status_id_str;
		std::optional<std::string_view> in_reply_to_user_id;
		std::optional<std::string_view> in_reply_to_user_id_str;
		std::optional<std::string_view> in_reply_to_screen_name;
		user_t user;
		std::string_view retweet_count;
		std::string_view favorite_count;
		entities_t entities;
		bool favorited;
		bool retweeted;
		std::optional<bool> possibly_sensitive;
		std::string_view lang;
	}; // retweeted_status_t

	struct search_metadata_t {
		std::string_view completed_in;
		std::string_view max_id;
		std::string_view max_id_str;
		std::string_view next_results;
		std::string_view query;
		std::string_view refresh_url;
		std::string_view count;
		std::string_view since_id;
		std::string_view since_id_str;
	}; // search_metadata_t

	struct twitter_object_t {
		std::vector<tweet_object_t> statuses;
		search_metadata_t search_metadata;
	}; // twitter_object_t
} // namespace daw::twitter

namespace daw::json {
	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::metadata_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type =
		  json_member_list<json_string_raw<"result_type", std::string_view>,
		                   json_string_raw<"iso_language_code", std::string_view>>;
#else
		static inline constexpr char const result_type[] = "result_type";
		static inline constexpr char const iso_language_code[] =
		  "iso_language_code";
		using type =
		  json_member_list<json_string_raw<result_type, std::string_view>,
		                   json_string_raw<iso_language_code, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::metadata_t const &value ) {
			return std::forward_as_tuple( value.result_type,
			                              value.iso_language_code );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::urls_element_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_string_raw<"url", std::string_view>,
		  json_string_raw<"expanded_url", std::string_view>,
		  json_string_raw<"display_url", std::string_view>,
		  json_array<"indices", json_custom<no_name, std::string_view>>>;
#else
		static inline constexpr char const url[] = "url";
		static inline constexpr char const expanded_url[] = "expanded_url";
		static inline constexpr char const display_url[] = "display_url";
		static inline constexpr char const indices[] = "indices";
		using type = json_member_list<
		  json_string_raw<url, std::string_view>,
		  json_string_raw<expanded_url, std::string_view>,
		  json_string_raw<display_url, std::string_view>,
		  json_array<indices, json_custom<no_name, std::string_view>>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::urls_element_t const &value ) {
			return std::forward_as_tuple( value.url, value.expanded_url,
			                              value.display_url, value.indices );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::url_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type =
		  json_member_list<json_array<"urls", daw::twitter::urls_element_t>>;
#else
		static inline constexpr char const urls[] = "urls";
		using type =
		  json_member_list<json_array<urls, daw::twitter::urls_element_t>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::url_t const &value ) {
			return std::forward_as_tuple( value.urls );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::description_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type =
		  json_member_list<json_array<"urls", daw::twitter::urls_element_t>>;
#else
		static inline constexpr char const urls[] = "urls";
		using type =
		  json_member_list<json_array<urls, daw::twitter::urls_element_t>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::description_t const &value ) {
			return std::forward_as_tuple( value.urls );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::entities_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_class_null<"url", std::optional<daw::twitter::url_t>,
		                  opt_construct_a<daw::twitter::url_t>>,
		  json_class_null<"description", std::optional<daw::twitter::description_t>,
		                  opt_construct_a<daw::twitter::description_t>>>;
#else
		static inline constexpr char const url[] = "url";
		static inline constexpr char const description[] = "description";
		using type = json_member_list<
		  json_class_null<url, std::optional<daw::twitter::url_t>,
		                  opt_construct_a<daw::twitter::url_t>>,
		  json_class_null<description, std::optional<daw::twitter::description_t>,
		                  opt_construct_a<daw::twitter::description_t>>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::entities_t const &value ) {
			return std::forward_as_tuple( value.url, value.description );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::user_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_custom<"id", std::string_view>,
		  json_string_raw<"id_str", std::string_view>,
		  json_string_raw<"name", std::string_view>,
		  json_string_raw<"screen_name", std::string_view>,
		  json_string_raw<"location", std::string_view>,
		  json_string_raw<"description", std::string_view>,
		  json_string_raw_null<"url", std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_class<"entities", daw::twitter::entities_t>, json_bool<"protected">,
		  json_custom<"followers_count", std::string_view>,
		  json_custom<"friends_count", std::string_view>,
		  json_custom<"listed_count", std::string_view>,
		  json_custom<"created_at", std::string_view>,
		  json_custom<"favourites_count", std::string_view>,
		  json_custom_null<"utc_offset", std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<"time_zone", std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_bool<"geo_enabled">, json_bool<"verified">,
		  json_custom<"statuses_count", std::string_view>,
		  json_string_raw<"lang", std::string_view>,
		  json_bool<"contributors_enabled">, json_bool<"is_translator">,
		  json_bool<"is_translation_enabled">,
		  json_string_raw<"profile_background_color", std::string_view>,
		  json_string_raw<"profile_background_image_url", std::string_view>,
		  json_string_raw<"profile_background_image_url_https", std::string_view>,
		  json_bool<"profile_background_tile">,
		  json_string_raw<"profile_image_url", std::string_view>,
		  json_string_raw<"profile_image_url_https", std::string_view>,
		  json_string_raw_null<"profile_banner_url",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_string_raw<"profile_link_color", std::string_view>,
		  json_string_raw<"profile_sidebar_border_color", std::string_view>,
		  json_string_raw<"profile_sidebar_fill_color", std::string_view>,
		  json_string_raw<"profile_text_color", std::string_view>,
		  json_bool<"profile_use_background_image">, json_bool<"default_profile">,
		  json_bool<"default_profile_image">, json_bool<"following">,
		  json_bool<"follow_request_sent">, json_bool<"notifications">>;
#else
		static inline constexpr char const id[] = "id";
		static inline constexpr char const id_str[] = "id_str";
		static inline constexpr char const name[] = "name";
		static inline constexpr char const screen_name[] = "screen_name";
		static inline constexpr char const location[] = "location";
		static inline constexpr char const description[] = "description";
		static inline constexpr char const url[] = "url";
		static inline constexpr char const entities[] = "entities";
		static inline constexpr char const _jsonprotected[] = "protected";
		static inline constexpr char const followers_count[] = "followers_count";
		static inline constexpr char const friends_count[] = "friends_count";
		static inline constexpr char const listed_count[] = "listed_count";
		static inline constexpr char const created_at[] = "created_at";
		static inline constexpr char const favourites_count[] = "favourites_count";
		static inline constexpr char const utc_offset[] = "utc_offset";
		static inline constexpr char const time_zone[] = "time_zone";
		static inline constexpr char const geo_enabled[] = "geo_enabled";
		static inline constexpr char const verified[] = "verified";
		static inline constexpr char const statuses_count[] = "statuses_count";
		static inline constexpr char const lang[] = "lang";
		static inline constexpr char const contributors_enabled[] =
		  "contributors_enabled";
		static inline constexpr char const is_translator[] = "is_translator";
		static inline constexpr char const is_translation_enabled[] =
		  "is_translation_enabled";
		static inline constexpr char const profile_background_color[] =
		  "profile_background_color";
		static inline constexpr char const profile_background_image_url[] =
		  "profile_background_image_url";
		static inline constexpr char const profile_background_image_url_https[] =
		  "profile_background_image_url_https";
		static inline constexpr char const profile_background_tile[] =
		  "profile_background_tile";
		static inline constexpr char const profile_image_url[] =
		  "profile_image_url";
		static inline constexpr char const profile_image_url_https[] =
		  "profile_image_url_https";
		static inline constexpr char const profile_banner_url[] =
		  "profile_banner_url";
		static inline constexpr char const profile_link_color[] =
		  "profile_link_color";
		static inline constexpr char const profile_sidebar_border_color[] =
		  "profile_sidebar_border_color";
		static inline constexpr char const profile_sidebar_fill_color[] =
		  "profile_sidebar_fill_color";
		static inline constexpr char const profile_text_color[] =
		  "profile_text_color";
		static inline constexpr char const profile_use_background_image[] =
		  "profile_use_background_image";
		static inline constexpr char const default_profile[] = "default_profile";
		static inline constexpr char const default_profile_image[] =
		  "default_profile_image";
		static inline constexpr char const following[] = "following";
		static inline constexpr char const follow_request_sent[] =
		  "follow_request_sent";
		static inline constexpr char const notifications[] = "notifications";
		using type = json_member_list<
		  json_custom<id, std::string_view>,
		  json_string_raw<id_str, std::string_view>,
		  json_string_raw<name, std::string_view>,
		  json_string_raw<screen_name, std::string_view>,
		  json_string_raw<location, std::string_view>,
		  json_string_raw<description, std::string_view>,
		  json_string_raw_null<url, std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_class<entities, daw::twitter::entities_t>, json_bool<_jsonprotected>,
		  json_custom<followers_count, std::string_view>,
		  json_custom<friends_count, std::string_view>,
		  json_custom<listed_count, std::string_view>,
		  json_custom<created_at, std::string_view>,
		  json_custom<favourites_count, std::string_view>,
		  json_custom_null<utc_offset, std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<time_zone, std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_bool<geo_enabled>, json_bool<verified>,
		  json_custom<statuses_count, std::string_view>,
		  json_string_raw<lang, std::string_view>, json_bool<contributors_enabled>,
		  json_bool<is_translator>, json_bool<is_translation_enabled>,
		  json_string_raw<profile_background_color, std::string_view>,
		  json_string_raw<profile_background_image_url, std::string_view>,
		  json_string_raw<profile_background_image_url_https, std::string_view>,
		  json_bool<profile_background_tile>,
		  json_string_raw<profile_image_url, std::string_view>,
		  json_string_raw<profile_image_url_https, std::string_view>,
		  json_string_raw_null<profile_banner_url, std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_string_raw<profile_link_color, std::string_view>,
		  json_string_raw<profile_sidebar_border_color, std::string_view>,
		  json_string_raw<profile_sidebar_fill_color, std::string_view>,
		  json_string_raw<profile_text_color, std::string_view>,
		  json_bool<profile_use_background_image>, json_bool<default_profile>,
		  json_bool<default_profile_image>, json_bool<following>,
		  json_bool<follow_request_sent>, json_bool<notifications>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::user_t const &value ) {
			return std::forward_as_tuple(
			  value.id, value.id_str, value.name, value.screen_name, value.location,
			  value.description, value.url, value.entities, value._jsonprotected,
			  value.followers_count, value.friends_count, value.listed_count,
			  value.created_at, value.favourites_count, value.utc_offset,
			  value.time_zone, value.geo_enabled, value.verified,
			  value.statuses_count, value.lang, value.contributors_enabled,
			  value.is_translator, value.is_translation_enabled,
			  value.profile_background_color, value.profile_background_image_url,
			  value.profile_background_image_url_https, value.profile_background_tile,
			  value.profile_image_url, value.profile_image_url_https,
			  value.profile_banner_url, value.profile_link_color,
			  value.profile_sidebar_border_color, value.profile_sidebar_fill_color,
			  value.profile_text_color, value.profile_use_background_image,
			  value.default_profile, value.default_profile_image, value.following,
			  value.follow_request_sent, value.notifications );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::hashtags_element_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_string_raw<"text", std::string_view>,
		  json_array<"indices", json_custom<no_name, std::string_view>>>;
#else
		static inline constexpr char const text[] = "text";
		static inline constexpr char const indices[] = "indices";
		using type = json_member_list<
		  json_string_raw<text, std::string_view>,
		  json_array<indices, json_custom<no_name, std::string_view>>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::hashtags_element_t const &value ) {
			return std::forward_as_tuple( value.text, value.indices );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::tweet_object_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_class<"metadata", daw::twitter::metadata_t>,
		  json_custom<"created_at", std::string_view>,
		  json_custom<"id", std::string_view>,
		  json_string_raw<"id_str", std::string_view>,
		  json_string_raw<"text", std::string_view>,
		  json_string_raw<"source", std::string_view>, json_bool<"truncated">,
		  json_custom_null<"in_reply_to_status_id", std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<"in_reply_to_status_id_str",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_custom_null<"in_reply_to_user_id", std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<"in_reply_to_user_id_str",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_string_raw_null<"in_reply_to_screen_name",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_class<"user", daw::twitter::user_t>,
		  json_custom<"retweet_count", std::string_view>,
		  json_custom<"favorite_count", std::string_view>,
		  json_class<"entities", daw::twitter::entities_t>, json_bool<"favorited">,
		  json_bool<"retweeted">, json_bool_null<"possibly_sensitive">,
		  json_string_raw<"lang", std::string_view>>;
#else
		static inline constexpr char const metadata[] = "metadata";
		static inline constexpr char const created_at[] = "created_at";
		static inline constexpr char const id[] = "id";
		static inline constexpr char const id_str[] = "id_str";
		static inline constexpr char const text[] = "text";
		static inline constexpr char const source[] = "source";
		static inline constexpr char const truncated[] = "truncated";
		static inline constexpr char const in_reply_to_status_id[] =
		  "in_reply_to_status_id";
		static inline constexpr char const in_reply_to_status_id_str[] =
		  "in_reply_to_status_id_str";
		static inline constexpr char const in_reply_to_user_id[] =
		  "in_reply_to_user_id";
		static inline constexpr char const in_reply_to_user_id_str[] =
		  "in_reply_to_user_id_str";
		static inline constexpr char const in_reply_to_screen_name[] =
		  "in_reply_to_screen_name";
		static inline constexpr char const user[] = "user";
		static inline constexpr char const retweet_count[] = "retweet_count";
		static inline constexpr char const favorite_count[] = "favorite_count";
		static inline constexpr char const entities[] = "entities";
		static inline constexpr char const favorited[] = "favorited";
		static inline constexpr char const retweeted[] = "retweeted";
		static inline constexpr char const possibly_sensitive[] =
		  "possibly_sensitive";
		static inline constexpr char const lang[] = "lang";
		using type = json_member_list<
		  json_class<metadata, daw::twitter::metadata_t>,
		  json_custom<created_at, std::string_view>,
		  json_custom<id, std::string_view>,
		  json_string_raw<id_str, std::string_view>,
		  json_string_raw<text, std::string_view>,
		  json_string_raw<source, std::string_view>, json_bool<truncated>,
		  json_custom_null<in_reply_to_status_id, std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<in_reply_to_status_id_str,
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_custom_null<in_reply_to_user_id, std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<in_reply_to_user_id_str,
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_string_raw_null<in_reply_to_screen_name,
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_class<user, daw::twitter::user_t>,
		  json_custom<retweet_count, std::string_view>,
		  json_custom<favorite_count, std::string_view>,
		  json_class<entities, daw::twitter::entities_t>, json_bool<favorited>,
		  json_bool<retweeted>, json_bool_null<possibly_sensitive>,
		  json_string_raw<lang, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::tweet_object_t const &value ) {
			return std::forward_as_tuple(
			  value.metadata, value.created_at, value.id, value.id_str, value.text,
			  value.source, value.truncated, value.in_reply_to_status_id,
			  value.in_reply_to_status_id_str, value.in_reply_to_user_id,
			  value.in_reply_to_user_id_str, value.in_reply_to_screen_name,
			  value.user, value.retweet_count, value.favorite_count, value.entities,
			  value.favorited, value.retweeted, value.possibly_sensitive,
			  value.lang );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::user_mentions_element_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_string_raw<"screen_name", std::string_view>,
		  json_string_raw<"name", std::string_view>,
		  json_custom<"id", std::string_view>,
		  json_string_raw<"id_str", std::string_view>,
		  json_array<"indices", json_custom<no_name, std::string_view>>>;
#else
		static inline constexpr char const screen_name[] = "screen_name";
		static inline constexpr char const name[] = "name";
		static inline constexpr char const id[] = "id";
		static inline constexpr char const id_str[] = "id_str";
		static inline constexpr char const indices[] = "indices";
		using type = json_member_list<
		  json_string_raw<screen_name, std::string_view>,
		  json_string_raw<name, std::string_view>,
		  json_custom<id, std::string_view>,
		  json_string_raw<id_str, std::string_view>,
		  json_array<indices, json_custom<no_name, std::string_view>>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::user_mentions_element_t const &value ) {
			return std::forward_as_tuple( value.screen_name, value.name, value.id,
			                              value.id_str, value.indices );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::medium_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<json_custom<"w", std::string_view>,
		                              json_custom<"h", std::string_view>,
		                              json_string_raw<"resize", std::string_view>>;
#else
		static inline constexpr char const w[] = "w";
		static inline constexpr char const h[] = "h";
		static inline constexpr char const resize[] = "resize";
		using type = json_member_list<json_custom<w, std::string_view>,
		                              json_custom<h, std::string_view>,
		                              json_string_raw<resize, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::medium_t const &value ) {
			return std::forward_as_tuple( value.w, value.h, value.resize );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::small_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<json_custom<"w", std::string_view>,
		                              json_custom<"h", std::string_view>,
		                              json_string_raw<"resize", std::string_view>>;
#else
		static inline constexpr char const w[] = "w";
		static inline constexpr char const h[] = "h";
		static inline constexpr char const resize[] = "resize";
		using type = json_member_list<json_custom<w, std::string_view>,
		                              json_custom<h, std::string_view>,
		                              json_string_raw<resize, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::small_t const &value ) {
			return std::forward_as_tuple( value.w, value.h, value.resize );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::thumb_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<json_custom<"w", std::string_view>,
		                              json_custom<"h", std::string_view>,
		                              json_string_raw<"resize", std::string_view>>;
#else
		static inline constexpr char const w[] = "w";
		static inline constexpr char const h[] = "h";
		static inline constexpr char const resize[] = "resize";
		using type = json_member_list<json_custom<w, std::string_view>,
		                              json_custom<h, std::string_view>,
		                              json_string_raw<resize, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::thumb_t const &value ) {
			return std::forward_as_tuple( value.w, value.h, value.resize );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::large_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<json_custom<"w", std::string_view>,
		                              json_custom<"h", std::string_view>,
		                              json_string_raw<"resize", std::string_view>>;
#else
		static inline constexpr char const w[] = "w";
		static inline constexpr char const h[] = "h";
		static inline constexpr char const resize[] = "resize";
		using type = json_member_list<json_custom<w, std::string_view>,
		                              json_custom<h, std::string_view>,
		                              json_string_raw<resize, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::large_t const &value ) {
			return std::forward_as_tuple( value.w, value.h, value.resize );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::sizes_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<json_class<"medium", daw::twitter::medium_t>,
		                              json_class<"small", daw::twitter::small_t>,
		                              json_class<"thumb", daw::twitter::thumb_t>,
		                              json_class<"large", daw::twitter::large_t>>;
#else
		static inline constexpr char const medium[] = "medium";
		static inline constexpr char const small_[] = "small";
		static inline constexpr char const thumb[] = "thumb";
		static inline constexpr char const large[] = "large";
		using type = json_member_list<json_class<medium, daw::twitter::medium_t>,
		                              json_class<small_, daw::twitter::small_t>,
		                              json_class<thumb, daw::twitter::thumb_t>,
		                              json_class<large, daw::twitter::large_t>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::sizes_t const &value ) {
			return std::forward_as_tuple( value.medium, value.small_, value.thumb,
			                              value.large );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::media_element_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_custom<"id", std::string_view>,
		  json_string_raw<"id_str", std::string_view>,
		  json_array<"indices", json_custom<no_name, std::string_view>>,
		  json_string_raw<"media_url", std::string_view>,
		  json_string_raw<"media_url_https", std::string_view>,
		  json_string_raw<"url", std::string_view>,
		  json_string_raw<"display_url", std::string_view>,
		  json_string_raw<"expanded_url", std::string_view, std::string_view>,
		  json_string_raw<"type", std::string_view>,
		  json_class<"sizes", daw::twitter::sizes_t>>;
#else
		static inline constexpr char const id[] = "id";
		static inline constexpr char const id_str[] = "id_str";
		static inline constexpr char const indices[] = "indices";
		static inline constexpr char const media_url[] = "media_url";
		static inline constexpr char const media_url_https[] = "media_url_https";
		static inline constexpr char const url[] = "url";
		static inline constexpr char const display_url[] = "display_url";
		static inline constexpr char const expanded_url[] = "expanded_url";
		static inline constexpr char const _jsontype[] = "type";
		static inline constexpr char const sizes[] = "sizes";
		using type = json_member_list<
		  json_custom<id, std::string_view>,
		  json_string_raw<id_str, std::string_view>,
		  json_array<indices, json_custom<no_name, std::string_view>>,
		  json_string_raw<media_url, std::string_view>,
		  json_string_raw<media_url_https, std::string_view>,
		  json_string_raw<url, std::string_view>,
		  json_string_raw<display_url, std::string_view>,
		  json_string_raw<expanded_url, std::string_view>,
		  json_string_raw<_jsontype, std::string_view>,
		  json_class<sizes, daw::twitter::sizes_t>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::media_element_t const &value ) {
			return std::forward_as_tuple(
			  value.id, value.id_str, value.indices, value.media_url,
			  value.media_url_https, value.url, value.display_url, value.expanded_url,
			  value.type, value.sizes );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::retweeted_status_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_class<"metadata", daw::twitter::metadata_t>,
		  json_custom<"created_at", std::string_view>,
		  json_custom<"id", std::string_view>,
		  json_string_raw<"id_str", std::string_view>,
		  json_string_raw<"text", std::string_view>,
		  json_string_raw<"source", std::string_view>, json_bool<"truncated">,
		  json_custom_null<"in_reply_to_status_id", std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<"in_reply_to_status_id_str",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_custom_null<"in_reply_to_user_id", std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<"in_reply_to_user_id_str",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_string_raw_null<"in_reply_to_screen_name",
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_class<"user", daw::twitter::user_t>,
		  json_custom<"retweet_count", std::string_view>,
		  json_custom<"favorite_count", std::string_view>,
		  json_class<"entities", daw::twitter::entities_t>, json_bool<"favorited">,
		  json_bool<"retweeted">, json_bool_null<"possibly_sensitive">,
		  json_string_raw<"lang", std::string_view>>;
#else
		static inline constexpr char const metadata[] = "metadata";
		static inline constexpr char const created_at[] = "created_at";
		static inline constexpr char const id[] = "id";
		static inline constexpr char const id_str[] = "id_str";
		static inline constexpr char const text[] = "text";
		static inline constexpr char const source[] = "source";
		static inline constexpr char const truncated[] = "truncated";
		static inline constexpr char const in_reply_to_status_id[] =
		  "in_reply_to_status_id";
		static inline constexpr char const in_reply_to_status_id_str[] =
		  "in_reply_to_status_id_str";
		static inline constexpr char const in_reply_to_user_id[] =
		  "in_reply_to_user_id";
		static inline constexpr char const in_reply_to_user_id_str[] =
		  "in_reply_to_user_id_str";
		static inline constexpr char const in_reply_to_screen_name[] =
		  "in_reply_to_screen_name";
		static inline constexpr char const user[] = "user";
		static inline constexpr char const retweet_count[] = "retweet_count";
		static inline constexpr char const favorite_count[] = "favorite_count";
		static inline constexpr char const entities[] = "entities";
		static inline constexpr char const favorited[] = "favorited";
		static inline constexpr char const retweeted[] = "retweeted";
		static inline constexpr char const possibly_sensitive[] =
		  "possibly_sensitive";
		static inline constexpr char const lang[] = "lang";
		using type = json_member_list<
		  json_class<metadata, daw::twitter::metadata_t>,
		  json_custom<created_at, std::string_view>,
		  json_custom<id, std::string_view>,
		  json_string_raw<id_str, std::string_view>,
		  json_string_raw<text, std::string_view>,
		  json_string_raw<source, std::string_view>, json_bool<truncated>,
		  json_custom_null<in_reply_to_status_id, std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<in_reply_to_status_id_str,
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_custom_null<in_reply_to_user_id, std::optional<std::string_view>,
		                   opt_construct_a<std::string_view>>,
		  json_string_raw_null<in_reply_to_user_id_str,
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_string_raw_null<in_reply_to_screen_name,
		                       std::optional<std::string_view>,
		                       opt_construct_a<std::string_view>>,
		  json_class<user, daw::twitter::user_t>,
		  json_custom<retweet_count, std::string_view>,
		  json_custom<favorite_count, std::string_view>,
		  json_class<entities, daw::twitter::entities_t>, json_bool<favorited>,
		  json_bool<retweeted>, json_bool_null<possibly_sensitive>,
		  json_string_raw<lang, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::retweeted_status_t const &value ) {
			return std::forward_as_tuple(
			  value.metadata, value.created_at, value.id, value.id_str, value.text,
			  value.source, value.truncated, value.in_reply_to_status_id,
			  value.in_reply_to_status_id_str, value.in_reply_to_user_id,
			  value.in_reply_to_user_id_str, value.in_reply_to_screen_name,
			  value.user, value.retweet_count, value.favorite_count, value.entities,
			  value.favorited, value.retweeted, value.possibly_sensitive,
			  value.lang );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::search_metadata_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type =
		  json_member_list<json_custom<"completed_in", std::string_view>,
		                   json_custom<"max_id", std::string_view>,
		                   json_string_raw<"max_id_str", std::string_view>,
		                   json_string_raw<"next_results", std::string_view>,
		                   json_string_raw<"query", std::string_view>,
		                   json_string_raw<"refresh_url", std::string_view>,
		                   json_custom<"count", std::string_view>,
		                   json_custom<"since_id", std::string_view>,
		                   json_string_raw<"since_id_str", std::string_view>>;
#else
		static inline constexpr char const completed_in[] = "completed_in";
		static inline constexpr char const max_id[] = "max_id";
		static inline constexpr char const max_id_str[] = "max_id_str";
		static inline constexpr char const next_results[] = "next_results";
		static inline constexpr char const query[] = "query";
		static inline constexpr char const refresh_url[] = "refresh_url";
		static inline constexpr char const count[] = "count";
		static inline constexpr char const since_id[] = "since_id";
		static inline constexpr char const since_id_str[] = "since_id_str";
		using type =
		  json_member_list<json_custom<completed_in, std::string_view>,
		                   json_custom<max_id, std::string_view>,
		                   json_string_raw<max_id_str, std::string_view>,
		                   json_string_raw<next_results, std::string_view>,
		                   json_string_raw<query, std::string_view>,
		                   json_string_raw<refresh_url, std::string_view>,
		                   json_custom<count, std::string_view>,
		                   json_custom<since_id, std::string_view>,
		                   json_string_raw<since_id_str, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::search_metadata_t const &value ) {
			return std::forward_as_tuple( value.completed_in, value.max_id,
			                              value.max_id_str, value.next_results,
			                              value.query, value.refresh_url, value.count,
			                              value.since_id, value.since_id_str );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::twitter::twitter_object_t> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_array<"statuses", daw::twitter::tweet_object_t>,
		  json_class<"search_metadata", daw::twitter::search_metadata_t>>;
#else
		static inline constexpr char const statuses[] = "statuses";
		static inline constexpr char const search_metadata[] = "search_metadata";
		using type = json_member_list<
		  json_array<statuses, daw::twitter::tweet_object_t>,
		  json_class<search_metadata, daw::twitter::search_metadata_t>>;
#endif
		[[nodiscard, maybe_unused]] static inline auto
		to_json_data( daw::twitter::twitter_object_t const &value ) {
			return std::forward_as_tuple( value.statuses, value.search_metadata );
		}
	};
} // namespace daw::json
