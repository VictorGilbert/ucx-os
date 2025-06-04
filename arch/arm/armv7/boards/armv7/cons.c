/*
 *                               POK header
 *
 * The following file is a part of the POK project. Any modification should
 * made according to the POK licence. You CANNOT use this file or a part of
 * this file is this part of a file for your own project
 *
 * For more information on the POK licence, please see our LICENCE FILE
 *
 * Please follow the coding guidelines described in doc/CODING_GUIDELINES
 *
 *                                      Copyright (c) 2007-2009 POK team
 *
 * Created by julien on Thu Jan 15 23:34:13 2009
 */
#include "libpok_legacy/config.h"

#include <errno.h>

// #include "Cioports.h"
#include "libc.h"
#include <libpok_legacy/debug.h>
// #include <asp/cons.h>

#include "bsp/bsp.h"
#include "bsp/serial.h"
/* Main and debug consoles.
* 
* Exposed for future use.
*/
extern struct jet_console jet_console_main;
extern struct jet_console jet_console_debug;

static size_t iostream_write_main(const char* s, size_t length)
{
    serial_write(s, length);
    return length;
}

static size_t iostream_write_debug(const char* s, size_t length)
{
    serial_write(s, length);
    return length;
}

static size_t iostream_read_main(char* s, size_t length)
{
    return 0;
}
static size_t iostream_read_debug(char* s, size_t length)
{
    return 0;
}

struct jet_iostream
{
    /*
     * Write given string of given length into stream.
     * 
     * Return number of characters which has been written.
     * 
     * Never return 0.
     * 
     * TODO: Is returning error should be supported?
     * 
     * NULL means that writing is not supported.
     */
    size_t (*write)(const char* s, size_t length);

    /*
     * Read from the stream into given string.
     * 
     * At most 'length' characters will be read.
     * 
     * Return number of characters which has been read.
     * Return 0 if there is no available characters in the stream.
     * 
     * TODO: Is returning error should be supported?
     * 
     * NULL means that reading is not supported.
     */
    size_t (*read)(char* s, size_t length);
    
    /* If not NULL, this function should be called before use
     * .write and .read methods.
     * 
     * NOTE: This function may be called many times.
     */
    void (*init)(void);
};


struct jet_iostream arm_stream_main =
{
    .write = &iostream_write_main,
    .read  = &iostream_read_main
};
struct jet_iostream arm_stream_debug =
{
    .write = &iostream_write_debug,
    .read  = &iostream_read_debug
};
static size_t iostream_write_null(const char* s, size_t length)
{
   return length;
}
static size_t iostream_read_null(char* s, size_t length)
{
   return 0;
}
struct jet_iostream jet_stream_null =
{
   .write = &iostream_write_null,
   .read = &iostream_read_null
};

static struct jet_iostream* iostream_get_default(struct jet_iostream* arch_default)
{
   if(arch_default) return arch_default;
   else return &jet_stream_null;
}


struct jet_iostream* ja_stream_default_read = &arm_stream_main;
struct jet_iostream* ja_stream_default_write = &arm_stream_main;
struct jet_iostream* ja_stream_default_read_debug = &arm_stream_debug;
struct jet_iostream* ja_stream_default_write_debug = &arm_stream_debug;
void jet_console_init_all(void)
{
//    jet_console_main.read_stream = iostream_get_default(ja_stream_default_read);
//    jet_console_main.write_stream = iostream_get_default(ja_stream_default_write);
//    jet_console_debug.read_stream = iostream_get_default(ja_stream_default_read_debug);
//    jet_console_debug.write_stream = iostream_get_default(ja_stream_default_write_debug);

//    iostream_init(jet_console_main.read_stream);
//    iostream_init(jet_console_main.write_stream);
//    iostream_init(jet_console_debug.read_stream);
//    iostream_init(jet_console_debug.write_stream);
}


