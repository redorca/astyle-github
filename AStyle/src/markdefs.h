
#if defined(VERBOSE)
static  void MARK_EXIT(const char *caller) { printf("==^^^^ %s :\n", caller); }
static  void MARK_ENTRY(const char *caller) { printf("==vvvv %s :\n", caller); }
#else
static  void MARK_EXIT(const char *caller) {  const char *tmp; tmp = caller;}
static  void MARK_ENTRY(const char *caller) {  const char *tmp; tmp = caller;}
#endif
