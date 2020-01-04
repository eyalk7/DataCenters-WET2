#include <new>
#include "library2.h"
#include "DataCentersManager.h"

void* Init(int n) {
    // if (n <= 0) return nullptr;
    try {
        auto *manager = new DataCentersManager(n);
        return (void*)manager;
    } catch (std::bad_alloc& ba) {
        return nullptr;
    }
}

StatusType MergeDataCenters(void *DS, int dataCenter1, int dataCenter2) {
    if (!DS || dataCenter1 <= 0 || dataCenter2 <= 0) return INVALID_INPUT;
    auto manager = (DataCentersManager*)DS;
    try {
        return (StatusType)(manager->MergeDataCenters(dataCenter1, dataCenter2));
    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddServer(void *DS, int dataCenterID, int serverID) {
    if (!DS || dataCenterID <= 0 || serverID <= 0) return INVALID_INPUT;
    auto manager = (DataCentersManager*)DS;
    try {
        return (StatusType)(manager->AddServer(dataCenterID , serverID));
    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveServer(void *DS, int serverID) {
    if (!DS || serverID <= 0) return INVALID_INPUT;
    auto manager = (DataCentersManager*)DS;
    try {
        return (StatusType)(manager->RemoveServer(serverID));
    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
}

StatusType SetTraffic(void *DS, int serverID,  int traffic) {
    if (!DS || serverID <= 0 || traffic < 0) return INVALID_INPUT;
    auto manager = (DataCentersManager*)DS;
    try {
        return (StatusType)(manager->SetTraffic(serverID, traffic));
    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
}

StatusType SumHighestTrafficServers(void *DS, int dataCenterID,  int k, int *traffic) {
    if (!DS || dataCenterID < 0 || k < 0 || !traffic) return INVALID_INPUT;
    auto manager = (DataCentersManager*)DS;
    try {
        return (StatusType)(manager->SumHighestTrafficServers(dataCenterID, k, traffic));
    } catch (std::bad_alloc& ba) {
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS) {
    auto manager = (DataCentersManager*)(*DS);
    delete manager;
    *DS = nullptr;
}
