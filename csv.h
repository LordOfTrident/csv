/* #define CSV_IMPLEMENTATION */

#ifndef CSV_HEADER_GUARD
#define CSV_HEADER_GUARD

#include <string.h>  /* strlen */
#include <stdbool.h> /* bool, true, false */

#define CSV_VERSION_MAJOR 1
#define CSV_VERSION_MINOR 0
#define CSV_VERSION_PATCH 0

typedef struct {
	size_t      len;
	const char *cstr;
} sv_t;

#define SV_FMT     "%.*s"
#define SV_ARG(SV) (int)(SV).len, (SV).cstr

#define SV_NULL (sv_t){.cstr = NULL}
#define SV_NPOS (size_t)-1

#define SV_WHITESPACES " \f\n\r\t\v"

sv_t sv_new( const char *cstr, size_t len) {return (sv_t){.len = len, .cstr = cstr};}
sv_t sv_cstr(const char *cstr)             {return sv_new(cstr, strlen(cstr));}

char sv_at(     sv_t sv, size_t idx) {return sv.cstr[idx];}
bool sv_is_null(sv_t sv)             {return sv.cstr == NULL;}

bool sv_is_equal(sv_t sv, sv_t to);

bool sv_has_prefix(sv_t sv, sv_t prefix);
bool sv_has_suffix(sv_t sv, sv_t suffix);

sv_t sv_substr(    sv_t sv, size_t start, size_t len);
sv_t sv_trim_front(sv_t sv, const char *chs);
sv_t sv_trim_back( sv_t sv, const char *chs);
sv_t sv_trim(      sv_t sv, const char *chs);

bool   sv_contains(      sv_t sv, char ch);
size_t sv_find_first(    sv_t sv, char ch);
size_t sv_find_last(     sv_t sv, char ch);
size_t sv_find_first_not(sv_t sv, char ch);
size_t sv_find_last_not( sv_t sv, char ch);

bool   sv_contains_substr(sv_t sv, sv_t substr);
size_t sv_find_substr(    sv_t sv, sv_t substr);

#endif

#ifdef CSV_IMPLEMENTATION

bool sv_is_equal(sv_t sv, sv_t to) {
	size_t len = sv.len > to.len? sv.len : to.len;
	for (size_t i = 0; i < len; ++ i) {
		if (sv_at(sv, i) != sv_at(to, i))
			return false;
	}

	return true;
}

bool sv_has_prefix(sv_t sv, sv_t prefix) {
	if (sv.len < prefix.len)
		return false;

	for (size_t i = 0; i < prefix.len; ++ i) {
		if (sv_at(sv, i) != sv_at(prefix, i))
			return false;
	}
}

bool sv_has_suffix(sv_t sv, sv_t suffix) {
	if (sv.len < suffix.len)
		return false;

	for (size_t i = sv.len - suffix.len; i < sv.len; ++ i) {
		if (sv_at(sv, i) != sv_at(suffix, i))
			return false;
	}
}

sv_t sv_substr(sv_t sv, size_t start, size_t len) {
	if (len != SV_NPOS) {
		if (start + len > sv.len)
			return SV_NULL;
	} else if (start > sv.len)
		return SV_NULL;

	sv_t substr  = sv;
	substr.cstr += start;
	substr.len   = len == SV_NPOS? sv.len - start : len;

	return substr;
}

sv_t sv_trim_front(sv_t sv, const char *chs) {
	sv_t matches = sv_cstr(chs);
	sv_t trimmed = sv;
	for (size_t i = 0; i < sv.len; ++ i) {
		if (!sv_contains(matches, sv_at(sv, i)))
			break;

		++ trimmed.cstr;
		-- trimmed.len;
	}

	return trimmed;
}

sv_t sv_trim_back(sv_t sv, const char *chs) {
	sv_t matches = sv_cstr(chs);
	sv_t trimmed = sv;
	for (size_t i = sv.len - 1; i != SV_NPOS; -- i) {
		if (!sv_contains(matches, sv_at(sv, i)))
			break;

		-- trimmed.len;
	}

	return trimmed;
}

sv_t sv_trim(sv_t sv, const char *chs) {
	sv =   sv_trim_front(sv, chs);
	return sv_trim_back( sv, chs);
}

bool sv_contains(sv_t sv, char ch) {
	for (size_t i = 0; i < sv.len; ++ i) {
		if (sv_at(sv, i) == ch)
			return true;
	}

	return false;
}

size_t sv_find_first(sv_t sv, char ch) {
	for (size_t i = 0; i < sv.len; ++ i) {
		if (sv_at(sv, i) == ch)
			return i;
	}

	return SV_NPOS;
}

size_t sv_find_last(sv_t sv, char ch) {
	for (size_t i = sv.len - 1; i != SV_NPOS; -- i) {
		if (sv_at(sv, i) == ch)
			return i;
	}

	return SV_NPOS;
}

size_t sv_find_first_not(sv_t sv, char ch) {
	for (size_t i = 0; i < sv.len; ++ i) {
		if (sv_at(sv, i) != ch)
			return i;
	}

	return SV_NPOS;
}

size_t sv_find_last_not(sv_t sv, char ch) {
	for (size_t i = sv.len - 1; i != SV_NPOS; -- i) {
		if (sv_at(sv, i) != ch)
			return i;
	}

	return SV_NPOS;
}

bool sv_contains_substr(sv_t sv, sv_t substr) {
	if (substr.len > sv.len)
		return false;

	for (size_t i = 0; i < sv.len - (substr.len - 1); ++ i) {
		bool matched = true;
		for (size_t j = 0; j < substr.len; ++ j) {
			if (sv_at(sv, i + j) != sv_at(substr, j)) {
				matched = false;
				break;
			}
		}

		if (matched)
			return true;
	}

	return false;
}


size_t sv_find_substr(sv_t sv, sv_t substr) {
	if (substr.len > sv.len)
		return SV_NPOS;

	for (size_t i = 0; i < sv.len - (substr.len - 1); ++ i) {
		bool matched = true;
		for (size_t j = 0; j < substr.len; ++ j) {
			if (sv_at(sv, i + j) != sv_at(substr, j)) {
				matched = false;
				break;
			}
		}

		if (matched)
			return i;
	}

	return SV_NPOS;
}

#endif
