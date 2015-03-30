#include "MyDSF.h"
#include "SyncObj.h"
#include "ObjManager.h"

int main(int argc, const char * argv[]) {
    const int NUMBER_OF_OBJS = 100;
    auto dsf = new MyDSF();
    auto om = new ObjManager(dsf);
    SyncObj* sos[NUMBER_OF_OBJS];
    for(int i = 0; i < NUMBER_OF_OBJS; i ++) { // Creates NUMBER_OF_OBJS SyncObj objects
        sos[i] = new SyncObj(i);
        dsf->add(sos[i]); // Adds objects to DSF object
        dsf->send(sos[i], sos[i], om->print, new dsf::TaskArgument(sos[i])); // Sends messages
    }
    dsf->start();
    delete dsf;
    delete om;
    return 0;
}
