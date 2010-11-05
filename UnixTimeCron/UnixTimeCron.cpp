#include <UnixTimeCron.h>

UnixTimeCronAction::UnixTimeCronAction(unsigned long long t,unsigned long long r){
	time = t;
	repeat = r;
	next = NULL;
}

void UnixTimeCronAction::go(unsigned long long time){

}

UnixTimeCronCallbackAction::UnixTimeCronCallbackAction(unsigned long long t,unsigned long r,void (*cb) (unsigned long long t,void *d),void *d) : UnixTimeCronAction(t,r) {
	data = d;
	callback = cb;
}

void UnixTimeCronCallbackAction::go(unsigned long long time){
	(*callback) (time,data);
}

UnixTimeCron::UnixTimeCron(){
       first = NULL;
}

void UnixTimeCron::add(UnixTimeCronAction *action){
	if(!first){
		first = action;
	}else{
		action->next = first;
		first = action;
	}
}

void UnixTimeCron::init(UnixTime *r){
	rtc = r;
	lastPoll = r->getTime();
}

void UnixTimeCron::rem(UnixTimeCronAction *action){
	UnixTimeCronAction *prev;

	if(action == first){
		first = action->next;
		action->next = NULL;
		return;
	}

	prev = first;

	while(prev){
		if(prev->next == action){
			prev->next = action->next;
			action->next = NULL;
			break;
		}
		prev = prev->next;
	}
}

void UnixTimeCron::poll(){
	UnixTimeCronAction *tmp;
	while(lastPoll < rtc->getTime()){
		lastPoll++;
		tmp = first;

		while(tmp){
			if(tmp->repeat){
				tmp->time++;
				if(tmp->time >= tmp->repeat){
					tmp->go(lastPoll);
					tmp->time = 0;
				}
			}else if(!tmp->repeat && tmp->time == lastPoll){
				tmp->go(lastPoll);
			}
			tmp = tmp->next;
		}
	}
}

