/* Device Operations Table implementation for write, read, open, close
 */

#ifndef DEVOPTAB_H
#define DEVOPTAB_H




#include <reent.h>
#include <errno.h>
#include <stdint.h>
#include <sys/types.h>


typedef struct {
   const char *name;
   int  (*open  )( const char *path,
                     int flags, int mode );
   int  (*close )( int fd );
   int (*write )( int fd,
                     const char *ptr, int len );
   int (*read  )( int fd,
                     char *ptr, int len );
} devoptab_t;


// Global device driver list (file descriptors)
extern const devoptab_t *devoptab_list[];




#endif /* DEVOPTAB_H */
