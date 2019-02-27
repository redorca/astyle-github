
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
#define MAX_INDENT 60

#if defined(GEN1)
#define DEPTH   (MAX_INDENT - (depth % MAX_INDENT))
#define NEW_DEPTH(a)    depth += a
#define EXIT    "^^^"
#define ENTER   "vvv"

#define LABEL(a)                         \
                {                                                                                       \
                        printf("%s::%d ==== %s%s\n", a, DEPTH, &depth_indent[DEPTH], __FUNCTION__);    \
                }
#define STEP  2

#if !defined(OLD_MARKERS)
#define MARK_EXIT()    \
                {                       \
                        LABEL(EXIT)     \
                        NEW_DEPTH(-STEP);  \
                }
#define MARK_ENTRY()    \
                {                       \
                        NEW_DEPTH(STEP);   \
                        LABEL(ENTER)    \
                }
#else
#define MARK_EXIT()     LABEL(EXIT)
#define MARK_ENTRY()    LABEL(ENTER)
#endif

#if defined(OLD_MARKERS)
#define MARK_EXIT()                     \
                {                                                                                       \
                        printf("^^^::%d ====%s%s\n", DEPTH, &depth_indent[DEPTH], __FUNCTION__);        \
                        NEW_DEPTH;                                                                      \
                }
#define MARK_ENTRY() \
                {
                        printf("vvv::%d ====%s%s\n", DEPTH, &depth_indent[DEPTH], __FUNCTION__);        \
                        NEW_DEPTH;                                                                      \
                }
#endif /* OLD_MARKERS */

#endif /* GEN1 */

