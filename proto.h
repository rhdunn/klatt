#ifndef PROTO
#if defined (USE_PROTOTYPES) ? USE_PROTOTYPES : defined (__STDC__)
#define PROTO(ARGS) ARGS
#else
#define PROTO(ARGS) ()
#endif
#ifndef __STDC__
#define const
#endif
#ifndef __GNUC__
#define inline
#endif
#endif

