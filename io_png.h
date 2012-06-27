/* Camera motion estimation, by Léo Girardin and David Lafontaine
    Copyright (C) 2012 Léo Girardin and David Lafontaine

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _IO_PNG_H
#define _IO_PNG_H

#ifdef __cplusplus
extern "C" {
#endif

#define IO_PNG_VERSION "0.20110919"

#include <stddef.h>

typedef enum io_png_opt_e {
    IO_PNG_OPT_NONE = 0x00,
    IO_PNG_OPT_RGB = 0x01,
    IO_PNG_OPT_GRAY = 0x02,
    IO_PNG_OPT_ADAM7 = 0x10,
    IO_PNG_OPT_ZMIN = 0x20,
    IO_PNG_OPT_ZMAX = 0x40
} io_png_opt_t;

/* io_png.c */
char *io_png_info(void);
float *io_png_read_flt_opt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp, io_png_opt_t opt);
float *io_png_read_flt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp);
unsigned char *io_png_read_uchar_opt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp, io_png_opt_t opt);
unsigned char *io_png_read_uchar(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp);
unsigned short *io_png_read_ushrt_opt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp, io_png_opt_t opt);
unsigned short *io_png_read_ushrt(const char *fname, size_t *nxp, size_t *nyp, size_t *ncp);
void io_png_write_flt(const char *fname, const float *data, size_t nx, size_t ny, size_t nc);
void io_png_write_uchar(const char *fname, const unsigned char *data, size_t nx, size_t ny, size_t nc);
void io_png_write_ushrt(const char *fname, const unsigned short *data, size_t nx, size_t ny, size_t nc);

#ifdef __cplusplus
}
#endif

#endif /* !_IO_PNG_H */
