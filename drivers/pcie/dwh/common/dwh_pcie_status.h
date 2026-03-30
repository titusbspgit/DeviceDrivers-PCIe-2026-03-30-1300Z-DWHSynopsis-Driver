/*
 * dwh_pcie_status.h - Common status codes
 * RCI-ag-DrvGen Agent
 */
#ifndef DWH_PCIE_STATUS_H
#define DWH_PCIE_STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    DWH_OK = 0,
    DWH_E_TIMEOUT = -1,
    DWH_E_PARAM = -2,
    DWH_E_UNSUPPORTED = -3,
    DWH_E_HWSTATE = -4,
    DWH_E_IO = -5,
    DWH_E_BUSY = -6,
    DWH_E_DENIED = -7,
    DWH_E_CRC = -8
} dwh_status_t;

#ifdef __cplusplus
}
#endif

#endif /* DWH_PCIE_STATUS_H */
