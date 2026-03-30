#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../../drivers/pcie/dwh/flit_mode/dwh_pcie_flit.h"

#ifndef TEST_MODE
#define TEST_MODE 0
#endif

static volatile uint32_t mock_dbi[0x1000/4];
static volatile uint32_t mock_pl[0x1000/4];

#undef DWC_PCIE_DBI_BASE
#undef DWC_PCIE_PORT_LOGIC_BASE
#define DWC_PCIE_DBI_BASE ((uintptr_t)mock_dbi)
#define DWC_PCIE_PORT_LOGIC_BASE ((uintptr_t)mock_pl)

int main(void)
{
    dwh_pcie_ctx_t ctx;
    if (dwh_pcie_init(&ctx) != DWH_OK) {
        printf("INIT FAIL\n");
        return -1;
    }

    /* Build a mock ext cap chain: PL64G at 0x100 */
    mock_dbi[0x100/4] = (uint32_t)PL64G_CAP_ID; /* id */
    mock_dbi[(0x100 + PL64G_STATUS_OFF)/4] = 0U; /* status */

    /* Link Status2 flit status initially 0 */
    mock_dbi[PCIE_CAP_LINK_STATUS2/4] = 0U;

    bool has = dwh_pcie_flit_cap_present();
    printf("FLIT CAP: %s\n", has ? "Y" : "N");

    uint32_t cap=0, st=0;
    dwh_status_t rc = dwh_pcie_flit_read_cap_status(&cap, &st);
    printf("FLIT CAP/STS rc=%d cap=0x%08x st=0x%08x\n", rc, cap, st);

    /* Simulate enable by toggling status bit in Link Status2 */
    mock_dbi[PCIE_CAP_LINK_STATUS2/4] = (uint32_t)PCIE_LS2_FLIT_MODE_STATUS_MASK;
    bool act = dwh_pcie_flit_link_active();
    printf("FLIT ACTIVE: %s\n", act ? "Y" : "N");

    rc = dwh_pcie_flit_enable(10U);
    printf("EN rc=%d\n", rc);

    mock_dbi[PCIE_CAP_LINK_STATUS2/4] = 0U;
    rc = dwh_pcie_flit_disable(10U);
    printf("DIS rc=%d\n", rc);

    return 0;
}
