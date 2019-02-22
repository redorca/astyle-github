
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

extern char spaces[];
extern int spacing;

#if defined(GEN1)
#define MARK_EXIT()  { printf("^^^====%s%s\n", &spaces[spacing], __FUNCTION__); spacing--; }
#define MARK_ENTRY() { spacing++; printf("vvv====%s%s\n", &spaces[spacing], __FUNCTION__); }

#endif /* GEN1 */

