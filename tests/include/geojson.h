// Copyright (c) Darrell Wright
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/beached/daw_json_link
//

#pragma once

#include "defines.h"

#include <daw/json/daw_json_link.h>

#include <array>
#include <cstdint>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

#ifdef __GNUC__
#define DAW_HIDDEN __attribute__( ( visibility( "hidden" ) ) )
#else
#define DAW_HIDDEN
#endif

namespace daw::geojson {
	struct Property {
		std::string_view name;
	}; // Property

	struct Point {
		double x;
		double y;
	};

	struct Polygon {
		std::string_view type;
		std::vector<std::vector<Point>> coordinates;

		Polygon( std::string_view t, std::vector<std::vector<Point>> &&coords )
		  : type( t )
		  , coordinates( std::move( coords ) ) {}
	}; // Polygon

	struct Feature {
		std::string_view type;
		Property properties;
		Polygon geometry;
	}; // Feature

	struct FeatureCollection {
		std::string_view type;
		std::vector<Feature> features;
	}; // FeatureCollection

	template<typename T>
	struct array_appender {
		T *ptr;

		template<size_t N>
		explicit DAW_CONSTEXPR array_appender( std::array<T, N> &ary ) noexcept
		  : ptr( ary.data( ) ) {}

		template<typename U>
		DAW_CONSTEXPR void operator( )( U &&item ) noexcept {
			*ptr++ = std::forward<U>( item );
		}
	};
} // namespace daw::geojson

namespace daw::json {
	template<>
	struct DAW_HIDDEN json_data_contract<daw::geojson::Point> {
		using type = json_ordered_member_list<double, double>;

		[[nodiscard, maybe_unused]] static DAW_CONSTEXPR auto
		to_json_data( daw::geojson::Point const &p ) {
			return std::forward_as_tuple( p.x, p.y );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::geojson::Property> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<json_string_raw<"name", std::string_view>>;
#else
		static constexpr char const type_sym[] = "type";
		static constexpr char const name[] = "name";
		using type = json_member_list<json_string_raw<name, std::string_view>>;
#endif
		[[nodiscard, maybe_unused]] static DAW_CONSTEXPR auto
		to_json_data( daw::geojson::Property const &value ) {
			return std::forward_as_tuple( value.name );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::geojson::Polygon> {
#ifdef __cpp_nontype_template_parameter_class
		using type = json_member_list<
		  json_string_raw<"type", std::string_view>,
		  json_array<"coordinates", std::vector<daw::geojson::Point>>>;
#else
		static constexpr char const type_sym[] = "type";
		static constexpr char const coordinates[] = "coordinates";
		using type = json_member_list<
		  json_string_raw<type_sym, std::string_view>,
		  json_array<coordinates, std::vector<daw::geojson::Point>>>;
#endif

		[[nodiscard, maybe_unused]] static DAW_CONSTEXPR auto
		to_json_data( daw::geojson::Polygon const &value ) {
			return std::forward_as_tuple( value.type, value.coordinates );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::geojson::Feature> {
#ifdef __cpp_nontype_template_parameter_class
		using type =
		  json_member_list<json_string_raw<"type", std::string_view>,
		                   json_class<"properties", daw::geojson::Property>,
		                   json_class<"geometry", daw::geojson::Polygon>>;
#else
		static constexpr char const type_sym[] = "type";
		static constexpr char const properties[] = "properties";
		static constexpr char const geometry[] = "geometry";
		using type =
		  json_member_list<json_string_raw<type_sym, std::string_view>,
		                   json_class<properties, daw::geojson::Property>,
		                   json_class<geometry, daw::geojson::Polygon>>;
#endif
		[[nodiscard, maybe_unused]] static DAW_CONSTEXPR auto
		to_json_data( daw::geojson::Feature const &value ) {
			return std::forward_as_tuple( value.type, value.properties,
			                              value.geometry );
		}
	};

	template<>
	struct DAW_HIDDEN json_data_contract<daw::geojson::FeatureCollection> {
#ifdef __cpp_nontype_template_parameter_class
		using type =
		  json_member_list<json_string_raw<"type", std::string_view>,
		                   json_array<"features", daw::geojson::Feature>>;
#else
		static constexpr char const type_sym[] = "type";
		static constexpr char const features[] = "features";
		using type = json_member_list<json_string_raw<type_sym, std::string_view>,
		                              json_array<features, daw::geojson::Feature>>;
#endif
		[[nodiscard, maybe_unused]] static DAW_CONSTEXPR auto
		to_json_data( daw::geojson::FeatureCollection const &value ) {
			return std::forward_as_tuple( value.type, value.features );
		}
	};
} // namespace daw::json
