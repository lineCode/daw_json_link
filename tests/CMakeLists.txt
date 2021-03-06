# TODO clean this up, but for now it makes tests get approprait options

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF CACHE STRING "Enable LTO")
if (CMAKE_INTERPROCEDURAL_OPTIMIZATION)
  message("CMAKE_INTERPROCEDURAL_OPTIMIZATION=ON: LTO is enabled")
endif ()
message("CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")

set(DAW_NUM_RUNS OFF CACHE STRING "Enable address and undefined behaviour sanitizers")
if (DAW_NUM_RUNS)
  message("DAW_NUM_RUNS=${DAW_NUM_RUNS}: Overriding number of test runs")
  add_definitions(-DDAW_NUM_RUNS=${DAW_NUM_RUNS})
endif ()
set(DAW_JSON_USE_SANITIZERS OFF CACHE STRING "Enable address and undefined behaviour sanitizers")
if (DAW_JSON_USE_SANITIZERS)
  message("DAW_JSON_USE_SANITIZERS=ON: compiler sanitizers enabled")
  add_definitions(-DDAW_JSON_NO_INT128)
else ()
  message("DAW_JSON_USE_SANITIZERS=OFF: compiler sanitizers disabled")
endif ()

include(cmake/test_compiler_options.cmake)

add_library(json_test INTERFACE)
target_link_libraries(json_test INTERFACE daw::json_link daw::header_libraries daw::utf_range ${COMPILER_SPECIFIC_LIBS})
target_include_directories( json_test INTERFACE include/ )

add_custom_target(full)

add_executable(daw_json_link_test src/daw_json_link_test.cpp)
target_link_libraries(daw_json_link_test json_test)
add_test(NAME daw_json_link_test COMMAND daw_json_link_test)
add_dependencies(full daw_json_link_test)

add_executable(city_test src/city_test.cpp)
target_link_libraries(city_test json_test)
#add_test( NAME city_test COMMAND city_test)
add_dependencies(full city_test)

add_executable(int_array_test src/int_array_test.cpp)
target_link_libraries(int_array_test json_test)
add_test(NAME int_array_test COMMAND int_array_test)
add_dependencies(full int_array_test)

add_executable(int_array_basic_test src/int_array_basic_test.cpp)
target_link_libraries(int_array_basic_test json_test)
add_test(NAME int_array_basic_test COMMAND int_array_basic_test)
add_dependencies(full int_array_basic_test)

add_executable(float_array_test src/float_array_test.cpp)
target_link_libraries(float_array_test json_test)
add_test(NAME float_array_test COMMAND float_array_test)
add_dependencies(full float_array_test)

add_executable(float_array_basic_test src/float_array_basic_test.cpp)
target_link_libraries(float_array_basic_test json_test)
add_test(NAME float_array_basic_test COMMAND float_array_basic_test)
add_dependencies(full float_array_basic_test)

add_executable(simple_test src/simple_test.cpp)
target_link_libraries(simple_test json_test)
#add_test( NAME simple_test COMMAND simple_test)
add_dependencies(full simple_test)

add_executable(coords_test src/coords_test.cpp)
target_link_libraries(coords_test json_test)
#add_test( NAME coords_test COMMAND coords_test)
add_dependencies(full coords_test)

if (NOT DEFINED MSVC)
	add_executable(kostya_bench src/kostya_bench.cpp)
	target_link_libraries(kostya_bench json_test)
	#add_test( NAME kostya_bench COMMAND kostya_bench)
	add_dependencies(full kostya_bench)

	add_executable(kostya_bench2 src/kostya_bench2.cpp)
	target_link_libraries(kostya_bench2 json_test)
	#add_test( NAME kostya_bench2 COMMAND kostya_bench2)
	add_dependencies(full kostya_bench2)

	add_executable(kostya_bench3 src/kostya_bench3.cpp)
	target_link_libraries(kostya_bench3 json_test)
	#add_test( NAME kostya_bench3 COMMAND kostya_bench3)
	add_dependencies(full kostya_bench3)
endif ()

