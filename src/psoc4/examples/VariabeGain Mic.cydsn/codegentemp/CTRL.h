/*******************************************************************************
* File Name: CTRL.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CTRL_H) /* Pins CTRL_H */
#define CY_PINS_CTRL_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CTRL_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} CTRL_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CTRL_Read(void);
void    CTRL_Write(uint8 value);
uint8   CTRL_ReadDataReg(void);
#if defined(CTRL__PC) || (CY_PSOC4_4200L) 
    void    CTRL_SetDriveMode(uint8 mode);
#endif
void    CTRL_SetInterruptMode(uint16 position, uint16 mode);
uint8   CTRL_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CTRL_Sleep(void); 
void CTRL_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CTRL__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CTRL_DRIVE_MODE_BITS        (3)
    #define CTRL_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CTRL_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CTRL_SetDriveMode() function.
         *  @{
         */
        #define CTRL_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CTRL_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CTRL_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CTRL_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CTRL_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CTRL_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CTRL_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CTRL_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CTRL_MASK               CTRL__MASK
#define CTRL_SHIFT              CTRL__SHIFT
#define CTRL_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CTRL_SetInterruptMode() function.
     *  @{
     */
        #define CTRL_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CTRL_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CTRL_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CTRL_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CTRL__SIO)
    #define CTRL_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CTRL__PC) && (CY_PSOC4_4200L)
    #define CTRL_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CTRL_USBIO_DISABLE              ((uint32)(~CTRL_USBIO_ENABLE))
    #define CTRL_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CTRL_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CTRL_USBIO_ENTER_SLEEP          ((uint32)((1u << CTRL_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CTRL_USBIO_SUSPEND_DEL_SHIFT)))
    #define CTRL_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CTRL_USBIO_SUSPEND_SHIFT)))
    #define CTRL_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CTRL_USBIO_SUSPEND_DEL_SHIFT)))
    #define CTRL_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CTRL__PC)
    /* Port Configuration */
    #define CTRL_PC                 (* (reg32 *) CTRL__PC)
#endif
/* Pin State */
#define CTRL_PS                     (* (reg32 *) CTRL__PS)
/* Data Register */
#define CTRL_DR                     (* (reg32 *) CTRL__DR)
/* Input Buffer Disable Override */
#define CTRL_INP_DIS                (* (reg32 *) CTRL__PC2)

/* Interrupt configuration Registers */
#define CTRL_INTCFG                 (* (reg32 *) CTRL__INTCFG)
#define CTRL_INTSTAT                (* (reg32 *) CTRL__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CTRL_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CTRL__SIO)
    #define CTRL_SIO_REG            (* (reg32 *) CTRL__SIO)
#endif /* (CTRL__SIO_CFG) */

/* USBIO registers */
#if !defined(CTRL__PC) && (CY_PSOC4_4200L)
    #define CTRL_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CTRL_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CTRL_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CTRL_DRIVE_MODE_SHIFT       (0x00u)
#define CTRL_DRIVE_MODE_MASK        (0x07u << CTRL_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CTRL_H */


/* [] END OF FILE */
