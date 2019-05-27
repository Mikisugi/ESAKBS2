	component nios_system is
		port (
			flash_ADDR                          : out   std_logic_vector(22 downto 0);                    -- ADDR
			flash_CE_N                          : out   std_logic;                                        -- CE_N
			flash_OE_N                          : out   std_logic;                                        -- OE_N
			flash_WE_N                          : out   std_logic;                                        -- WE_N
			flash_RST_N                         : out   std_logic;                                        -- RST_N
			flash_DQ                            : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- DQ
			sdram_addr                          : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_ba                            : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_cas_n                         : out   std_logic;                                        -- cas_n
			sdram_cke                           : out   std_logic;                                        -- cke
			sdram_cs_n                          : out   std_logic;                                        -- cs_n
			sdram_dq                            : inout std_logic_vector(31 downto 0) := (others => 'X'); -- dq
			sdram_dqm                           : out   std_logic_vector(3 downto 0);                     -- dqm
			sdram_ras_n                         : out   std_logic;                                        -- ras_n
			sdram_we_n                          : out   std_logic;                                        -- we_n
			sdram_clk_clk                       : out   std_logic;                                        -- clk
			sram_DQ                             : inout std_logic_vector(15 downto 0) := (others => 'X'); -- DQ
			sram_ADDR                           : out   std_logic_vector(19 downto 0);                    -- ADDR
			sram_LB_N                           : out   std_logic;                                        -- LB_N
			sram_UB_N                           : out   std_logic;                                        -- UB_N
			sram_CE_N                           : out   std_logic;                                        -- CE_N
			sram_OE_N                           : out   std_logic;                                        -- OE_N
			sram_WE_N                           : out   std_logic;                                        -- WE_N
			system_pll_ref_clk_clk              : in    std_logic                     := 'X';             -- clk
			system_pll_ref_reset_reset          : in    std_logic                     := 'X';             -- reset
			cam_in_0_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_1_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_2_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_3_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_4_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_5_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_6_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_7_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_8_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X'); -- export
			cam_in_9_external_connection_export : in    std_logic_vector(14 downto 0) := (others => 'X')  -- export
		);
	end component nios_system;

	u0 : component nios_system
		port map (
			flash_ADDR                          => CONNECTED_TO_flash_ADDR,                          --                        flash.ADDR
			flash_CE_N                          => CONNECTED_TO_flash_CE_N,                          --                             .CE_N
			flash_OE_N                          => CONNECTED_TO_flash_OE_N,                          --                             .OE_N
			flash_WE_N                          => CONNECTED_TO_flash_WE_N,                          --                             .WE_N
			flash_RST_N                         => CONNECTED_TO_flash_RST_N,                         --                             .RST_N
			flash_DQ                            => CONNECTED_TO_flash_DQ,                            --                             .DQ
			sdram_addr                          => CONNECTED_TO_sdram_addr,                          --                        sdram.addr
			sdram_ba                            => CONNECTED_TO_sdram_ba,                            --                             .ba
			sdram_cas_n                         => CONNECTED_TO_sdram_cas_n,                         --                             .cas_n
			sdram_cke                           => CONNECTED_TO_sdram_cke,                           --                             .cke
			sdram_cs_n                          => CONNECTED_TO_sdram_cs_n,                          --                             .cs_n
			sdram_dq                            => CONNECTED_TO_sdram_dq,                            --                             .dq
			sdram_dqm                           => CONNECTED_TO_sdram_dqm,                           --                             .dqm
			sdram_ras_n                         => CONNECTED_TO_sdram_ras_n,                         --                             .ras_n
			sdram_we_n                          => CONNECTED_TO_sdram_we_n,                          --                             .we_n
			sdram_clk_clk                       => CONNECTED_TO_sdram_clk_clk,                       --                    sdram_clk.clk
			sram_DQ                             => CONNECTED_TO_sram_DQ,                             --                         sram.DQ
			sram_ADDR                           => CONNECTED_TO_sram_ADDR,                           --                             .ADDR
			sram_LB_N                           => CONNECTED_TO_sram_LB_N,                           --                             .LB_N
			sram_UB_N                           => CONNECTED_TO_sram_UB_N,                           --                             .UB_N
			sram_CE_N                           => CONNECTED_TO_sram_CE_N,                           --                             .CE_N
			sram_OE_N                           => CONNECTED_TO_sram_OE_N,                           --                             .OE_N
			sram_WE_N                           => CONNECTED_TO_sram_WE_N,                           --                             .WE_N
			system_pll_ref_clk_clk              => CONNECTED_TO_system_pll_ref_clk_clk,              --           system_pll_ref_clk.clk
			system_pll_ref_reset_reset          => CONNECTED_TO_system_pll_ref_reset_reset,          --         system_pll_ref_reset.reset
			cam_in_0_external_connection_export => CONNECTED_TO_cam_in_0_external_connection_export, -- cam_in_0_external_connection.export
			cam_in_1_external_connection_export => CONNECTED_TO_cam_in_1_external_connection_export, -- cam_in_1_external_connection.export
			cam_in_2_external_connection_export => CONNECTED_TO_cam_in_2_external_connection_export, -- cam_in_2_external_connection.export
			cam_in_3_external_connection_export => CONNECTED_TO_cam_in_3_external_connection_export, -- cam_in_3_external_connection.export
			cam_in_4_external_connection_export => CONNECTED_TO_cam_in_4_external_connection_export, -- cam_in_4_external_connection.export
			cam_in_5_external_connection_export => CONNECTED_TO_cam_in_5_external_connection_export, -- cam_in_5_external_connection.export
			cam_in_6_external_connection_export => CONNECTED_TO_cam_in_6_external_connection_export, -- cam_in_6_external_connection.export
			cam_in_7_external_connection_export => CONNECTED_TO_cam_in_7_external_connection_export, -- cam_in_7_external_connection.export
			cam_in_8_external_connection_export => CONNECTED_TO_cam_in_8_external_connection_export, -- cam_in_8_external_connection.export
			cam_in_9_external_connection_export => CONNECTED_TO_cam_in_9_external_connection_export  -- cam_in_9_external_connection.export
		);