add_executable(coords_test2 src/coords_test2.cpp)
target_link_libraries(coords_test2 json_test)
#add_test( NAME coords_test2 COMMAND coords_test2)
add_dependencies(full coords_test2)

add_executable(nativejson_bench src/nativejson_bench.cpp)
target_link_libraries(nativejson_bench json_test)
add_test(NAME nativejson_bench COMMAND nativejson_bench ./twitter.json ./citm_catalog.json ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full nativejson_bench)

add_executable( nativejson_bench_alloc EXCLUDE_FROM_ALL src/nativejson_bench_alloc.cpp)
target_link_libraries(nativejson_bench_alloc json_test)
add_dependencies(full nativejson_bench_alloc)

add_executable(nativejson_bench2 src/nativejson_bench2.cpp)
target_link_libraries(nativejson_bench2 json_test)
add_test(NAME nativejson_bench2 COMMAND nativejson_bench2 ./twitter.json ./citm_catalog.json ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full nativejson_bench2)

add_executable(nativejson_bench_basic src/nativejson_bench_basic.cpp)
target_link_libraries(nativejson_bench_basic json_test)
add_test(NAME nativejson_bench_basic COMMAND nativejson_bench_basic ./twitter.json ./citm_catalog.json ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full nativejson_bench_basic)

add_executable(nativejson_bench_basic2 src/nativejson_bench_basic2.cpp)
target_link_libraries(nativejson_bench_basic2 json_test)
add_test(NAME nativejson_bench_basic2 COMMAND nativejson_bench_basic2 ./twitter.json ./citm_catalog.json ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full nativejson_bench_basic2)

add_executable(citm_test src/citm_test.cpp)
target_link_libraries(citm_test json_test)
add_test(NAME citm_test COMMAND citm_test ./citm_catalog.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full citm_test)

add_executable(citm_test_alloc EXCLUDE_FROM_ALL src/citm_test_alloc.cpp)
target_link_libraries(citm_test_alloc json_test)
add_dependencies(full citm_test_alloc)

add_executable(citm_test_basic src/citm_test_basic.cpp)
target_link_libraries(citm_test_basic json_test)
add_test(NAME citm_test_basic COMMAND citm_test_basic ./citm_catalog.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full citm_test_basic)

add_executable(twitter_test src/twitter_test.cpp)
target_link_libraries(twitter_test json_test)
add_test(NAME twitter_test COMMAND twitter_test ./twitter.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full twitter_test)

add_executable(twitter_test_alloc EXCLUDE_FROM_ALL src/twitter_test_alloc.cpp)
target_link_libraries(twitter_test_alloc json_test)
add_dependencies(full twitter_test_alloc)

add_executable(twitter_test2 src/twitter_test2.cpp)
target_link_libraries(twitter_test2 json_test)
add_test(NAME twitter_test2 COMMAND twitter_test2 ./twitter.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full twitter_test2)

add_executable(twitter_test_basic src/twitter_test_basic.cpp)
target_link_libraries(twitter_test_basic json_test)
add_test(NAME twitter_test_basic COMMAND twitter_test_basic ./twitter.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full twitter_test_basic)

add_executable(twitter_test_basic2 src/twitter_test_basic2.cpp)
target_link_libraries(twitter_test_basic2 json_test)
add_test(NAME twitter_test_basic2 COMMAND twitter_test_basic2 ./twitter.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full twitter_test_basic2)

add_executable(twitter_timeline_test src/twitter_timeline_test.cpp)
target_link_libraries(twitter_timeline_test json_test)
add_test(NAME twitter_timeline_test COMMAND twitter_timeline_test ./twitter_timeline.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full twitter_timeline_test)

add_executable(canada_test src/canada_test.cpp)
target_link_libraries(canada_test json_test)
add_test(NAME canada_test COMMAND canada_test ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full canada_test)

add_executable(canada_test_alloc EXCLUDE_FROM_ALL src/canada_test_alloc.cpp)
target_link_libraries(canada_test_alloc json_test)
add_dependencies(full canada_test_alloc)

add_executable(canada_test_basic src/canada_test_basic.cpp)
target_link_libraries(canada_test_basic json_test)
add_test(NAME canada_test_basic COMMAND canada_test_basic ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full canada_test_basic)

