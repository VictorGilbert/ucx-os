/*
 * bsp.c
 *
 *  Created on: 10 mai 2019
 *      Author: Alexy
 */

#include <bsp.h>

#include <libpok_legacy/types.h>
#include <errno.h>
#include <libpok_legacy/syscall.h>

// #include <core/time.h>
#include <interrupt.h>
#include <space.h>

#include <bsp/rti.h>
#include <bsp/serial.h>
#include <bsp/vim.h>
#include "bsp/bsp.h"

// #include <asp/entries.h>
#include <libpok_legacy/debug.h>

#define POK_TIMER_FREQUENCY 1000

extern void __TI_auto_init(void);
/**
 * @brief System register type 1.
 * @details System register type 1 structure as defined by documentation.
 */
 typedef struct sys_reg_type1
 {
     uint32_t SYSPC1;
     uint32_t SYSPC2;
     uint32_t SYSPC3;
     uint32_t SYSPC4;
     uint32_t SYSPC5;
     uint32_t SYSPC6;
     uint32_t SYSPC7;
     uint32_t SYSPC8;
     uint32_t SYSPC9;
     uint32_t rsvd1;
     uint32_t rsvd2;
     uint32_t rsvd3;
     uint32_t CSDIS;
     uint32_t CSDISSET;
     uint32_t CSDISCLR;
     uint32_t CDDIS;
     uint32_t CDDISSET;
     uint32_t CDDISCLR;
     uint32_t GHVSRC;
     uint32_t VCLKASRC;
     uint32_t RCLKSRC;
     uint32_t CSVSTAT;
     uint32_t MSTGCR;
     uint32_t MINITGCR;
     uint32_t MSINENA;
     uint32_t MSTFAIL;
     uint32_t MSTCGSTAT;
     uint32_t MINISTAT;
     uint32_t PLLCTL1;
     uint32_t PLLCTL2;
     uint32_t SYSPC10;
     uint32_t DIEIDL;
     uint32_t DIEIDH;
     uint32_t rsvd4;
     uint32_t LPOMONCTL;
     uint32_t CLKTEST;
     uint32_t DFTCTRLREG1;
     uint32_t DFTCTRLREG2;
     uint32_t rsvd5;
     uint32_t rsvd6;
     uint32_t GPREG1;
     uint32_t rsvd7;
     uint32_t rsvd8;
     uint32_t rsvd9;
     uint32_t SSIR1;
     uint32_t SSIR2;
     uint32_t SSIR3;
     uint32_t SSIR4;
     uint32_t RAMGCR;
     uint32_t BMMCR1;
     uint32_t rsvd10;
     uint32_t CPURSTCR;
     uint32_t CLKCNTL;
     uint32_t ECPCNTL;
     uint32_t rsvd11;
     uint32_t DEVCR1;
     uint32_t SYSECR;
     uint32_t SYSESR;
     uint32_t SYSTASR;
     uint32_t GBLSTAT;
     uint32_t DEVID;
     uint32_t SSIVEC;
     uint32_t SSIF;
 } sys_reg_type1_t;
 
 /**
  * @brief System register type 2.
  * @details System register type 2 structure as defined by documentation.
  */
 typedef struct sys_reg_type2
 {
     uint32_t PLLCTL3;
     uint32_t rsvd1;
     uint32_t STCCLKDIV;
     uint32_t rsvd2[6];
     uint32_t ECPCNTL;
     uint32_t ECPCNTL1;
     uint32_t rsvd3[4];
     uint32_t CLK2CNTRL;
     uint32_t VCLKACON1;
     uint32_t rsvd4[4];
     uint32_t HCLKCNTL;
     uint32_t rsvd5[6];
     uint32_t CLKSLIP;
     uint32_t rsvd6;
     uint32_t IP1ECCERREN;
     uint32_t rsvd7[28];
     uint32_t EFC_CTLEN;
     uint32_t DIEIDL_REG0;
     uint32_t DIEIDH_REG1;
     uint32_t DIEIDL_REG2;
     uint32_t DIEIDH_REG3;
 } sys_reg_type2_t;
 
 #define SYS_REG_1_BASE ((sys_reg_type1_t *)0xFFFFFF00)
 #define SYS_REG_2_BASE ((sys_reg_type2_t *)0xFFFFE100)
