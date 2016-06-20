#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

enum json_value_type {
	JSON_VALUE_NULL,
	JSON_VALUE_BOOL,
	JSON_VALUE_STRING,
	
	/* There are really only "numbers", but c doesn't have "numbers", so we
	 * try to guess */
	JSON_VALUE_INT,
	JSON_VALUE_UINT,
	JSON_VALUE_DOUBLE,

	/* containers */
	JSON_VALUE_ARRAY,
	JSON_VALUE_OBJECT,
};

struct json_array {
	char *start;
	size_t len_max;
};

struct json_object {
	char *start;
	size_t len_max;
};

struct json_string {
	char *start;
	size_t len;
};

struct json_value {
	enum json_value_type type;

	union {
		struct json_array array;
		struct json_object object;
		uintmax_t uint;
		intmax_t i;
		double d;
	};
};

enum json_error_kind {
	JSON_ERROR_GENERIC = -2,
	JSON_ERROR_EXPECTED_STRUCTURAL_CHAR = -1,
};

struct json_error {
	enum json_error_kind kind;
	char *pos;
	size_t len;
};

struct json_result {
	union {
		struct json_value value;
		struct json_error error;
	};
};

struct json_result json_decode_init(char *pos, size_t len);

struct json_result json_array_next(struct json_array *a);

struct json_result_object {
	union {
		struct json_error error;
		struct {
			struct json_string key;
			struct json_value value;
		};
	};
};
struct json_result_object json_object_next(struct json_object *o);
