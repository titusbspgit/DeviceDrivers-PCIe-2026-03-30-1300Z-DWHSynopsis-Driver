Synopsys DesignWare PCIe (DM v6.00a) per-feature drivers

Integration notes
- Define DWC_PCIE_DBI_BASE and DWC_PCIE_PORT_LOGIC_BASE to map the controller DBI and Port Logic windows.
- Big-endian CPU is assumed; set DWC_PCIE_MMIO_LE_SPACE=1 if MMIO windows are little-endian.
- Extended capability helper walks from 0x100 using next pointer[31:20].

Limitations
- Some bitfields are placeholders pending full manual field tables.
- Debug Link EQ features should not be used on production.
