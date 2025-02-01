#include "headers/highlight.h"

bool eligible; // is syntax highlighting enabled
const char *types[] = {"bool", "char", "const", "double", "enum", "extern", "float", 
    "int", "int16_t", "int32_t", "int64_t", "long", "short", "signed", "size_t", 
    "static", "uint16t", "uint32_t", "uint64_t", "uint8t", "unsigned", "void"};
const char *defs[]  = {"break", "case", "continue", "default", "do", "else", "false", 
    "for", "goto", "if", "return", "sizeof", "struct", "switch", "true", "while"};
const char oper[]  = {'&', '*', '+', '-', '/', '<', '=', '>', '[', ']', '^', '|', '~'};
uchar types_len[] = {4, 4, 5, 6, 4, 6, 5, 3, 7, 7, 7, 4, 5, 6, 6, 6, 7, 8, 8, 6, 8, 4};
uchar defs_len[] = {5, 4, 8, 7, 2, 4, 5, 3, 4, 2, 6, 6, 6, 6, 4, 5};

#define DEFINC	COLOR_CYAN
#define COMMENT	COLOR_GREEN
#define TYPES	COLOR_RED
#define OPER	COLOR_YELLOW
#define DEFS    COLOR_BLUE
#define STR	COLOR_MAGENTA
// TODO: color for numbers?

#define nelems(x)  (sizeof(x) / sizeof((x)[0]))
#define is_separator(ch) ((ch > 31 && ch < 48) || (ch > 57 && ch < 65) || (ch > 90 && ch < 95) || ch > 122)

wchar_t tmp[256];
char str[256];

// checks if file is C source code
bool isc(const char *str)
{
	uint res = whereis(str, '.');
	if (res == 0)
		return false;
	str += res;
	if (!strcmp(str, "c") || !strcmp(str, "cpp") || !strcmp(str, "cc")
		|| !strcmp(str, "h") || !strcmp(str, "hpp"))
		return true;
	return false;
}

typedef struct res_s {
	uchar len;
	char type;
} res_t;

int char_cmp(const char a, const char b, uchar) { return a - b; }
// helper binary search template
template <typename T, typename Compare>
bool binary_search(const T *arr, const uchar *len_arr, uint size, const T &line, res_t &res, 
		char type, Compare cmpf)
{
	int lo = 0, hi = size - 1, mid;
	while (lo <= hi) {
		mid = lo + (hi - lo) / 2;
		int cmp = cmpf(arr[mid], line, len_arr[mid]);
		if (cmp == 0) {
			res.len = len_arr ? len_arr[mid] : 1;
			res.type = type;
			return true;
		} else if (cmp < 0)
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return false;
}

// identify color to use
res_t get_category(const char *line)
{
	res_t res;
	res.len = 0;
	res.type = COLOR_WHITE;

	if (binary_search(types, types_len, nelems(types), line, res, TYPES, strncmp))
		return res;
	if (binary_search(defs, defs_len, nelems(defs), line, res, DEFS, strncmp))
		return res;
	if (binary_search(oper, 0, nelems(oper), *line, res, OPER, char_cmp))
		return res;
	return res;
}

// highight line if eligible = true
void apply(uint line)
{
	if (!eligible)
		return;
	wmove(text_win, line, 0);
	winwstr(text_win, tmp);
	uint len = wcstombs(str, tmp, min(256, maxx - 2));
	uint previ = 0;

	for (uint i = 0; i < len; ++i) {
		wmove(text_win, line, i);
		if (str[i] == '#') { // define / include
			wchgat(text_win, maxx - i - 1, 0, DEFINC, 0);
			return;
		} else if (str[i] == '/' && str[i + 1] == '/') { // comments
			wchgat(text_win, maxx - i - 1, 0, COMMENT, 0);
			return;
		} else if (str[i] == '/' && str[i + 1] == '*') {
			previ = i;
			i += 2;
			// TODO: end of multi-line comment might be in next line
			while (str[i] != '*' && str[i + 1] != '/' && i < len)
				++i;
			wchgat(text_win, i++ - previ + 2, 0, COMMENT, 0);
		} else if (str[i] == '\'') { // string / char
			previ = i++;
			while (str[i] != '\'' && i < len)
				++i;
			wchgat(text_win, i - previ + 1, 0, STR, 0);
		} else if (str[i] == '\"') {
			previ = i++;
			while (str[i] != '\"' && i < len)
				++i;
			wchgat(text_win, i - previ + 1, 0, STR, 0);
		} else { // type (int, char) / keyword (if, return) / operator (=, +)
			res_t res = get_category(str + i);

			// no highlight for non-separated matches
			bool next = is_separator(str[i + res.len]);
			bool prev = i == 0 ? 1 : is_separator(str[i - 1]);
			// except for operators which are separators
			if ((next && prev) || res.type == OPER)
				wchgat(text_win, res.len, 0, res.type, 0);
		}
	}
}

// wrapper for apply()
void highlight(uint y)
{
#ifdef HIGHLIGHT
	apply(y);
#endif
}