/**
 * @brief PCR register structure as per defined by the documentation.
 */
 typedef struct pcr_reg
 {
     uint32_t PMPROTSET0;
     uint32_t PMPROTSET1;
     uint32_t rsvd1[2];
     uint32_t PMPROTCLR0;
     uint32_t PMPROTCLR1;
     uint32_t rsvd2[2];
     uint32_t PPROTSET0;
     uint32_t PPROTSET1;
     uint32_t PPROTSET2;
     uint32_t PPROTSET3;
     uint32_t rsvd3[4];
     uint32_t PPROTCLR0;
     uint32_t PPROTCLR1;
     uint32_t PPROTCLR2;
     uint32_t PPROTCLR3;
     uint32_t rsvd4[4];
     uint32_t PCSPWRDWNSET0;
     uint32_t PCSPWRDWNSET1;
     uint32_t rsvd5[2];
     uint32_t PCSPWRDWNCLR0;
     uint32_t PCSPWRDWNCLR1;
     uint32_t rsvd6[2];
     uint32_t PSPWRDWNSET0;
     uint32_t PSPWRDWNSET1;
     uint32_t PSPWRDWNSET2;
     uint32_t PSPWRDWNSET3;
     uint32_t rsvd7[4];
     uint32_t PSPWRDWNCLR0;
     uint32_t PSPWRDWNCLR1;
     uint32_t PSPWRDWNCLR2;
     uint32_t PSPWRDWNCLR3;
     uint32_t rsvd8[4];
     uint32_t PDPWRDWNSET;
     uint32_t PDPWRDWNCLR;
     uint32_t rsvd9[78];
     uint32_t MSTIDWRENA;
     uint32_t MSTIDENA;
     uint32_t MSTIDDIAGCTRL;
     uint32_t rsvd10[61];
     struct
     {
         uint32_t PSxMSTID_L;
         uint32_t PSxMSTID_H;
     }PSxMSTID[32];
     struct
     {
         uint32_t PPSxMSTID_L;
         uint32_t PPSxMSTID_H;
     }PPSxMSTID[8];
     struct
     {
         uint32_t PPSExMSTID_L;
         uint32_t PPSExMSTID_H;
     }PPSExMSTID[32];
     uint32_t PCSxMSTID[32];
     uint32_t PPCSxMSTID[8];
 } pcr_reg_t;
 
 
 #define PCR_REG_1 ((pcr_reg_t *)0xFFFF1000)
 #define PCR_REG_2 ((pcr_reg_t *)0xFCFF1000)
 #define PCR_REG_3 ((pcr_reg_t *)0xFFF78000) 


/**
 * @brief Flash register structure as per defined by the documentation.
 */
typedef struct flash_reg
{
    uint32_t FRDCNTL;
    uint32_t rsvd1;
    uint32_t EE_FEDACCTRL1;
    uint32_t rsvd2;
    uint32_t rsvd3;
    uint32_t FEDAC_PASTATUS;
    uint32_t FEDAC_PBSTATUS;
    uint32_t FEDAC_GBLSTATUS;
    uint32_t rsvd4;
    uint32_t FEDACSDIS;
    uint32_t FPRIM_ADD_TAG;
    uint32_t FDUP_ADD_TAG;
    uint32_t FBPROT;
    uint32_t FBSE;
    uint32_t FBBUSY;
    uint32_t FBAC;
    uint32_t FBPWRMODE;
    uint32_t FBPRDY;
    uint32_t FPAC1;
    uint32_t rsvd5;
    uint32_t FMAC;
    uint32_t FMSTAT;
    uint32_t FEMU_DMSW;
    uint32_t FEMU_DLSW;
    uint32_t FEMU_ECC;
    uint32_t FLOCK;
    uint32_t rsvd6;
    uint32_t FDIAGCTRL;
    uint32_t rsvd7;
    uint32_t FRAW_ADDR;
    uint32_t rsvd8;
    uint32_t FPAR_OVR;
    uint32_t rsvd9[13];
    uint32_t RCR_VALID;
    uint32_t ACC_THRESHOLD;
    uint32_t rsvd10;
    uint32_t FEDACSDIS2;
    uint32_t rsvd11;
    uint32_t rsvd12;
    uint32_t rsvd13;
    uint32_t RCR_VALUE0;
    uint32_t RCR_VALUE1;
    uint32_t rsvd14[108];
    uint32_t FSM_WR_ENA;
    uint32_t rsvd15[11];
    uint32_t EEPROM_CONFIG;
    uint32_t rsvd16;
    uint32_t FSM_SECTOR1;
    uint32_t FSM_SECTOR2;
    uint32_t rsvd17[78];
    uint32_t FCFG_BANK;

} flash_reg_t;