add_executable(kv_map_test src/kv_map_test.cpp)
target_link_libraries( kv_map_test json_test)
add_test(NAME kv_map_test COMMAND kv_map_test)
add_dependencies(full kv_map_test)

add_executable(cookbook_kv1_test src/cookbook_kv1_test.cpp)
target_link_libraries( cookbook_kv1_test json_test)
add_test(NAME cookbook_kv1_test COMMAND cookbook_kv1_test ./cookbook_kv1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_kv1_test)

add_executable(cookbook_kv2_test src/cookbook_kv2_test.cpp)
target_link_libraries( cookbook_kv2_test json_test)
add_test(NAME cookbook_kv2_test COMMAND cookbook_kv2_test ./cookbook_kv2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_kv2_test)

add_executable(cookbook_kv3_test src/cookbook_kv3_test.cpp)
target_link_libraries( cookbook_kv3_test json_test)
add_test(NAME cookbook_kv3_test COMMAND cookbook_kv3_test ./cookbook_kv3.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_kv3_test)

add_executable(cookbook_kv4_test src/cookbook_kv4_test.cpp)
target_link_libraries( cookbook_kv4_test json_test)
add_test(NAME cookbook_kv4_test COMMAND cookbook_kv4_test ./cookbook_kv4.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_kv4_test)

add_executable(cookbook_class1_test src/cookbook_class1_test.cpp)
target_link_libraries( cookbook_class1_test json_test)
add_test(NAME cookbook_class1_test COMMAND cookbook_class1_test ./cookbook_class1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_class1_test)

add_executable(cookbook_class2_test src/cookbook_class2_test.cpp)
target_link_libraries( cookbook_class2_test json_test)
add_test(NAME cookbook_class2_test COMMAND cookbook_class2_test ./cookbook_class2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_class2_test)

add_executable(cookbook_class3_test src/cookbook_class3_test.cpp)
target_link_libraries( cookbook_class3_test json_test)
add_test(NAME cookbook_class3_test COMMAND cookbook_class3_test ./cookbook_class3.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_class3_test)

add_executable(cookbook_array1_test src/cookbook_array1_test.cpp)
target_link_libraries( cookbook_array1_test json_test)
add_test(NAME cookbook_array1_test COMMAND cookbook_array1_test ./cookbook_array1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_array1_test)

add_executable(cookbook_array2_test src/cookbook_array2_test.cpp)
target_link_libraries( cookbook_array2_test json_test)
add_test(NAME cookbook_array2_test COMMAND cookbook_array2_test ./cookbook_array2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_array2_test)

add_executable(cookbook_array3_test src/cookbook_array3_test.cpp)
target_link_libraries( cookbook_array3_test json_test)
add_test(NAME cookbook_array3_test COMMAND cookbook_array3_test ./cookbook_array3.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_array3_test)

add_executable(cookbook_escaped_strings1_test src/cookbook_escaped_strings1_test.cpp)
target_link_libraries( cookbook_escaped_strings1_test json_test)
add_test(NAME cookbook_escaped_strings1_test COMMAND cookbook_escaped_strings1_test ./cookbook_escaped_strings1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_escaped_strings1_test)

add_executable(full_unicode_roundtrip_test src/full_unicode_roundtrip_test.cpp)
target_link_libraries( full_unicode_roundtrip_test json_test)
add_test(NAME full_unicode_roundtrip_test COMMAND full_unicode_roundtrip_test ./full_unicode.json ./full_unicode_escaped.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full full_unicode_roundtrip_test)

add_executable(make_full24 src/make_full24.cpp)
target_link_libraries( make_full24 json_test)
add_dependencies(full make_full24)

add_executable(cookbook_enums1_test src/cookbook_enums1_test.cpp)
target_link_libraries( cookbook_enums1_test json_test)
add_test(NAME cookbook_enums1_test COMMAND cookbook_enums1_test ./cookbook_enums1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_enums1_test)

