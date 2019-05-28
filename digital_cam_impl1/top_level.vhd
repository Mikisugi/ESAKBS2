library ieee;
use ieee.std_logic_1164.all;


entity digital_cam_impl1 is
  Port (
		clk_50 					: in  std_logic;
		btn_resend        	: in  std_logic;
		led_config_finished	: out std_logic;
	 
		btn_group_pixels		: in std_logic;

		vga_hsync	: out  std_logic;
		vga_vsync	: out  std_logic;
		vga_r			: out  std_logic_vector(7 downto 0);
		vga_g			: out  std_logic_vector(7 downto 0);
		vga_b			: out  std_logic_vector(7 downto 0);
		vga_blank_N	: out  std_logic;
		vga_sync_N	: out  std_logic;
		vga_CLK		: out  std_logic;

		ov7670_pclk  : in  std_logic;
		ov7670_xclk  : out std_logic;
		ov7670_vsync : in  std_logic;
		ov7670_href  : in  std_logic;
		ov7670_data  : in  std_logic_vector(7 downto 0);
		ov7670_sioc  : out std_logic;
		ov7670_siod  : inout std_logic;
		ov7670_pwdn  : out std_logic;
		ov7670_reset : out std_logic;
	 
		HEX1 : out  std_logic_vector(6 downto 0);
		HEX2 : out  std_logic_vector(6 downto 0);
		HEX3 : out  std_logic_vector(6 downto 0);
		HEX4 : out  std_logic_vector(6 downto 0);
		HEX5 : out  std_logic_vector(6 downto 0);
		HEX6 : out  std_logic_vector(6 downto 0);
	 
		led16 : out std_logic;
		led15 : out std_logic;
		led14 : out std_logic;
		
		Switch : in std_logic_vector(6 downto 0);
		ledsw	 : out std_logic_vector(2 downto 0);
		ledw : out std_logic
		
		-- word gebruikt door de C code:
		-- here we placed all the variables that will be used by the C code
		-- empty: 				001
		-- friendly stone:	010
		-- friendly king:	011
		-- enemy stone:		100
		-- enemy king:		101
--		vak1	: out std_logic_vector(2 downto 0);
--		vak2	: out std_logic_vector(2 downto 0);
--		vak3	: out std_logic_vector(2 downto 0);
--		vak4	: out std_logic_vector(2 downto 0);
--		vak5	: out std_logic_vector(2 downto 0);
--		vak6	: out std_logic_vector(2 downto 0);
--		vak7	: out std_logic_vector(2 downto 0);
--		vak8	: out std_logic_vector(2 downto 0);
--		vak9	: out std_logic_vector(2 downto 0);
--		vak10 : out std_logic_vector(2 downto 0);
--		vak11 : out std_logic_vector(2 downto 0);
--		vak12 : out std_logic_vector(2 downto 0);
--		vak13 : out std_logic_vector(2 downto 0);
--		vak14 : out std_logic_vector(2 downto 0);
--		vak15 : out std_logic_vector(2 downto 0);
--		vak16 : out std_logic_vector(2 downto 0);
--		vak17 : out std_logic_vector(2 downto 0);
--		vak18 : out std_logic_vector(2 downto 0);
--		vak19 : out std_logic_vector(2 downto 0);
--		vak20 : out std_logic_vector(2 downto 0);
--		vak21 : out std_logic_vector(2 downto 0);
--		vak22 : out std_logic_vector(2 downto 0);
--		vak23 : out std_logic_vector(2 downto 0);
--		vak24 : out std_logic_vector(2 downto 0);
--		vak25 : out std_logic_vector(2 downto 0);
--		vak26 : out std_logic_vector(2 downto 0);
--		vak27 : out std_logic_vector(2 downto 0);
--		vak28 : out std_logic_vector(2 downto 0);
--		vak29 : out std_logic_vector(2 downto 0);
--		vak30 : out std_logic_vector(2 downto 0);
--		vak31 : out std_logic_vector(2 downto 0);
--		vak32 : out std_logic_vector(2 downto 0);
--		vak33 : out std_logic_vector(2 downto 0);
--		vak34 : out std_logic_vector(2 downto 0);
--		vak35 : out std_logic_vector(2 downto 0);
--		vak36 : out std_logic_vector(2 downto 0);
--		vak37 : out std_logic_vector(2 downto 0);
--		vak38 : out std_logic_vector(2 downto 0);
--		vak39 : out std_logic_vector(2 downto 0);
--		vak40 : out std_logic_vector(2 downto 0);
--		vak41 : out std_logic_vector(2 downto 0);
--		vak42 : out std_logic_vector(2 downto 0);
--		vak43 : out std_logic_vector(2 downto 0);
--		vak44 : out std_logic_vector(2 downto 0);
--		vak45 : out std_logic_vector(2 downto 0);
--		vak46 : out std_logic_vector(2 downto 0);
--		vak47 : out std_logic_vector(2 downto 0);
--		vak48 : out std_logic_vector(2 downto 0);
--		vak49 : out std_logic_vector(2 downto 0);
--		vak50 : out std_logic_vector(2 downto 0)
	);
