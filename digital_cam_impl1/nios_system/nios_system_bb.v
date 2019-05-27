
module nios_system (
	flash_ADDR,
	flash_CE_N,
	flash_OE_N,
	flash_WE_N,
	flash_RST_N,
	flash_DQ,
	sdram_addr,
	sdram_ba,
	sdram_cas_n,
	sdram_cke,
	sdram_cs_n,
	sdram_dq,
	sdram_dqm,
	sdram_ras_n,
	sdram_we_n,
	sdram_clk_clk,
	sram_DQ,
	sram_ADDR,
	sram_LB_N,
	sram_UB_N,
	sram_CE_N,
	sram_OE_N,
	sram_WE_N,
	system_pll_ref_clk_clk,
	system_pll_ref_reset_reset,
	cam_in_0_external_connection_export,
	cam_in_1_external_connection_export,
	cam_in_2_external_connection_export,
	cam_in_3_external_connection_export,
	cam_in_4_external_connection_export,
	cam_in_5_external_connection_export,
	cam_in_6_external_connection_export,
	cam_in_7_external_connection_export,
	cam_in_8_external_connection_export,
	cam_in_9_external_connection_export);	

	output	[22:0]	flash_ADDR;
	output		flash_CE_N;
	output		flash_OE_N;
	output		flash_WE_N;
	output		flash_RST_N;
	inout	[7:0]	flash_DQ;
	output	[12:0]	sdram_addr;
	output	[1:0]	sdram_ba;
	output		sdram_cas_n;
	output		sdram_cke;
	output		sdram_cs_n;
	inout	[31:0]	sdram_dq;
	output	[3:0]	sdram_dqm;
	output		sdram_ras_n;
	output		sdram_we_n;
	output		sdram_clk_clk;
	inout	[15:0]	sram_DQ;
	output	[19:0]	sram_ADDR;
	output		sram_LB_N;
	output		sram_UB_N;
	output		sram_CE_N;
	output		sram_OE_N;
	output		sram_WE_N;
	input		system_pll_ref_clk_clk;
	input		system_pll_ref_reset_reset;
	input	[14:0]	cam_in_0_external_connection_export;
	input	[14:0]	cam_in_1_external_connection_export;
	input	[14:0]	cam_in_2_external_connection_export;
	input	[14:0]	cam_in_3_external_connection_export;
	input	[14:0]	cam_in_4_external_connection_export;
	input	[14:0]	cam_in_5_external_connection_export;
	input	[14:0]	cam_in_6_external_connection_export;
	input	[14:0]	cam_in_7_external_connection_export;
	input	[14:0]	cam_in_8_external_connection_export;
	input	[14:0]	cam_in_9_external_connection_export;
endmodule