#define FLASH_REG ((flash_reg_t *)(0xFFF87000))
#define FSM_WR_ENA_HL       (*(volatile uint32_t *)0xFFF87288)
#define EEPROM_CONFIG_HL    (*(volatile uint32_t *)0xFFF872B8)
/**
 * @brief Flash power modes.
 */
 typedef enum FLASH_POWER_MODE
 {
     SYS_SLEEP   = 0U, /**< Alias for flash bank power mode sleep   */
     SYS_STANDBY = 1U, /**< Alias for flash bank power mode standby */
     SYS_ACTIVE  = 3U  /**< Alias for flash bank power mode active  */
 }FLASH_POWER_MODE_E;
 
 /** @enum SYS_CLOCK_SOURCE_E
 *   @brief Alias names for clock sources
 */
 typedef enum SYS_CLOCK_SOURCE
 {
     SYS_OSC             = 0x0U,
     SYS_PLL1            = 0x1U,  /**< Alias for Pll1 clock Source                      */
     SYS_EXTERNAL1       = 0x3U,  /**< Alias for external clock Source                  */
     SYS_LPO_LOW         = 0x4U,  /**< Alias for low power oscillator low clock Source  */
     SYS_LPO_HIGH        = 0x5U,  /**< Alias for low power oscillator high clock Source */
     SYS_PLL2            = 0x6U,  /**< Alias for Pll2 clock Source                      */
     SYS_EXTERNAL2       = 0x7U,  /**< Alias for external 2 clock Source                */
     SYS_VCLK            = 0x9U,  /**< Alias for synchronous VCLK1 clock Source         */
     SYS_PLL2_ODCLK_8    = 0xEU,  /**< Alias for PLL2_post_ODCLK/8                      */
     SYS_PLL2_ODCLK_16   = 0xFU   /**< Alias for PLL2_post_ODCLK/8                      */
 } SYS_CLOCK_SOURCE_E;
 
 #define SYS_DOZE_MODE        0x000F3F02
 #define SYS_SNOOZE_MODE      0x000F3F03
 #define SYS_SLEEP_MODE       0x000FFFFF
 #define LPO_TRIM_VALUE       (((*(volatile uint32_t *)0xF00801B4) & 0xFFFF0000)>>16U)
 #define SYS_EXCEPTION        (*(volatile uint32_t *)0xFFFFFFE4)
 
static void init_periph(void)
{
    /** - Disable Peripherals before peripheral powerup*/
    SYS_REG_1_BASE->CLKCNTL &= 0xFFFFFEFF;

    /** - Release peripherals from reset and enable clocks to all peripherals */
    /** - Power-up all peripherals */
    PCR_REG_1->PSPWRDWNCLR0 = 0xFFFFFFFF;
    PCR_REG_1->PSPWRDWNCLR1 = 0xFFFFFFFF;
    PCR_REG_1->PSPWRDWNCLR2 = 0xFFFFFFFF;
    PCR_REG_1->PSPWRDWNCLR3 = 0xFFFFFFFF;
    PCR_REG_2->PSPWRDWNCLR0 = 0xFFFFFFFF;
    PCR_REG_2->PSPWRDWNCLR1 = 0xFFFFFFFF;
    PCR_REG_2->PSPWRDWNCLR2 = 0xFFFFFFFF;
    PCR_REG_2->PSPWRDWNCLR3 = 0xFFFFFFFF;
    PCR_REG_3->PSPWRDWNCLR0 = 0xFFFFFFFF;
    PCR_REG_3->PSPWRDWNCLR1 = 0xFFFFFFFF;
    PCR_REG_3->PSPWRDWNCLR2 = 0xFFFFFFFF;
    PCR_REG_3->PSPWRDWNCLR3 = 0xFFFFFFFF;

    /** - Enable Peripherals */
    SYS_REG_1_BASE->CLKCNTL |= 0x00000100U;
}

