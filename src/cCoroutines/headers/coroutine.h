/* coroutine.h
 * 
 * [Simple version using static variables (scr macros)]
 * int ascending (void) {
 *    static int i;
 * 
 *    scrBegin;
 *    for (i=0; i<10; i++) {
 *       scrReturn(i);
 *    }
 *    scrFinish(-1);
 * }
 * 
 * [Re-entrant version using an explicit context structure (ccr macros)]
 * int ascending (ccrContParam) {
 *    ccrBeginContext;
 *    int i;
 *    ccrEndContext(foo);
 *
 *    ccrBegin(foo);
 *    for (foo->i=0; foo->i<10; foo->i++) {
 *       ccrReturn(foo->i);
 *    }
 *    ccrFinish(-1);
 * }
 * 
 * The caller of a static coroutine calls it just as if it were an
 * ordinary function:
 * 
 * void main(void) {
 *    int i;
 *    do {
 *       i = ascending();
 *       printf("got number %d\n", i);
 *    } while (i != -1);
 * }
 * 
 * The caller of a re-entrant coroutine must provide a context
 * variable:
 * 
 * void main(void) {
 *    ccrContext z = 0;
 *    do {
 *       printf("got number %d\n", ascending (&z));
 *    } while (z);
 * }
 * 
 * Note that the context variable is set back to zero when the
 * coroutine terminates (by crStop, or by control reaching
 * crFinish). This can make the re-entrant coroutines more useful
 * than the static ones, because you can tell when they have
 * finished.
 * 
 * If you need to dispose of a crContext when it is non-zero (that
 * is, if you want to stop calling a coroutine without suffering a
 * memory leak), the caller should call `ccrAbort(ctx)' where `ctx'
 * is the context variable.
 */

#ifndef __COROUTINE_H_
#define __COROUTINE_H_

#include <stdlib.h>

#define scrBegin static int scrLine = 0; switch(scrLine) { case 0:;
#define scrFinish(z) } return (z)
#define scrFinishV } return

#define scrReturn(z) \
    do { \
        scrLine = __LINE__; \
        return(z); case __LINE__:; \
    } while(0);
#define scrReturnV \
    do { \
        scrLine = __LINE__; \
        return; case __LINE__:; \
    } while(0)






#define ccrContParam     void **ccrParam

#define ccrBeginContext  struct ccrContextTag { int ccrLine
#define ccrEndContext(x) } *x = (struct ccrContextTag*)*ccrParam

#define ccrBegin(x)      if(!x) { x = *ccrParam = malloc(sizeof(*x)); x->ccrLine = 0; } \
                         if(x) switch(x->ccrLine) { case 0:;
#define ccrFinish(z)     } free(*ccrParam); *ccrParam = 0; return(z)
#define ccrFinishV       } free(*ccrParam); *ccrParam = 0; return

#define ccrReturn(z)     \
    do { \
        ((struct ccrContextTag*)*ccrParam)->ccrLine = __LINE__; \
        return(z); case __LINE__:; \
    } while(0)
#define ccrReturnV       \
    do { \
        ((struct ccrContextTag *)*ccrParam)->ccrLine=__LINE__; \
        return; case __LINE__:; \
    } while(0)

#define ccrStop(z)       do{ free(*ccrParam); *ccrParam = 0; return(z); } while(0)
#define ccrStopV         do{ free(*ccrParam); *ccrParam = 0; return; } while(0)

#define ccrContext       void *
#define ccrAbort(ctx)    do { free(ctx); ctx = 0; } while(0)

#endif
