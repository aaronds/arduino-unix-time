#include <UnixTimeChron.h>

UnixTimeChronAction::UnixTimeChronAction(unsigned long long t,unsigned long long r){
	time = t;
	repeat = r;
	next = NULL;
}

void UnixTimeChronAction::go(unsigned long long time){

}

UnixTimeChronCallbackAction::UnixTimeChronCallbackAction(unsigned long long t,unsigned long r,void (*cb) (unsigned long long t,void *d),void *d) : UnixTimeChronAction(t,r) {
	data = d;
	callback = cb;
}

void UnixTimeChronCallbackAction::go(unsigned long long time){
	(*callback) (time,data);
}

UnixTimeChron::UnixTimeChron(){
       first = NULL;
}

void UnixTimeChron::add(UnixTimeChronAction *action){
	if(!first){
		first = action;
	}else{
		action->next = first;
		first = action;
	}
}

void UnixTimeChron::init(UnixTime *r){
	rtc = r;
	lastPoll = r->getTime();
}

void UnixTimeChron::rem(UnixTimeChronAction *action){
	UnixTimeChronAction *prev;

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

void UnixTimeChron::poll(){
	UnixTimeChronAction *tmp;
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