static void init_pll(void)
{
    /* Disable PLL1 and PLL2 */
    SYS_REG_1_BASE->CSDISSET = 0x00000002U | 0x00000040U;
    while((SYS_REG_1_BASE->CSDIS & 0x42U) != 0x42U)
    {
    /* Wait */
    }

    /* Clear Global Status Register */
    SYS_REG_1_BASE->GBLSTAT = 0x301U;

    /** - Configure PLL control registers */
    /** @b Initialize @b Pll1: */

    /**   - Setup pll control register 1:
    *     - Setup reset on oscillator slip
    *     - Setup bypass on pll slip
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reset on oscillator fail
    *     - Setup reference clock divider
    *     - Setup Pll multiplier
    */
    SYS_REG_1_BASE->PLLCTL1 =  (uint32_t)0x00000000U
                        |  (uint32_t)0x20000000U
                        |  (uint32_t)((uint32_t)0x1FU << 24U)
                        |  (uint32_t)0x00000000U
                        |  (uint32_t)((uint32_t)(8U - 1U)<< 16U)
                        |  (uint32_t)(0x9500U);

    /**   - Setup pll control register 2
    *     - Setup spreading rate
    *     - Setup bandwidth adjustment
    *     - Setup internal Pll output divider
    *     - Setup spreading amount
    */
    SYS_REG_1_BASE->PLLCTL2 =  (uint32_t)((uint32_t)255U << 22U)
                        |  (uint32_t)((uint32_t)7U << 12U)
                        |  (uint32_t)((uint32_t)(1U - 1U) << 9U)
                        |  (uint32_t)61U;

    /** @b Initialize @b Pll2: */

    /**   - Setup pll2 control register :
    *     - setup Pll output clock divider to max before Lock
    *     - Setup reference clock divider
    *     - Setup internal Pll output divider
    *     - Setup Pll multiplier
    */
    SYS_REG_2_BASE->PLLCTL3 = (uint32_t)((uint32_t)(1U - 1U) << 29U)
                        | (uint32_t)((uint32_t)0x1FU << 24U)
                        | (uint32_t)((uint32_t)(8U - 1U)<< 16U)
                        | (uint32_t)(0x9500U);

    /** - Enable PLL(s) to start up or Lock */
    SYS_REG_1_BASE->CSDIS = 0x00000000U
                      | 0x00000000U
                      | 0x00000008U
                      | 0x00000080U
                      | 0x00000000U
                      | 0x00000000U
                      | 0x00000000U
                      | 0x00000004U;
}

static void init_flash(void)
{
    /** - Setup flash read mode, address wait states and data wait states */
    FLASH_REG->FRDCNTL =  0x00000000U
                       | (uint32_t)((uint32_t)3U << 8U)
                       |  3U;

    /** - Setup flash access wait states for bank 7 */
    FSM_WR_ENA_HL    = 0x5U;
    EEPROM_CONFIG_HL = 0x00000002U
                     | (uint32_t)((uint32_t)9U << 16U);

    /** - Disable write access to flash state machine registers */
    FSM_WR_ENA_HL    = 0x2U;

    /** - Setup flash bank power modes */
    FLASH_REG->FBPWRMODE = 0x00000000U
                          | (uint32_t)((uint32_t)SYS_ACTIVE << 14U) /* BANK 7 */
                          | (uint32_t)((uint32_t)SYS_ACTIVE << 2U)  /* BANK 1 */
                          | (uint32_t)((uint32_t)SYS_ACTIVE << 0U); /* BANK 0 */
}

