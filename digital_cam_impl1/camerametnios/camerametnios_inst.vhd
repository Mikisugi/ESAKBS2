	component camerametnios is
		port (
			camera_input_0_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_1_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_2_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_3_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_4_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_5_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_6_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_7_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_8_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			camera_input_9_external_connection_export : in std_logic_vector(14 downto 0) := (others => 'X'); -- export
			clk_clk                                   : in std_logic                     := 'X';             -- clk
			reset_reset_n                             : in std_logic                     := 'X'              -- reset_n
		);
	end component camerametnios;

	u0 : component camerametnios
		port map (
			camera_input_0_external_connection_export => CONNECTED_TO_camera_input_0_external_connection_export, -- camera_input_0_external_connection.export
			camera_input_1_external_connection_export => CONNECTED_TO_camera_input_1_external_connection_export, -- camera_input_1_external_connection.export
			camera_input_2_external_connection_export => CONNECTED_TO_camera_input_2_external_connection_export, -- camera_input_2_external_connection.export
			camera_input_3_external_connection_export => CONNECTED_TO_camera_input_3_external_connection_export, -- camera_input_3_external_connection.export
			camera_input_4_external_connection_export => CONNECTED_TO_camera_input_4_external_connection_export, -- camera_input_4_external_connection.export
			camera_input_5_external_connection_export => CONNECTED_TO_camera_input_5_external_connection_export, -- camera_input_5_external_connection.export
			camera_input_6_external_connection_export => CONNECTED_TO_camera_input_6_external_connection_export, -- camera_input_6_external_connection.export
			camera_input_7_external_connection_export => CONNECTED_TO_camera_input_7_external_connection_export, -- camera_input_7_external_connection.export
			camera_input_8_external_connection_export => CONNECTED_TO_camera_input_8_external_connection_export, -- camera_input_8_external_connection.export
			camera_input_9_external_connection_export => CONNECTED_TO_camera_input_9_external_connection_export, -- camera_input_9_external_connection.export
			clk_clk                                   => CONNECTED_TO_clk_clk,                                   --                                clk.clk
			reset_reset_n                             => CONNECTED_TO_reset_reset_n                              --                              reset.reset_n
		);

