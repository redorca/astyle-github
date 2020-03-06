

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
#define RESET()         "\033[0;39;49m"
#define YELLOW(a)       "\033[1;30;43m" # a
#define GREEN(a)        "\033[1;37;42m" # a
#define BLUE(a)         "\033[1;37;44m" # a
#define LTBLUE(a)       "\033[1;30;46m" # a
#if defined(DBG)

/* #define CONTINUE    {  SHOW_LINE(&currentLine[0]); continue; } */
#define CONTINUE    continue;

#define SHOW_LINE(a)     \
        printf("%s :: %d == %s %s\n", __FILE__, __LINE__, #a, a);
/*      printf("%s :: %s\n", __FUNCTION__, a); */

#define LABEL(a)                                                                                                \
                {                                                                                               \
                        printf(" ::%d ==== %s%s %s\n", FOO(STEP), &depth_indent[DEPTH], a, __FUNCTION__);       \
                }

#define DISPLAY(a, b)                                                                           \
                {                                                                               \
                        printf(" ::   %s%s%s\n", b, a, RESET());        \
                }

#define MARK_EXIT()                             \
                {                               \
                        LABEL(EXIT);            \
                        NEW_DEPTH(-STEP);       \
                }
#define MARK_ENTRY()                            \
                {                               \
                        NEW_DEPTH(STEP);        \
                        LABEL(ENTER);           \
                }

#define RETURN(args ...)        \
        {                       \
                MARK_EXIT();    \
                return args;    \
        }
#else

#define CONTINUE    continue;
#define SHOW_LINE(a)
#define SHOW_DEPTH(XXX)
#define LABEL(a)
#define DISPLAY(a, b)
#define MARK_EXIT()
#define MARK_ENTRY()
#define RETURN(args ...)   return args

#endif
