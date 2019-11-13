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

#include <cstdio>
#include <cstdlib>

#include <daw/json/daw_json_link.h>
#include <daw/json/impl/daw_memory_mapped.h>

template<typename Key, typename Value>
struct KVPair : std::pair<Key, Value> {
	using std::pair<Key, Value>::pair;

	constexpr operator std::pair<Key, Value>( ) const {
		return {this->first, this->last};
	}
};

#if defined( __cpp_nontype_template_parameter_class )
template<typename Key, typename Value>
auto describe_json_class( KVPair<Key, Value> ) {
	using namespace daw::json;
	return class_description_t<json_number<"key", Key>,
	                           json_string<"value", Value>>{};
}
#else
namespace symbols_KVPair {
	static constexpr char const key[] = "key";
	static constexpr char const value[] = "value";
} // namespace symbols_KVPair
template<typename Key, typename Value>
auto describe_json_class( KVPair<Key, Value> ) {
	using namespace daw::json;
	return class_description_t<json_number<symbols_KVPair::key, Key>,
	                           json_string<symbols_KVPair::value, Value>>{};
}
#endif
template<typename Key, typename Value>
auto to_json_data( KVPair<Key, Value> const &value ) {
	return std::forward_as_tuple( value.first, value.second );
}

struct MyKeyValue2 {
	std::unordered_map<intmax_t, std::string> kv;
};

#if defined( __cpp_nontype_template_parameter_class )
auto describe_json_class( MyKeyValue2 ) {
	using namespace daw::json;
	return class_description_t<
	  json_array<"kv", std::unordered_map<intmax_t, std::string>,
	             json_class<no_name, KVPair<intmax_t, std::string>>>>{};
}
#else
namespace symbols_MyKeyValue2 {
	static constexpr char const kv[] = "kv";
}
auto describe_json_class( MyKeyValue2 ) {
	using namespace daw::json;
	return class_description_t<json_array<
	  symbols_MyKeyValue2::kv, std::unordered_map<intmax_t, std::string>,
	  json_class<no_name, KVPair<intmax_t, std::string>>>>{};
}
#endif
auto to_json_data( MyKeyValue2 const &value ) {
	return std::forward_as_tuple( value.kv );
}

int main( int argc, char **argv ) {
	if( argc <= 1 ) {
		puts( "Must supply path to cookbook_kv2.json file\n" );
		exit( EXIT_FAILURE );
	}
	auto data = daw::memory_mapped_file<>( argv[1] );

	auto kv = daw::json::from_json<MyKeyValue2>(
	  std::string_view( data.data( ), data.size( ) ) );

	daw::json::json_assert( kv.kv.size( ) == 2, "Expected data to have 2 items" );
	daw::json::json_assert( kv.kv[0] == "test_001", "Unexpected value" );
	daw::json::json_assert( kv.kv[1] == "test_002", "Unexpected value" );
}