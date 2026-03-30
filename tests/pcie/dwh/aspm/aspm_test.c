#include <stdint.h>
#include <stdio.h>
#include "../../../drivers/pcie/dwh/aspm/dwh_pcie_aspm.h"
#include "../../../drivers/pcie/dwh/common/dwh_pcie_regs.h"

static volatile uint32_t mock_dbi[0x1000/4];
static volatile uint32_t mock_pl[0x1000/4];

#undef DWC_PCIE_DBI_BASE
#undef DWC_PCIE_PORT_LOGIC_BASE
#define DWC_PCIE_DBI_BASE ((uintptr_t)mock_dbi)
#define DWC_PCIE_PORT_LOGIC_BASE ((uintptr_t)mock_pl)

int main(void)
{
    mock_dbi[PCIE_CAP_LINK_CONTROL/4] = 0U;
    mock_pl[ACK_F_ASPM_CTRL_OFF/4] = 0U;
    mock_pl[PORT_LINK_CTRL_OFF/4] = 0U;

    dwh_status_t rc = dwh_aspm_set(DWH_ASPM_L0S_L1);
    printf("ASPM rc=%d LC=0x%08x ACK=0x%08x PLC=0x%08x\n", rc,
           mock_dbi[PCIE_CAP_LINK_CONTROL/4],
           mock_pl[ACK_F_ASPM_CTRL_OFF/4],
           mock_pl[PORT_LINK_CTRL_OFF/4]);

    rc = dwh_aspm_set(DWH_ASPM_DISABLE);
    printf("ASPM rc=%d LC=0x%08x ACK=0x%08x PLC=0x%08x\n", rc,
           mock_dbi[PCIE_CAP_LINK_CONTROL/4],
           mock_pl[ACK_F_ASPM_CTRL_OFF/4],
           mock_pl[PORT_LINK_CTRL_OFF/4]);

    return 0;
}
