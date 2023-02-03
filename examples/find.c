#include <stdio.h>

#define CSV_IMPLEMENTATION
#include "../csv.h"

int main(void) {
	sv_t sv, substr;

	sv     = sv_cstr("Hello, world!");
	substr = sv_substr(sv, 7, 5);
	printf("Inspecting '"SV_FMT"':\n", SV_ARG(sv));

	bool contains = sv_contains_substr(sv, substr);
	printf("  contains '"SV_FMT"': %i\n", SV_ARG(substr), contains);
	printf("    -> at %zu\n", sv_find_substr(sv, substr));

	sv      = sv_cstr("ey hey heyaya hello");
	char ch = 'h';
	printf("Inspecting '"SV_FMT"':\n", SV_ARG(sv));

	contains = sv_contains(sv, ch);
	printf("  contains '%c': %i\n", ch, contains);
	printf("    -> first at %zu\n",     sv_find_first(    sv, ch));
	printf("    -> last  at %zu\n\n",   sv_find_last(     sv, ch));
	printf("    -> first not at %zu\n", sv_find_first_not(sv, ch));
	printf("    -> last  not at %zu\n", sv_find_last_not( sv, ch));

	return 0;
}
