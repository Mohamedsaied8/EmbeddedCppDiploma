/* @file 			 : NVIC.c
*  @Description: This file includes the Functions Implementation of the NVIC Register Access and interrupt Enable per
                 Request.
This source file should include functions to do the following 
@NVIC Enable Int. Request
@NVIC Disable Int. Request
@NVIC Get pending Int. Request
@NVIC Set pending Int. Request
@NVIC Get Active  Int. Request

*	  @Author: 		 Mohamed Saied     & 			Mohamed Abdallah
*/
#include "nvic.h"


/** @brief enable Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_enable_irq(NVIC_EXTI0_IRQ);
*/
void nvic_enable_irq(u8 irqn)
{
	NVIC_ISER(irqn / 32) = (1 << (irqn % 32));
}

/** @brief disable Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_disable_irq(NVIC_EXTI1_IRQ);
*/
void nvic_disable_irq(u8 irqn)
{
	NVIC_ICER(irqn / 32) = (1 << (irqn % 32));
}
/** @brief Get the pending Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_get_pending_irq(NVIC_EXTI2_IRQ);
*/
u8 nvic_get_pending_irq(u8 irqn)
{
	return NVIC_ISPR(irqn / 32) & (1 << (irqn % 32)) ? 1 : 0;
}
/** @brief Set the pending Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_set_pending_irq(NVIC_WWDG_IRQ);
*/
void nvic_set_pending_irq(u8 irqn)
{
	NVIC_ISPR(irqn / 32) = (1 << (irqn % 32));
}
/** @brief Clear the pending Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_clear_pending_irq(NVIC_ADC1_2_IRQ);
*/
void nvic_clear_pending_irq(u8 irqn)
{
	NVIC_ICPR(irqn / 32) = (1 << (irqn % 32));
}
/** @brief Get the Active Interrupt for the desired peripheral request (check if this peripheral has sent IRQ).
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_get_active_irq(NVIC_ADC1_2_IRQ);
*/
u8 nvic_get_active_irq(u8 irqn)
{
	return NVIC_IABR(irqn / 32) & (1 << (irqn % 32)) ? 1 : 0;
}
/** @brief Get the Active Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_get_irq_enabled(NVIC_ADC1_2_IRQ);
*/
u8 nvic_get_irq_enabled(u8 irqn)
{
	return NVIC_ISER(irqn / 32) & (1 << (irqn % 32)) ? 1 : 0;
}
/** @brief Set the priority Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@param[in] interrupt priority
		@example nvic_set_priority(NVIC_ADC1_2_IRQ);
*/
void nvic_set_priority(u8 irqn, u8 priority)
{
	NVIC_IPR(irqn) = priority;
}
/** @brief Generate Software Interrupt for the desired peripheral request.
		@param[in] interrupt Request which represents IRQ from peripheral
		@example nvic_generate_software_interrupt(NVIC_ADC1_2_IRQ);
*/
void nvic_generate_software_interrupt(u8 irqn)
{
	if (irqn <= 239)
		NVIC_STIR |= irqn;
}
