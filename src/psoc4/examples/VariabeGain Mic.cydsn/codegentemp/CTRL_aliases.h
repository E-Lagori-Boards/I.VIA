/*******************************************************************************
* File Name: CTRL.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CTRL_ALIASES_H) /* Pins CTRL_ALIASES_H */
#define CY_PINS_CTRL_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CTRL_0			(CTRL__0__PC)
#define CTRL_0_PS		(CTRL__0__PS)
#define CTRL_0_PC		(CTRL__0__PC)
#define CTRL_0_DR		(CTRL__0__DR)
#define CTRL_0_SHIFT	(CTRL__0__SHIFT)
#define CTRL_0_INTR	((uint16)((uint16)0x0003u << (CTRL__0__SHIFT*2u)))

#define CTRL_INTR_ALL	 ((uint16)(CTRL_0_INTR))


#endif /* End Pins CTRL_ALIASES_H */


/* [] END OF FILE */