static void init_clock(void)
{
    uint32_t SYS_CSVSTAT, SYS_CSDIS;

    /** @b Initialize @b Clock @b Tree: */
    /** - Setup system clock divider for HCLK */
    SYS_REG_2_BASE->HCLKCNTL = 1U;

    /** - Disable / Enable clock domain */
    SYS_REG_1_BASE->CDDIS = (uint32_t)((uint32_t)0U << 4U ) /* AVCLK1 , 1 - OFF, 0 - ON */
                      | (uint32_t)((uint32_t)1U << 5U ) /* AVCLK2 , 1 - OFF, 0 - ON */
                      | (uint32_t)((uint32_t)0U << 8U ) /* VCLK3 , 1 - OFF, 0 - ON */
                      | (uint32_t)((uint32_t)0U << 9U ) /* VCLK4 , 1 - OFF, 0 - ON */
                      | (uint32_t)((uint32_t)0U << 10U) /* AVCLK3 , 1 - OFF, 0 - ON */
                      | (uint32_t)((uint32_t)0U << 11U); /* AVCLK4 , 1 - OFF, 0 - ON */


    /* Always check the CSDIS register to make sure the clock source is turned on and check
     * the CSVSTAT register to make sure the clock source is valid. Then write to GHVSRC to switch the clock.
     */
    /** - Wait for until clocks are locked */
    SYS_CSVSTAT = SYS_REG_1_BASE->CSVSTAT;
    SYS_CSDIS = SYS_REG_1_BASE->CSDIS;
    while ((SYS_CSVSTAT & ((SYS_CSDIS ^ 0xFFU) & 0xFFU)) != ((SYS_CSDIS ^ 0xFFU) & 0xFFU))
    {
        SYS_CSVSTAT = SYS_REG_1_BASE->CSVSTAT;
        SYS_CSDIS = SYS_REG_1_BASE->CSDIS;
    } /* Wait */

    /** - Map device clock domains to desired sources and configure top-level dividers */
    /** - All clock domains are working off the default clock sources until now */
    /** - The below assignments can be easily modified using the HALCoGen GUI */

    /** - Setup GCLK, HCLK and VCLK clock source for normal operation, power down mode and after wakeup */
    SYS_REG_1_BASE->GHVSRC = (uint32_t)((uint32_t)SYS_PLL1 << 24U)
                       | (uint32_t)((uint32_t)SYS_PLL1 << 16U)
                       | (uint32_t)((uint32_t)SYS_PLL1 << 0U);

    /** - Setup RTICLK1 and RTICLK2 clocks */
    SYS_REG_1_BASE->RCLKSRC = (uint32_t)((uint32_t)1U << 24U)        /* RTI2 divider (Not applicable for lock-step device)  */
                        | (uint32_t)((uint32_t)SYS_VCLK << 16U) /* RTI2 clock source (Not applicable for lock-step device) */
                        | (uint32_t)((uint32_t)1U << 8U)         /* RTI1 divider */
                        | (uint32_t)((uint32_t)SYS_VCLK << 0U); /* RTI1 clock source */

    /** - Setup asynchronous peripheral clock sources for AVCLK1 and AVCLK2 */
    SYS_REG_1_BASE->VCLKASRC = (uint32_t)((uint32_t)SYS_VCLK << 8U)
                         | (uint32_t)((uint32_t)SYS_VCLK << 0U);

    /** - Setup synchronous peripheral clock dividers for VCLK1, VCLK2, VCLK3 */
    SYS_REG_1_BASE->CLKCNTL  = (SYS_REG_1_BASE->CLKCNTL & 0xF0FFFFFFU)
                         | (uint32_t)((uint32_t)1U << 24U);
    SYS_REG_1_BASE->CLKCNTL  = (SYS_REG_1_BASE->CLKCNTL & 0xFFF0FFFFU)
                         | (uint32_t)((uint32_t)1U << 16U);

    SYS_REG_2_BASE->CLK2CNTRL = (SYS_REG_2_BASE->CLK2CNTRL & 0xFFFFFFF0U)
                         | (uint32_t)((uint32_t)1U << 0U);

    SYS_REG_2_BASE->VCLKACON1 =  (uint32_t)((uint32_t)(1U - 1U) << 24U)
                           | (uint32_t)((uint32_t)0U << 20U)
                           | (uint32_t)((uint32_t)SYS_VCLK << 16U)
                           | (uint32_t)((uint32_t)(1U - 1U) << 8U)
                           | (uint32_t)((uint32_t)0U << 4U)
                           | (uint32_t)((uint32_t)SYS_VCLK << 0U);

    /* Now the PLLs are locked and the PLL outputs can be sped up */
    /* The R-divider was programmed to be 0xF. Now this divider is changed to programmed value */
    SYS_REG_1_BASE->PLLCTL1 = (SYS_REG_1_BASE->PLLCTL1 & 0xE0FFFFFFU) | (uint32_t)((uint32_t)(1U - 1U) << 24U);
    /*SAFETYMCUSW 134 S MR:12.2 <APPROVED> " Clear and write to the volatile register " */
    SYS_REG_2_BASE->PLLCTL3 = (SYS_REG_2_BASE->PLLCTL3 & 0xE0FFFFFFU) | (uint32_t)((uint32_t)(1U - 1U) << 24U);

    /* Enable/Disable Frequency modulation */
    SYS_REG_1_BASE->PLLCTL2 |= 0x00000000U;
}