add_executable(cookbook_enums2_test src/cookbook_enums2_test.cpp)
target_link_libraries( cookbook_enums2_test json_test)
add_test(NAME cookbook_enums2_test COMMAND cookbook_enums2_test ./cookbook_enums2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_enums2_test)

add_executable(cookbook_graphs1_test src/cookbook_graphs1_test.cpp)
target_link_libraries( cookbook_graphs1_test json_test)
add_test(NAME cookbook_graphs1_test COMMAND cookbook_graphs1_test ./cookbook_graphs1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_graphs1_test)

add_executable(cookbook_optional_values1_test src/cookbook_optional_values1_test.cpp)
target_link_libraries( cookbook_optional_values1_test json_test)
add_test(NAME cookbook_optional_values1_test COMMAND cookbook_optional_values1_test ./cookbook_optional_values1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_optional_values1_test)

add_executable(cookbook_variant1_test src/cookbook_variant1_test.cpp)
target_link_libraries( cookbook_variant1_test json_test)
add_test(NAME cookbook_variant1_test COMMAND cookbook_variant1_test ./cookbook_variant1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_variant1_test)

add_executable(small_test src/small_test.cpp)
target_link_libraries( small_test json_test)
add_test(NAME small_test COMMAND small_test ./small_test.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full small_test)

add_executable(should_fail src/should_fail_001.cpp)
target_link_libraries( should_fail json_test)
add_test(should_fail_test should_fail)
add_dependencies(full should_fail)

add_executable(trailing_commas src/trailing_commas.cpp)
target_link_libraries( trailing_commas json_test)
add_test(trailing_commas_test trailing_commas)
add_dependencies(full trailing_commas)

add_executable(cookbook_parsing_individual_members1_test src/cookbook_parsing_individual_members1_test.cpp)
target_link_libraries(cookbook_parsing_individual_members1_test json_test)
add_test(NAME cookbook_parsing_individual_members1_test COMMAND cookbook_parsing_individual_members1_test ./cookbook_parsing_individual_members1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_parsing_individual_members1_test)

add_executable(cookbook_parsing_individual_members2_test src/cookbook_parsing_individual_members2_test.cpp)
target_link_libraries(cookbook_parsing_individual_members2_test json_test)
add_test(NAME cookbook_parsing_individual_members2_test COMMAND cookbook_parsing_individual_members2_test ./cookbook_parsing_individual_members2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_parsing_individual_members2_test)

add_executable(cookbook_parsing_individual_members3_test src/cookbook_parsing_individual_members3_test.cpp)
target_link_libraries(cookbook_parsing_individual_members3_test json_test)
add_test(NAME cookbook_parsing_individual_members3_test COMMAND cookbook_parsing_individual_members3_test ./cookbook_parsing_individual_members3.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_parsing_individual_members3_test)

add_executable(cookbook_variant2_test src/cookbook_variant2_test.cpp)
target_link_libraries(cookbook_variant2_test json_test)
add_test(NAME cookbook_variant2_test COMMAND cookbook_variant2_test ./cookbook_variant2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_variant2_test)

add_executable(cookbook_variant3_test src/cookbook_variant3_test.cpp)
target_link_libraries(cookbook_variant3_test json_test)
add_test(NAME cookbook_variant3_test COMMAND cookbook_variant3_test ./cookbook_variant3.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_variant3_test)

add_executable(optional_tagged_variant_test src/optional_tagged_variant_test.cpp)
target_link_libraries(optional_tagged_variant_test json_test)
add_test(NAME optional_tagged_variant_test COMMAND optional_tagged_variant_test ./optional_tagged_variant.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full optional_tagged_variant_test)

add_executable(optional_variant_test src/optional_variant_test.cpp)
target_link_libraries(optional_variant_test json_test)
add_test(NAME optional_variant_test COMMAND optional_variant_test ./optional_variant.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full optional_variant_test)

add_executable(daw_murmur3_test src/daw_murmur3_test.cpp)
target_link_libraries(daw_murmur3_test json_test)
add_test(NAME daw_murmur3_test COMMAND daw_murmur3_test)
add_dependencies(full daw_murmur3_test)

