	nios_system u0 (
		.flash_ADDR                          (<connected-to-flash_ADDR>),                          //                        flash.ADDR
		.flash_CE_N                          (<connected-to-flash_CE_N>),                          //                             .CE_N
		.flash_OE_N                          (<connected-to-flash_OE_N>),                          //                             .OE_N
		.flash_WE_N                          (<connected-to-flash_WE_N>),                          //                             .WE_N
		.flash_RST_N                         (<connected-to-flash_RST_N>),                         //                             .RST_N
		.flash_DQ                            (<connected-to-flash_DQ>),                            //                             .DQ
		.sdram_addr                          (<connected-to-sdram_addr>),                          //                        sdram.addr
		.sdram_ba                            (<connected-to-sdram_ba>),                            //                             .ba
		.sdram_cas_n                         (<connected-to-sdram_cas_n>),                         //                             .cas_n
		.sdram_cke                           (<connected-to-sdram_cke>),                           //                             .cke
		.sdram_cs_n                          (<connected-to-sdram_cs_n>),                          //                             .cs_n
		.sdram_dq                            (<connected-to-sdram_dq>),                            //                             .dq
		.sdram_dqm                           (<connected-to-sdram_dqm>),                           //                             .dqm
		.sdram_ras_n                         (<connected-to-sdram_ras_n>),                         //                             .ras_n
		.sdram_we_n                          (<connected-to-sdram_we_n>),                          //                             .we_n
		.sdram_clk_clk                       (<connected-to-sdram_clk_clk>),                       //                    sdram_clk.clk
		.sram_DQ                             (<connected-to-sram_DQ>),                             //                         sram.DQ
		.sram_ADDR                           (<connected-to-sram_ADDR>),                           //                             .ADDR
		.sram_LB_N                           (<connected-to-sram_LB_N>),                           //                             .LB_N
		.sram_UB_N                           (<connected-to-sram_UB_N>),                           //                             .UB_N
		.sram_CE_N                           (<connected-to-sram_CE_N>),                           //                             .CE_N
		.sram_OE_N                           (<connected-to-sram_OE_N>),                           //                             .OE_N
		.sram_WE_N                           (<connected-to-sram_WE_N>),                           //                             .WE_N
		.system_pll_ref_clk_clk              (<connected-to-system_pll_ref_clk_clk>),              //           system_pll_ref_clk.clk
		.system_pll_ref_reset_reset          (<connected-to-system_pll_ref_reset_reset>),          //         system_pll_ref_reset.reset
		.cam_in_0_external_connection_export (<connected-to-cam_in_0_external_connection_export>), // cam_in_0_external_connection.export
		.cam_in_1_external_connection_export (<connected-to-cam_in_1_external_connection_export>), // cam_in_1_external_connection.export
		.cam_in_2_external_connection_export (<connected-to-cam_in_2_external_connection_export>), // cam_in_2_external_connection.export
		.cam_in_3_external_connection_export (<connected-to-cam_in_3_external_connection_export>), // cam_in_3_external_connection.export
		.cam_in_4_external_connection_export (<connected-to-cam_in_4_external_connection_export>), // cam_in_4_external_connection.export
		.cam_in_5_external_connection_export (<connected-to-cam_in_5_external_connection_export>), // cam_in_5_external_connection.export
		.cam_in_6_external_connection_export (<connected-to-cam_in_6_external_connection_export>), // cam_in_6_external_connection.export
		.cam_in_7_external_connection_export (<connected-to-cam_in_7_external_connection_export>), // cam_in_7_external_connection.export
		.cam_in_8_external_connection_export (<connected-to-cam_in_8_external_connection_export>), // cam_in_8_external_connection.export
		.cam_in_9_external_connection_export (<connected-to-cam_in_9_external_connection_export>)  // cam_in_9_external_connection.export
	);