static void init_pins(void)
{
    /** - set ECLK pins functional mode */
    SYS_REG_1_BASE->SYSPC1 = 0U;

    /** - set ECLK pins default output value */
    SYS_REG_1_BASE->SYSPC4 = 0U;

    /** - set ECLK pins output direction */
    SYS_REG_1_BASE->SYSPC2 = 1U;

    /** - set ECLK pins open drain enable */
    SYS_REG_1_BASE->SYSPC7 = 0U;

    /** - set ECLK pins pullup/pulldown enable */
    SYS_REG_1_BASE->SYSPC8 = 0U;

    /** - set ECLK pins pullup/pulldown select */
    SYS_REG_1_BASE->SYSPC9 = 1U;

    /** - Setup ECLK */
    SYS_REG_1_BASE->ECPCNTL = (uint32_t)((uint32_t)0U << 24U)
                        | (uint32_t)((uint32_t)0U << 23U)
                        | (uint32_t)((uint32_t)(8U - 1U) & 0xFFFFU);
}

static void init_lpo(void)
{
    uint32_t u32clocktestConfig;
    /* Save user clocktest register configuration */
    u32clocktestConfig = SYS_REG_1_BASE->CLKTEST;

    /*The TRM states OTP TRIM value should be stepped to avoid large changes in the HF LPO clock that would result in a LPOCLKMON fault. At issue is the TRM does not specify what the maximum step is so there is no metric to use for the SW implementation - the routine can temporarily disable the LPOCLKMON range check so the sudden change will not cause a fault.*/
    /* Disable clock range detection*/

    SYS_REG_1_BASE->CLKTEST = (SYS_REG_1_BASE->CLKTEST
                        | (uint32_t)((uint32_t)0x1U << 24U))
                        & (uint32_t)(~((uint32_t)0x1U << 25U));
    /*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Hardware status bit read check" */
    if(LPO_TRIM_VALUE != 0xFFFFU)
    {

        SYS_REG_1_BASE->LPOMONCTL  = (uint32_t)((uint32_t)1U << 24U)
                               | (uint32_t)((uint32_t)LPO_TRIM_VALUE);
    }
    else
    {

        SYS_REG_1_BASE->LPOMONCTL   = (uint32_t)((uint32_t)1U << 24U)
                                     | (uint32_t)((uint32_t)16U << 8U)
                                     | (uint32_t)((uint32_t)16U);

    }

    /* Restore the user clocktest register value configuration */
    SYS_REG_1_BASE->CLKTEST = u32clocktestConfig;

}

void ja_bsp_init(void)
{
    init_pll();
    init_periph();
    init_lpo();
    init_flash();
    init_clock();
    init_pins();
    init_serial();
    // __TI_auto_init();
    serial_write("BSP Initialized\r\n", 17);

    // init_vim();
    // serial_write("VIM Initialized\r\n", 17); //TODO: enable vim

    init_rti();
    serial_write("RTI Initialized\r\n", 17);

    jet_console_init_all();
    serial_write("Console Initialized\r\n", 21);

    rtiEnableNotification(rtiREG1, rtiNOTIFICATION_COMPARE0);
    rtiSetPeriod(rtiREG1, rtiCOMPARE0, RTI_FREQUENCY / POK_TIMER_FREQUENCY);
    rtiStartCounter(rtiREG1, 0);
    rtiStartCounter(rtiREG1, 1);
    serial_write("Timers Initialized\r\n", 20);
}

void bsp_soft_reset(void)
{
    SYS_REG_1_BASE->SYSECR |= (1 << 15);
}
