

extern char depth_indent[];
extern int depth;

#define MAX_INDENT 60
#define MODDEPTH  (depth % MAX_INDENT)
#define DEPTH   (MAX_INDENT - MODDEPTH)
#define NEW_DEPTH(a)    depth += a
#define EXIT    "^^^"
#define ENTER   "vvv"
#define STEP  4
#define FOO(a)  MODDEPTH / (a)

#if defined(DBG)

#define SHOW_LINE(a)     \
        printf("%s :: %s\n", #a , a);
/*      printf("%s :: %s\n", __FUNCTION__, a); */

#define LABEL(a)                         \
                {                                                                                       \
                        printf("%s::%d ==== %s%s\n", a, FOO(STEP), &depth_indent[DEPTH], __FUNCTION__);    \
                }

#define MARK_EXIT()    \
                {                               \
                        LABEL(EXIT);            \
                        NEW_DEPTH(-STEP);       \
                }
#define MARK_ENTRY()    \
                {                               \
                        NEW_DEPTH(STEP);        \
                        LABEL(ENTER);           \
                }

#define RETURN(args ...)   \
        {                       \
                MARK_EXIT();    \
                return args;    \
        }
#else

#define SHOW_LINE(a)

#define SHOW_DEPTH(XXX)
#define LABEL(a)
#define MARK_EXIT()
#define MARK_ENTRY()
#define RETURN(args ...)   return args

#endif