end digital_cam_impl1;

architecture my_structural of digital_cam_impl1 is
	component VGA
	port(
		CLK25			: in std_logic;    
		Hsync			: out std_logic;
		Vsync			: out std_logic;
		Nblank		: out std_logic;      
		clkout		: out std_logic;
		activeArea	: out std_logic;
		Nsync			: out std_logic
	);
	end component;

	component ov7670_controller
	port(
		clk					: in std_logic;
		resend				: in std_logic;    
		siod					: inout std_logic;      
		config_finished	: out std_logic;
		sioc					: out std_logic;
		reset					: out std_logic;
		pwdn					: out std_logic;
		xclk					: out std_logic
	);
	end component;

	component frame_buffer
	port(
		data			: in std_logic_vector(11 downto 0);
		rdaddress	: in std_logic_vector(16 downto 0);
		rdclock		: in std_logic;
		wraddress	: in std_logic_vector(16 downto 0);
		wrclock		: in std_logic;
		wren			: in std_logic;          
		q				: out std_logic_vector(11 downto 0)
	);
	end component;

	component ov7670_capture
	port(
		pclk	: in std_logic;
		vsync : in std_logic;
		href	: in std_logic;
		d		: in std_logic_vector(7 downto 0);          
		addr	: out std_logic_vector(16 downto 0);
		dout	: out std_logic_vector(11 downto 0);
		we		: out std_logic
	);
	end component;

	component RGB
	port(
		Din		: in std_logic_vector(11 downto 0);
		Nblank	: in std_logic;          
		R			: out std_logic_vector(7 downto 0);
		G			: out std_logic_vector(7 downto 0);
		B			: out std_logic_vector(7 downto 0)
	);
	end component;

	-- DE2-115 board has an Altera Cyclone V E, which has ALTPLL's'
	component my_altpll
	port (
		inclk0 : in std_logic := '0';
		c0     : out std_logic ;
		c1     : out std_logic 
	);
	end component;

	component Address_Generator
	port(
		CLK25		: in  std_logic;
		enable	: in  std_logic;       
		vsync		: in  std_logic;
		address	: out std_logic_vector(16 downto 0)
	);
	end component;
  
	component Colour_Recognition_register
	port(
		activated		: in std_logic;
		clk_i  			: in std_logic;
		dpixel 			: in std_logic_vector(11 downto 0);    
		address_second	: in std_logic_vector (16 downto 0);
		colour 			: out std_logic_vector(11 downto 0);
		pixel				: out std_logic_vector(11 downto 0);
		vak_1 			: out std_logic_vector(2 downto 0);
		vak_2 			: out std_logic_vector(2 downto 0);
		vak_3 			: out std_logic_vector(2 downto 0);
		vak_4 			: out std_logic_vector(2 downto 0);
		vak_5 			: out std_logic_vector(2 downto 0);
		vak_6 			: out std_logic_vector(2 downto 0);
		vak_7 			: out std_logic_vector(2 downto 0);
		vak_8 			: out std_logic_vector(2 downto 0);
		vak_9 			: out std_logic_vector(2 downto 0);
		vak_10 			: out std_logic_vector(2 downto 0);
		vak_11 			: out std_logic_vector(2 downto 0);
		vak_12 			: out std_logic_vector(2 downto 0);
		vak_13 			: out std_logic_vector(2 downto 0);
		vak_14 			: out std_logic_vector(2 downto 0);
		vak_15 			: out std_logic_vector(2 downto 0);
		vak_16 			: out std_logic_vector(2 downto 0);
		vak_17 			: out std_logic_vector(2 downto 0);
		vak_18 			: out std_logic_vector(2 downto 0);
		vak_19 			: out std_logic_vector(2 downto 0);
		vak_20 			: out std_logic_vector(2 downto 0);
		vak_21 			: out std_logic_vector(2 downto 0);
		vak_22 			: out std_logic_vector(2 downto 0);
		vak_23 			: out std_logic_vector(2 downto 0);
		vak_24 			: out std_logic_vector(2 downto 0);
		vak_25 			: out std_logic_vector(2 downto 0);
		vak_26 			: out std_logic_vector(2 downto 0);
		vak_27 			: out std_logic_vector(2 downto 0);
		vak_28 			: out std_logic_vector(2 downto 0);
		vak_29 			: out std_logic_vector(2 downto 0);
		vak_30 			: out std_logic_vector(2 downto 0);
		vak_31 			: out std_logic_vector(2 downto 0);
		vak_32 			: out std_logic_vector(2 downto 0);
		vak_33 			: out std_logic_vector(2 downto 0);
		vak_34 			: out std_logic_vector(2 downto 0);
		vak_35 			: out std_logic_vector(2 downto 0);
		vak_36 			: out std_logic_vector(2 downto 0);
		vak_37 			: out std_logic_vector(2 downto 0);
		vak_38 			: out std_logic_vector(2 downto 0);
		vak_39 			: out std_logic_vector(2 downto 0);
		vak_40 			: out std_logic_vector(2 downto 0);
		vak_41 			: out std_logic_vector(2 downto 0);
		vak_42 			: out std_logic_vector(2 downto 0);
		vak_43 			: out std_logic_vector(2 downto 0);
		vak_44 			: out std_logic_vector(2 downto 0);
		vak_45 			: out std_logic_vector(2 downto 0);
		vak_46 			: out std_logic_vector(2 downto 0);
		vak_47 			: out std_logic_vector(2 downto 0);
		vak_48 			: out std_logic_vector(2 downto 0);
		vak_49 			: out std_logic_vector(2 downto 0);
		vak_50 			: out std_logic_vector(2 downto 0);
		ledw : out std_logic
	);
	end component;
	
	component Switches
	port(
		--switches input
		switch	:	in std_logic_vector(6 downto 0);
		
		--data voor de ledjes
		data	: out std_logic_vector(2 downto 0);
		
		-- word gebruikt door de C code:
		-- here we placed all the variables that will be used by the C code
		-- empty: 				001
		-- friendly stone:	010
		-- friendly king:	011
		-- enemy stone:		100
		-- enemy king:		101
		vak1	: in std_logic_vector(2 downto 0);
		vak2	: in std_logic_vector(2 downto 0);
		vak3	: in std_logic_vector(2 downto 0);
		vak4	: in std_logic_vector(2 downto 0);
		vak5	: in std_logic_vector(2 downto 0);
		vak6	: in std_logic_vector(2 downto 0);
		vak7	: in std_logic_vector(2 downto 0);
		vak8	: in std_logic_vector(2 downto 0);
		vak9	: in std_logic_vector(2 downto 0);
		vak10 : in std_logic_vector(2 downto 0);
		vak11 : in std_logic_vector(2 downto 0);
		vak12 : in std_logic_vector(2 downto 0);
		vak13 : in std_logic_vector(2 downto 0);
		vak14 : in std_logic_vector(2 downto 0);
		vak15 : in std_logic_vector(2 downto 0);
		vak16 : in std_logic_vector(2 downto 0);
		vak17 : in std_logic_vector(2 downto 0);
		vak18 : in std_logic_vector(2 downto 0);
		vak19 : in std_logic_vector(2 downto 0);
		vak20 : in std_logic_vector(2 downto 0);
		vak21 : in std_logic_vector(2 downto 0);
		vak22 : in std_logic_vector(2 downto 0);
		vak23 : in std_logic_vector(2 downto 0);
		vak24 : in std_logic_vector(2 downto 0);
		vak25 : in std_logic_vector(2 downto 0);
		vak26 : in std_logic_vector(2 downto 0);
		vak27 : in std_logic_vector(2 downto 0);
		vak28 : in std_logic_vector(2 downto 0);
		vak29 : in std_logic_vector(2 downto 0);
		vak30 : in std_logic_vector(2 downto 0);
		vak31 : in std_logic_vector(2 downto 0);
		vak32 : in std_logic_vector(2 downto 0);
		vak33 : in std_logic_vector(2 downto 0);
		vak34 : in std_logic_vector(2 downto 0);
		vak35 : in std_logic_vector(2 downto 0);
		vak36 : in std_logic_vector(2 downto 0);
		vak37 : in std_logic_vector(2 downto 0);
		vak38 : in std_logic_vector(2 downto 0);
		vak39 : in std_logic_vector(2 downto 0);
		vak40 : in std_logic_vector(2 downto 0);
		vak41 : in std_logic_vector(2 downto 0);
		vak42 : in std_logic_vector(2 downto 0);
		vak43 : in std_logic_vector(2 downto 0);
		vak44 : in std_logic_vector(2 downto 0);
		vak45 : in std_logic_vector(2 downto 0);
		vak46 : in std_logic_vector(2 downto 0);
		vak47 : in std_logic_vector(2 downto 0);
		vak48 : in std_logic_vector(2 downto 0);
		vak49 : in std_logic_vector(2 downto 0);
		vak50 : in std_logic_vector(2 downto 0)
	);
	end component;
  
	component segment
	port(
		avg_colour	: in std_logic_vector(11 downto 0);
		hex1			: out std_logic_vector(6 downto 0);
		hex2			: out std_logic_vector(6 downto 0);
		hex3			: out std_logic_vector(6 downto 0);
		hex4			: out std_logic_vector(6 downto 0);
		hex5			: out std_logic_vector(6 downto 0);
		hex6			: out std_logic_vector(6 downto 0)
	);
	end component;

	signal clk_50_camera : std_logic;
	signal clk_25_vga    : std_logic;
	signal wren       	: std_logic;
	signal resend     	: std_logic;
	signal nBlank     	: std_logic;
	signal vSync      	: std_logic;

	signal wraddress  		: std_logic_vector(16 downto 0);
	signal wrdata     		: std_logic_vector(11 downto 0);   
	signal rdaddress  		: std_logic_vector(16 downto 0);
	signal rddata     		: std_logic_vector(11 downto 0);
	signal red,green,blue	: std_logic_vector(7 downto 0);
	signal activeArea			: std_logic;
  
