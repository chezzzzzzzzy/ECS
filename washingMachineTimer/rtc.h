#ifndef RTC_H
#define	RTC_H

#include <xc.h> // include processor files - each processor file is guarded.  
void start_timer(void);
long get_timeElapsed(void);
void timer_callback(void);
void timer_init(void);
#endif	/* RTC_H */