
// #define GEN0
#define GEN1

#if defined(GEN0)
#if defined(VERBOSE)
static  void MARK_EXIT(const char *caller) { printf("==^^^^ %s :\n", caller); }
static  void MARK_ENTRY(const char *caller) { printf("==vvvv %s :\n", caller); }
#else
static  void MARK_EXIT(const char *caller) {  const char *tmp; tmp = caller;}
static  void MARK_ENTRY(const char *caller) {  const char *tmp; tmp = caller;}
#endif
#endif /* GEN0 */

extern char depth_indent[];
extern int depth;
#define MAX_INDENT 40

#if defined(GEN1)
#define MARK_EXIT()  { printf("^^^====%s%s\n", &depth_indent[(MAX_INDENT - depth) % MAX_INDENT], __FUNCTION__); depth %= depth - 4; }
#define MARK_ENTRY() { depth %= depth + 4; printf("vvv====%s%s\n", &depth_indent[(MAX_INDENT - depth) % MAX_INDENT], __FUNCTION__); }

#endif /* GEN1 */

