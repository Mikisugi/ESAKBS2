	component dikkekoek is
		port (
			clk_clk                                 : in std_logic                     := 'X';             -- clk
			reset_reset_n                           : in std_logic                     := 'X';             -- reset_n
			camera_input_external_connection_export : in std_logic_vector(11 downto 0) := (others => 'X')  -- export
		);
	end component dikkekoek;

	u0 : component dikkekoek
		port map (
			clk_clk                                 => CONNECTED_TO_clk_clk,                                 --                              clk.clk
			reset_reset_n                           => CONNECTED_TO_reset_reset_n,                           --                            reset.reset_n
			camera_input_external_connection_export => CONNECTED_TO_camera_input_external_connection_export  -- camera_input_external_connection.export
		);