add_executable(apache_builds_test src/apache_builds_test.cpp)
target_link_libraries(apache_builds_test json_test)
add_test(NAME apache_builds_test COMMAND apache_builds_test ./apache_builds.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full apache_builds_test)

add_executable(apache_builds_cpp_comments_test src/apache_builds_cpp_comments_test.cpp)
target_link_libraries(apache_builds_cpp_comments_test json_test)
add_test(NAME apache_builds_cpp_comments_test COMMAND apache_builds_cpp_comments_test ./apache_builds_cpp_comments.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full apache_builds_cpp_comments_test)

add_executable(apache_builds_hash_comments_test src/apache_builds_hash_comments_test.cpp)
target_link_libraries(apache_builds_hash_comments_test json_test)
add_test(NAME apache_builds_hash_comments_test COMMAND apache_builds_hash_comments_test ./apache_builds_hash_comments.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full apache_builds_hash_comments_test)

add_executable(cookbook_dates1_test src/cookbook_dates1_test.cpp)
target_link_libraries(cookbook_dates1_test json_test)
add_test(NAME cookbook_dates1_test COMMAND cookbook_dates1_test ./cookbook_dates1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_dates1_test)

add_executable(cookbook_dates2_test src/cookbook_dates2_test.cpp)
target_link_libraries(cookbook_dates2_test json_test)
add_test(NAME cookbook_dates2_test COMMAND cookbook_dates2_test ./cookbook_dates2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_dates2_test)

add_executable(cookbook_dates3_test src/cookbook_dates3_test.cpp)
target_link_libraries(cookbook_dates3_test json_test)
add_test(NAME cookbook_dates3_test COMMAND cookbook_dates3_test ./cookbook_dates3.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_dates3_test)

add_executable(cookbook_dates4_test src/cookbook_dates4_test.cpp)
target_link_libraries(cookbook_dates4_test json_test)
add_test(NAME cookbook_dates4_test COMMAND cookbook_dates4_test ./cookbook_dates4.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_dates4_test)

add_executable(no_move_or_copy_cls_test src/no_move_or_copy_cls_test.cpp)
target_link_libraries(no_move_or_copy_cls_test json_test)
add_test(NAME no_move_or_copy_cls_test COMMAND no_move_or_copy_cls_test)
add_dependencies(full no_move_or_copy_cls_test)

add_executable(cookbook_class_from_array1_test src/cookbook_class_from_array1_test.cpp)
target_link_libraries(cookbook_class_from_array1_test json_test)
add_test(NAME cookbook_class_from_array1_test COMMAND cookbook_class_from_array1_test ./cookbook_class_from_array1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_class_from_array1_test)

add_executable(cookbook_class_from_array2_test src/cookbook_class_from_array2_test.cpp)
target_link_libraries(cookbook_class_from_array2_test json_test)
add_test(NAME cookbook_class_from_array2_test COMMAND cookbook_class_from_array2_test ./cookbook_class_from_array2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_class_from_array2_test)

add_executable(cookbook_numbers1_test src/cookbook_numbers1_test.cpp)
target_link_libraries(cookbook_numbers1_test json_test)
add_test(NAME cookbook_numbers1_test COMMAND cookbook_numbers1_test ./cookbook_numbers1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_numbers1_test)

add_executable(cookbook_numbers2_test src/cookbook_numbers2_test.cpp)
target_link_libraries(cookbook_numbers2_test json_test)
add_test(NAME cookbook_numbers2_test COMMAND cookbook_numbers2_test ./cookbook_numbers2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_numbers2_test)

add_executable(cookbook_unknown_types_and_delayed_parsing1_test src/cookbook_unknown_types_and_delayed_parsing1_test.cpp)
target_link_libraries(cookbook_unknown_types_and_delayed_parsing1_test json_test)
add_test(NAME cookbook_unknown_types_and_delayed_parsing1_test COMMAND cookbook_unknown_types_and_delayed_parsing1_test ./cookbook_unknown_types_and_delayed_parsing1.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_unknown_types_and_delayed_parsing1_test)

