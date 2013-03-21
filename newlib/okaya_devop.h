/* Device Operations table for Okaya LCD */

#ifndef OKAYA_DEVOP_H
#define OKAYA_DEVOP_H

#include "devoptab.h"


int okaya_open(const char *, int, int);
int okaya_open_backlit(const char *, int, int);
int okaya_close(int);
int okaya_read(int, char *, int);
int okaya_write(int, const char *, int);


extern const devoptab_t devoptab_okaya;
extern const devoptab_t devoptab_okaya_backlit;




#endif /* OKAYA_DEVOP_H */
