

extern char depth_indent[];
extern int depth;
#define MAX_INDENT 60

#define DEPTH   (MAX_INDENT - (depth % MAX_INDENT))
#define NEW_DEPTH(a)    depth += a
#define EXIT    "^^^"
#define ENTER   "vvv"

#define LABEL(a)                         \
                {                                                                                       \
                        printf("%s::%d ==== %s%s\n", a, DEPTH, &depth_indent[DEPTH], __FUNCTION__);    \
                }
#define STEP  2

#define MARK_EXIT()    \
                {                               \
                        LABEL(EXIT)             \
                        NEW_DEPTH(-STEP);       \
                }
#define MARK_ENTRY()    \
                {                               \
                        NEW_DEPTH(STEP);        \
                        LABEL(ENTER)            \
                }