add_executable(cookbook_unknown_types_and_delayed_parsing2_test src/cookbook_unknown_types_and_delayed_parsing2_test.cpp)
target_link_libraries(cookbook_unknown_types_and_delayed_parsing2_test json_test)
add_test(NAME cookbook_unknown_types_and_delayed_parsing2_test COMMAND cookbook_unknown_types_and_delayed_parsing2_test ./cookbook_unknown_types_and_delayed_parsing2.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full cookbook_unknown_types_and_delayed_parsing2_test)

add_executable(cookbook_unknown_types_and_delayed_parsing3_test src/cookbook_unknown_types_and_delayed_parsing3_test.cpp)
target_link_libraries(cookbook_unknown_types_and_delayed_parsing3_test json_test)
add_test(NAME cookbook_unknown_types_and_delayed_parsing3_test COMMAND cookbook_unknown_types_and_delayed_parsing3_test )
add_dependencies(full cookbook_unknown_types_and_delayed_parsing3_test)

add_executable(stream_output_test src/stream_output_test.cpp)
target_link_libraries(stream_output_test json_test)
add_test(NAME stream_output_test COMMAND stream_output_test)
add_dependencies(full stream_output_test)

add_executable(int_sanity_test src/int_sanity_test.cpp)
target_link_libraries(int_sanity_test json_test)
add_test(NAME int_sanity_test COMMAND int_sanity_test)
add_dependencies(full int_sanity_test)

add_executable(nativejson_roundtrip src/nativejson_roundtrip.cpp)
target_link_libraries(nativejson_roundtrip json_test)
add_test(NAME nativejson_roundtrip COMMAND nativejson_roundtrip ./twitter.json ./citm_catalog.json ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full nativejson_roundtrip)

add_executable(test_stateful_json_value src/test_stateful_json_value.cpp)
target_link_libraries(test_stateful_json_value json_test)
add_test(NAME test_stateful_json_value_test COMMAND test_stateful_json_value ./test_stateful_json_value.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full test_stateful_json_value)

add_executable(test_details_parse_real src/test_details_parse_real.cpp)
target_link_libraries(test_details_parse_real json_test)
add_test(test_details_parse_real_test test_details_parse_real)
add_dependencies(full test_details_parse_real)

add_executable(test_details_skip_string src/test_details_skip_string.cpp)
target_link_libraries(test_details_skip_string json_test)
add_test(test_details_skip_string_test test_details_skip_string)
add_dependencies(full test_details_skip_string)

add_executable(test_details_parse_value_class src/test_details_parse_value_class.cpp)
target_link_libraries(test_details_parse_value_class json_test)
add_test(test_details_parse_value_class_test test_details_parse_value_class)
add_dependencies(full test_details_parse_value_class)

add_executable(test_details_parse_value_array src/test_details_parse_value_array.cpp)
target_link_libraries(test_details_parse_value_array json_test)
add_test(test_details_parse_value_array_test test_details_parse_value_array)
add_dependencies(full test_details_parse_value_array)

add_executable(test_details_parse_value_custom src/test_details_parse_value_custom.cpp)
target_link_libraries(test_details_parse_value_custom json_test)
add_test(test_details_parse_value_custom_test test_details_parse_value_custom)
add_dependencies(full test_details_parse_value_custom)

add_executable(test_details_skip_array src/test_details_skip_array.cpp)
target_link_libraries(test_details_skip_array json_test)
add_test(test_details_skip_array_test test_details_skip_array)
add_dependencies(full test_details_skip_array)

add_executable(test_details_skip_class src/test_details_skip_class.cpp)
target_link_libraries(test_details_skip_class json_test)
add_test(test_details_skip_class_test test_details_skip_class)
add_dependencies(full test_details_skip_class)

add_executable(test_details_parse_value_null src/test_details_parse_value_null.cpp)
target_link_libraries(test_details_parse_value_null json_test)
add_test(test_details_parse_value_null_test test_details_parse_value_null)
add_dependencies(full test_details_parse_value_null)

add_executable(test_details_parse_value_unsigned src/test_details_parse_value_unsigned.cpp)
target_link_libraries(test_details_parse_value_unsigned json_test)
add_test(test_details_parse_value_unsigned_test test_details_parse_value_unsigned)
add_dependencies(full test_details_parse_value_unsigned)