--	type pixelArray is array (0 to 49) of std_logic_vector(11 downto 0);	-- (vaknummer)(kleur data)
--	signal pixel_main : pixelArray;
	
	-- gooit een pixel door naar de vga zodat er beeld op de monitor komt
	signal pixel : std_logic_vector(11 downto 0);
  
--	type colourArray is array (0 to 49) of std_logic_vector(11 downto 0);	-- (vaknummer)(kleur data)
--	signal colour_main : colourArray;
	
	-- gooit colour naar de 7-segment zodat we weten wat de gemiddelde kleur is
	signal colour : std_logic_vector(11 downto 0);

	-- 1: kleurherkenning wordt uitgevoerd op het beeld, 0: beeld gaat direct naar vga
	signal kleur_herkenning : std_logic := '0';
	
	-- handelt de status van de knop (KEY2)
	signal group_pixels	: std_logic := '0';
	
	-- voor het testen of de goede waardes worden opgeslagen voor de C code
	signal vak01 : std_logic_vector(2 downto 0);
	signal vak02 : std_logic_vector(2 downto 0);
	signal vak03 : std_logic_vector(2 downto 0);
	signal vak04 : std_logic_vector(2 downto 0);
	signal vak05 : std_logic_vector(2 downto 0);
	signal vak06 : std_logic_vector(2 downto 0);
	signal vak07 : std_logic_vector(2 downto 0);
	signal vak08 : std_logic_vector(2 downto 0);
	signal vak09 : std_logic_vector(2 downto 0);
	signal vak010 : std_logic_vector(2 downto 0);
	signal vak011 : std_logic_vector(2 downto 0);
	signal vak012 : std_logic_vector(2 downto 0);
	signal vak013 : std_logic_vector(2 downto 0);
	signal vak014 : std_logic_vector(2 downto 0);
	signal vak015 : std_logic_vector(2 downto 0);
	signal vak016 : std_logic_vector(2 downto 0);
	signal vak017 : std_logic_vector(2 downto 0);
	signal vak018 : std_logic_vector(2 downto 0);
	signal vak019 : std_logic_vector(2 downto 0);
	signal vak020 : std_logic_vector(2 downto 0);
	signal vak021 : std_logic_vector(2 downto 0);
	signal vak022 : std_logic_vector(2 downto 0);
	signal vak023 : std_logic_vector(2 downto 0);
	signal vak024 : std_logic_vector(2 downto 0);
	signal vak025 : std_logic_vector(2 downto 0);
	signal vak026 : std_logic_vector(2 downto 0);
	signal vak027 : std_logic_vector(2 downto 0);
	signal vak028 : std_logic_vector(2 downto 0);
	signal vak029 : std_logic_vector(2 downto 0);
	signal vak030 : std_logic_vector(2 downto 0);
	signal vak031 : std_logic_vector(2 downto 0);
	signal vak032 : std_logic_vector(2 downto 0);
	signal vak033 : std_logic_vector(2 downto 0);
	signal vak034 : std_logic_vector(2 downto 0);
	signal vak035 : std_logic_vector(2 downto 0);
	signal vak036 : std_logic_vector(2 downto 0);
	signal vak037 : std_logic_vector(2 downto 0);
	signal vak038 : std_logic_vector(2 downto 0);
	signal vak039 : std_logic_vector(2 downto 0);
	signal vak040 : std_logic_vector(2 downto 0);
	signal vak041 : std_logic_vector(2 downto 0);
	signal vak042 : std_logic_vector(2 downto 0);
	signal vak043 : std_logic_vector(2 downto 0);
	signal vak044 : std_logic_vector(2 downto 0);
	signal vak045 : std_logic_vector(2 downto 0);
	signal vak046 : std_logic_vector(2 downto 0);
	signal vak047 : std_logic_vector(2 downto 0);
	signal vak048 : std_logic_vector(2 downto 0);
	signal vak049 : std_logic_vector(2 downto 0);
	signal vak050 : std_logic_vector(2 downto 0);

