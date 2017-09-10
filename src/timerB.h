/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42, by Joerg Wunsch):
 * <rafaellcoellho@gmail.com> wrote this file.  As long as you retain this notice
 * you can do whatever you want with this stuff. If we meet some day, and you 
 * think this stuff is worth it, you can buy me a beer in return.
 * ----------------------------------------------------------------------------
 */

/*
	@file					timerb.h
	@autor					Rafael Coelho <rafaellcoellho@gmail.com>
	@brief					Biblioteca do timerb
	@details

*/


#ifndef TIMERB_H_
	#define TIMERB_H_

	#include <stdint.h>
	#include <stdbool.h>

	unsigned long millis(void);
	void timerbStart(unsigned int countVal);
	unsigned long int timerbRead(void);
	void timerbWait(void);
	bool timerbFinished(void);
	void timerbInit(void);

#endif /* TIMERB_H_ */
