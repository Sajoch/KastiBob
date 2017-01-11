#include "thing.hpp"
#include <iostream>

using namespace std;

Thing::Thing(){
	
}


Thing::Thing(NetworkPacket& p){
	cout<<"thing"<<endl;
	uint32_t type = p.getUint16();
	switch(type){
		case 0x61:
			cout<<"new creature"<<endl;
		break;
		case 0x62:
			cout<<"creature"<<endl;
		break;
		case 0x63:
			cout<<"turn"<<endl;
		break;
		default:
			cout<<"type "<<type<<endl;
			error = 1;
		break;
	}
}

bool Thing::good(){
	return error==0?true:false;
}