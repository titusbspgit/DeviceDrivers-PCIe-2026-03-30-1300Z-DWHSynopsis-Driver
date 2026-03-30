cmake_minimum_required(VERSION 3.13)
project(dwc_pcie_drivers C)

set(CMAKE_C_STANDARD 99)
add_compile_options(-Wall -Wextra -Werror)

include_directories(drivers/pcie/dwh/common)

add_library(dwc_pcie_common
    drivers/pcie/dwh/common/dwh_pcie_base.h
    drivers/pcie/dwh/common/dwh_pcie_regs.h
    drivers/pcie/dwh/common/dwh_pcie_status.h)

add_library(dwc_pcie_flit
    drivers/pcie/dwh/flit_mode/dwh_pcie_flit.c
    drivers/pcie/dwh/flit_mode/dwh_pcie_flit.h)

a dd_library(dwc_pcie_pipe_phy
    drivers/pcie/dwh/pipe_phy/dwh_pcie_pipe_phy.c
    drivers/pcie/dwh/pipe_phy/dwh_pcie_pipe_phy.h)

add_library(dwc_pcie_spcie
    drivers/pcie/dwh/spcie/dwh_pcie_spcie.c
    drivers/pcie/dwh/spcie/dwh_pcie_spcie.h)

add_library(dwc_pcie_link_eq
    drivers/pcie/dwh/link_eq/dwh_pcie_link_eq.c
    drivers/pcie/dwh/link_eq/dwh_pcie_link_eq.h)

add_library(dwc_pcie_aspm
    drivers/pcie/dwh/aspm/dwh_pcie_aspm.c
    drivers/pcie/dwh/aspm/dwh_pcie_aspm.h)

add_executable(flit_test tests/pcie/dwh/flit_mode/flit_test.c)
target_link_libraries(flit_test dwc_pcie_flit)

add_executable(pipe_phy_test tests/pcie/dwh/pipe_phy/pipe_phy_test.c)
target_link_libraries(pipe_phy_test dwc_pcie_pipe_phy)

add_executable(spcie_test tests/pcie/dwh/spcie/spcie_test.c)
target_link_libraries(spcie_test dwc_pcie_spcie)

add_executable(link_eq_test tests/pcie/dwh/link_eq/link_eq_test.c)
target_link_libraries(link_eq_test dwc_pcie_link_eq)

add_executable(aspm_test tests/pcie/dwh/aspm/aspm_test.c)
target_link_libraries(aspm_test dwc_pcie_aspm)