add_executable(test_details_parse_value_signed src/test_details_parse_value_signed.cpp)
target_link_libraries(test_details_parse_value_signed json_test)
add_test(test_details_parse_value_signed_test test_details_parse_value_signed)
add_dependencies(full test_details_parse_value_signed)

add_executable(test_details_parse_value_real src/test_details_parse_value_real.cpp)
target_link_libraries(test_details_parse_value_real json_test)
add_test(test_details_parse_value_real_test test_details_parse_value_real)
add_dependencies(full test_details_parse_value_real)

add_executable(test_details_skip_number src/test_details_skip_number.cpp)
target_link_libraries(test_details_skip_number json_test)
add_test(test_details_skip_number_test test_details_skip_number)
add_dependencies(full test_details_skip_number)

add_executable(strings_test src/strings_test.cpp)
target_link_libraries(strings_test json_test)
add_test(NAME strings_test COMMAND strings_test ./strings.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full strings_test)

add_executable(strings_escaped_test src/strings_escaped_test.cpp)
target_link_libraries(strings_escaped_test json_test)
add_test(NAME strings_escaped_test COMMAND strings_escaped_test ./strings_escaped.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full strings_escaped_test)

add_executable(numbers_test src/numbers_test.cpp)
target_link_libraries(numbers_test json_test)
add_test(NAME numbers_test COMMAND numbers_test ./numbers.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
add_dependencies(full numbers_test)

add_executable(daw_json_iostream_test src/daw_json_iostream_test.cpp)
target_link_libraries(daw_json_iostream_test json_test)
add_test(NAME daw_json_iostream_test COMMAND daw_json_iostream_test)
add_dependencies(full daw_json_iostream_test)

add_executable(daw_json_minify src/daw_json_minify.cpp)
target_link_libraries(daw_json_minify json_test)
add_dependencies(full daw_json_minify)

add_executable(daw_json_minify_full src/daw_json_minify_full.cpp)
target_link_libraries(daw_json_minify_full json_test)
add_dependencies(full daw_json_minify_full)

# **************************************************
# JSON Benchmark
# **************************************************
add_executable(json_benchmark src/json_benchmark.cpp)
target_link_libraries(json_benchmark json_test)
if (NOT DEFINED MSVC OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang" )
  add_test(NAME json_benchmark_test COMMAND json_benchmark ./apache_builds.json ./twitter.json ./citm_catalog.json ./canada.json WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_data/")
else( )
  add_compile_options("/bigobj")
endif ()
add_dependencies(full json_benchmark)

cmake_host_system_information(RESULT _proc_desc QUERY PROCESSOR_DESCRIPTION)
string(REPLACE "#" "" _proc_desc ${_proc_desc})
cmake_host_system_information(RESULT _os_name QUERY OS_NAME)
string(REPLACE "#" "" _os_name ${_os_name})
cmake_host_system_information(RESULT _os_rel QUERY OS_RELEASE)
string(REPLACE "#" "" _os_rel ${_os_rel})
cmake_host_system_information(RESULT _os_ver QUERY OS_VERSION)
string(REPLACE "#" "" _os_ver ${_os_ver})
cmake_host_system_information(RESULT _os_plat QUERY OS_PLATFORM)
string(REPLACE "#" "" _os_plat ${_os_plat})
target_compile_definitions(json_benchmark PRIVATE -DPROCESSOR_DESCRIPTION="${_proc_desc}")
target_compile_definitions(json_benchmark PRIVATE -DOS_NAME="${_os_name}")
target_compile_definitions(json_benchmark PRIVATE -DOS_RELEASE="${_os_rel}")
target_compile_definitions(json_benchmark PRIVATE -DOS_VERSION="${_os_ver}")
target_compile_definitions(json_benchmark PRIVATE -DOS_PLATFORM="${_os_plat}")
target_compile_definitions(json_benchmark PRIVATE -DBUILD_TYPE="${CMAKE_BUILD_TYPE}")
# **************************************************
