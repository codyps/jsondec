#include "jsondec.h"

#define JSON_ERROR(error_kind_, pos_, len_) (struct json_result) { \
	.error = { \
		.kind = JSON_ERROR_##error_kind_,\
		.pos = pos_, \
		.len = len_, \
	}\
}

static const char *whitespace = "\x20\x09\x0A\x0D";

enum struct_chars {
	BEGIN_ARRAY = 0x5b,  /* [ */
	BEGIN_OBJECT = 0x7b, /* { */
	END_ARRAY = 0x5d,    /* ] */
	END_OBJECT = 0x7d,   /* } */
	NAME_SEP = 0x3a,     /* : */
	VAL_SEP = 0x2c,      /* , */
};

static char *eat_ws(const char *d, size_t *len)
{
	size_t i;
	size_t l = *len;
	for (i = 0; i < l; i++) {
		size_t j;
		char c = d[i];
		for (j = 0; j < sizeof(whitespace) - 1; j++)
			if (whitespace[j] == c)
				goto next_c;
		break;
next_c:
		;
	}

	*len = l - i;
	return (char *)d + i;
}

struct json_result json_decode_init(char *data, size_t len)
{
	data = eat_ws(data, &len);
	if (len < 1)
		return JSON_ERROR(EXPECTED_STRUCTURAL_CHAR, data, 1);
	switch (*data) {
		case BEGIN_ARRAY:
			return (struct json_result) {
				.value = {
					.type = JSON_VALUE_ARRAY,
					.arr
				}
			};

		case BEGIN_OBJECT:
		/* or we might have a literal: */
		case 'n':
		case 'f':
		case 't':
		case '-':
		case '0'...'9':
	}
}
