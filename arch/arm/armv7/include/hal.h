#include <stdint.h>
#include <stdint.h>
#include <stddef.h>

// #include </home/victorgilbert/Portage_UCX-OS_TMS570/repo/ucx-os-forked/arch/arm/armv7/boards/armv7/include/gpio_ll.h>
#define __ARCH__	"ARM Cortex R5 (TMS570x)"
extern uint32_t __bss_start;
extern uint32_t __bss_end;
extern uint32_t __stack;

#define strcpy(dst, src)		ucx_strcpy(dst, src)
#define strncpy(s1, s2, n)		ucx_strncpy(s1, s2, n)
#define strcat(dst, src)		ucx_strcat(dst, src)
#define strncat(dst, src, n)		ucx_strncat(dst, src, n)
#define strcmp(s1, s2)			ucx_strcmp(s1, s2)
#define strncmp(s1, s2, n)		ucx_strncmp(s1, s2, n)
#define strstr(string, find)		ucx_strstr(string, find)
#define strlen(s)			ucx_strlen(s)
#define strchr(s, c)			ucx_strchr(s, c)
#define strpbrk(str, set)		ucx_strpbrk(str, set)
#define strsep(pp, delim)		ucx_strsep(pp, delim)
#define strtok(s, delim)		ucx_strtok(s, delim)
#define strtok_r(s, delim, holder)	ucx_strtok_r(s, delim, holder)
#define strtol(s, end, base)		ucx_strtol(s, end, base)
#define atoi(s)				ucx_atoi(s)
#define itoa(i, s, base)		ucx_itoa(i, s, base)
#define memcpy(dst, src, n)		ucx_memcpy(dst, src, n)
#define memmove(dst, src, n)		ucx_memmove(dst, src, n)
#define memcmp(cs, ct, n)		ucx_memcmp(cs, ct, n)
#define memset(s, c, n)			ucx_memset(s, c, n)
#define abs(n)				ucx_abs(n)
#define random()			ucx_random()
#define srand(seed)			ucx_srand(seed)
#define puts(str)			ucx_puts(str)
#define gets(s)				ucx_gets(s)
#define fgets(s, n, f)			ucx_fgets(s, n, f)
#define getline(s)			ucx_getline(s)
#define printf(fmt, ...)		ucx_printf(fmt, ##__VA_ARGS__)
#define sprintf(out, fmt, ...)		ucx_sprintf(out, fmt, ##__VA_ARGS__)

#define malloc(n)			ucx_malloc(n)
#define free(n)				ucx_free(n)
#define calloc(n, t)			ucx_calloc(n, t) 
#define realloc(p, s)			ucx_realloc(p, s)


// Time management
uint64_t _read_us(void);
void _delay_us(uint32_t usec);
void _delay_ms(uint32_t msec);


/* hardware dependent C library stuff */ // Pas certain du nom de la categorie
// struct jmp_buf
// {
//   uint32_t regs[13];
//   uint32_t sp;
//   uint32_t lr;
// };
typedef uint32_t jmp_buf[15];
// #define jmp_buf jet_context
void _context_init(jmp_buf *ctx, size_t sp, size_t ss, size_t ra);

/* hardware dependent C library stuff */
#define CONTEXT_RA	0 //VERIFIER
#define CONTEXT_SP	9 //VERIFIER
#define CONTEXT_PSP	10 //VERIFIER

#define MAX_INT_SOURCES 16

//TODO: Write functions and change constants
// int gpio_ll_setup(struct gpio_config_values_s *cfg);
// int gpio_ll_get(struct gpio_config_values_s *cfg);
// int gpio_ll_set(struct gpio_config_values_s *cfg, int val);
// int gpio_ll_clear(struct gpio_config_values_s *cfg, int val);
// int gpio_ll_toggle(struct gpio_config_values_s *cfg, int val);
// int gpio_ll_int_attach(struct gpio_config_values_s *cfg, int pin, void (*callback)(), int trigger);

// int i2c_ll_init(struct i2c_hw_config_values_s *config_values);
// int i2c_ll_deinit(struct i2c_hw_config_values_s *config_values);
// int i2c_ll_start(struct i2c_hw_config_values_s *config_values);
// int i2c_ll_restart(struct i2c_hw_config_values_s *config_values);
// int i2c_ll_stop(struct i2c_hw_config_values_s *config_values);
// int i2c_ll_wr_addr(struct i2c_hw_config_values_s *config_values, unsigned short addr);
// int i2c_ll_rd_addr(struct i2c_hw_config_values_s *config_values, unsigned short addr);
// int i2c_ll_write(struct i2c_hw_config_values_s *config_values, unsigned char val);
// int i2c_ll_read(struct i2c_hw_config_values_s *config_values, uint8_t nack);

#define PWM_DEFAULT_TIMER	PWM_TIMER4
#define PWM_DEFAULT_CHANNEL	PWM_CHANNEL1
#define PWM_DEFAULT_ALT_CHANNEL	PWM_CHANNEL4

// long pwm_ll_setup(struct pwm_config_values_s *cfg);
// int pwm_ll_get(struct pwm_config_values_s *cfg, unsigned channel, unsigned *pulse);
// int pwm_ll_set(struct pwm_config_values_s *cfg, unsigned channel, unsigned pulse);
#define DEFAULT_STACK_SIZE	2048

void _interrupt_tick(void);