begin
	-- splitst vak01 voor testen
	led16 <= vak01(2);
	led15 <= vak01(1);
	led14 <= vak01(0);
--	vak1 <= vak01;
--	vak2 <= vak02;
--	vak3 <= vak03;
--	vak4 <= vak04;
--	vak5 <= vak05;
--	vak6 <= vak06;
--	vak7 <= vak07;
--	vak8 <= vak08;
--	vak9 <= vak09;
--	vak10 <= vak010;
--	vak11 <= vak011;
--	vak12 <= vak012;
--	vak13 <= vak013;
--	vak14 <= vak014;
--	vak15 <= vak015;
--	vak16 <= vak016;
--	vak17 <= vak017;
--	vak18 <= vak018;
--	vak19 <= vak019;
--	vak20 <= vak020;
--	vak21 <= vak021;
--	vak22 <= vak022;
--	vak23 <= vak023;
--	vak24 <= vak024;
--	vak25 <= vak025;
--	vak26 <= vak026;
--	vak27 <= vak027;
--	vak28 <= vak028;
--	vak29 <= vak029;
--	vak30 <= vak030;
--	vak31 <= vak031;
--	vak32 <= vak032;
--	vak33 <= vak033;
--	vak34 <= vak034;
--	vak35 <= vak035;
--	vak36 <= vak036;
--	vak37 <= vak037;
--	vak38 <= vak038;
--	vak39 <= vak039;
--	vak40 <= vak040;
--	vak41 <= vak041;
--	vak42 <= vak042;
--	vak43 <= vak043;
--	vak44 <= vak044;
--	vak45 <= vak045;
--	vak46 <= vak046;
--	vak47 <= vak047;
--	vak48 <= vak048;
--	vak49 <= vak049;
--	vak50 <= vak050;

	-- de kleur lijnen worden hier aan de vga poort gekoppeld
	vga_r <= red(7 downto 0);
	vga_g <= green(7 downto 0);
	vga_b <= blue(7 downto 0);
   
	--hier worden de klokken gegenereerd
	Inst_vga_pll: my_altpll port map(
		inclk0 => clk_50,
		c0 => clk_50_camera,
		c1 => clk_25_vga
	);    
    
    
	-- zet de knoppen om, omdat een 1 is op de de2-115 niet ingedrukt en een 0 is wel ingedrukt
	resend <= not btn_resend;
	group_pixels <= not btn_group_pixels;
	
	
	vga_vsync <= vsync;
	vga_blank_N <= nBlank;
  
	process (clk_50)
	begin
		if rising_edge (clk_50) then
			if (group_pixels = '1') then
			kleur_herkenning <= '1';
			else
			kleur_herkenning <= '0';
			end if;
		end if;
	end process;
  
	Inst_VGA: VGA port map(
		CLK25      => clk_25_vga,
		clkout     => vga_CLK,
		Hsync      => vga_hsync,
		Vsync      => vsync,
		Nblank     => nBlank,
		Nsync      => vga_sync_N,
		activeArea => activeArea
	);

	Inst_ov7670_controller: ov7670_controller port map(
		clk             => clk_50_camera,
		resend          => resend,
		config_finished => led_config_finished,
		sioc            => ov7670_sioc,
		siod            => ov7670_siod,
		reset           => ov7670_reset,
		pwdn            => ov7670_pwdn,
		xclk            => ov7670_xclk
	);
   
	Inst_ov7670_capture: ov7670_capture port map(
		pclk  => ov7670_pclk,
		vsync => ov7670_vsync,
		href  => ov7670_href,
		d     => ov7670_data,
		addr  => wraddress,
		dout  => wrdata,
		we    => wren
	);

	Inst_frame_buffer: frame_buffer port map(
		rdaddress => rdaddress,
		rdclock   => clk_25_vga,
		q         => rddata, 
		wrclock   => ov7670_pclk,
		wraddress => wraddress(16 downto 0),
		data      => wrdata,
		wren      => wren
	);
  
	Inst_RGB: RGB port map(
		Din => pixel,
		Nblank => activeArea,
		R => red,
		G => green,
		B => blue
	);

	Inst_Address_Generator: Address_Generator port map(
		CLK25 => clk_25_vga,
		enable => activeArea,
		vsync => vsync,
		address => rdaddress
	);
	
	-- hier begint de kleur herkenning
	-- de reeks vak1, vak2, ... word op deze manier opgeslagen omdat dat gebruikt wordt door de C code
	Inst_Colour_Recognition_register: Colour_Recognition_register port map (
		activated => kleur_herkenning,
		clk_i => clk_50,
		dpixel => rddata,
		address_second => rdaddress,
		colour => colour,
		pixel => pixel,
		ledw => ledw,

		vak_1 => vak01, -- moet eigenlijk vak1 zijn, maar voor testing is hij hier 01
		vak_2 => vak02,
		vak_3 => vak03,
		vak_4 => vak04,
		vak_5 => vak05,
		vak_6 => vak06,
		vak_7 => vak07,
		vak_8 => vak08,
		vak_9 => vak09,
		vak_10 => vak010,
		vak_11 => vak011,
		vak_12 => vak012,
		vak_13 => vak013,
		vak_14 => vak014,
		vak_15 => vak015,
		vak_16 => vak016,
		vak_17 => vak017,
		vak_18 => vak018,
		vak_19 => vak019,
		vak_20 => vak020,
		vak_21 => vak021,
		vak_22 => vak022,
		vak_23 => vak023,
		vak_24 => vak024,
		vak_25 => vak025,
		vak_26 => vak026,
		vak_27 => vak027,
		vak_28 => vak028,
		vak_29 => vak029,
		vak_30 => vak030,
		vak_31 => vak031,
		vak_32 => vak032,
		vak_33 => vak033,
		vak_34 => vak034,
		vak_35 => vak035,
		vak_36 => vak036,
		vak_37 => vak037,
		vak_38 => vak038,
		vak_39 => vak039,
		vak_40 => vak040,
		vak_41 => vak041,
		vak_42 => vak042,
		vak_43 => vak043,
		vak_44 => vak044,
		vak_45 => vak045,
		vak_46 => vak046,
		vak_47 => vak047,
		vak_48 => vak048,
		vak_49 => vak049,
		vak_50 => vak050
	);
	
	Inst_Switches: Switches port map (
		switch => Switch,
		data => ledsw,
		vak1 => vak01,
		vak2 => vak02,
		vak3 => vak03,
		vak4 => vak04,
		vak5 => vak05,
		vak6 => vak06,
		vak7 => vak07,
		vak8 => vak08,
		vak9 => vak09,
		vak10 => vak010,
		vak11 => vak011,
		vak12 => vak012,
		vak13 => vak013,
		vak14 => vak014,
		vak15 => vak015,
		vak16 => vak016,
		vak17 => vak017,
		vak18 => vak018,
		vak19 => vak019,
		vak20 => vak020,
		vak21 => vak021,
		vak22 => vak022,
		vak23 => vak023,
		vak24 => vak024,
		vak25 => vak025,
		vak26 => vak026,
		vak27 => vak027,
		vak28 => vak028,
		vak29 => vak029,
		vak30 => vak030,
		vak31 => vak031,
		vak32 => vak032,
		vak33 => vak033,
		vak34 => vak034,
		vak35 => vak035,
		vak36 => vak036,
		vak37 => vak037,
		vak38 => vak038,
		vak39 => vak039,
		vak40 => vak040,
		vak41 => vak041,
		vak42 => vak042,
		vak43 => vak043,
		vak44 => vak044,
		vak45 => vak045,
		vak46 => vak046,
		vak47 => vak047,
		vak48 => vak048,
		vak49 => vak049,
		vak50 => vak050
	);
  
	-- dit blokje is voor het testen, de gemiddelde kleur word weergegeven op de hex poorten
	Inst_segment: segment port map (
		avg_colour => colour,
		hex1 => HEX1,
		hex2 => HEX2,
		hex3 => HEX3,
		hex4 => HEX4,
		hex5 => HEX5,
		hex6 => HEX6
	);
  
end my_structural;
