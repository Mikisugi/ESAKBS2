-- cristinel ababei; Jan.29.2015; CopyLeft (CL);
-- code name: "digital cam implementation #1";
-- project done using Quartus II 13.1 and tested on DE2-115;
--
-- this design basically connects a CMOS camera (OV7670 module) to
-- DE2-115 board; video frames are picked up from camera, buffered
-- on the FPGA (using embedded RAM), and displayed on the VGA monitor,
-- which is also connected to the board; clock signals generated
-- inside FPGA using ALTPLL's that take as input the board's 50MHz signal
-- from on-board oscillator; 
--
-- this whole project is an adaptation of Mike Field's original implementation 
-- that can be found here:
-- http://hamsterworks.co.nz/mediawiki/index.php/OV7670_camera

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity digital_cam_impl1 is
  Port ( clk_50 : in  STD_LOGIC;
    btn_resend          : in  STD_LOGIC;
    led_config_finished : out STD_LOGIC;
	 
	 btn_group_pixels		: in std_logic;
	 led_group_pixels		: out std_logic;

    vga_hsync : out  STD_LOGIC;
    vga_vsync : out  STD_LOGIC;
    vga_r     : out  STD_LOGIC_vector(7 downto 0);
    vga_g     : out  STD_LOGIC_vector(7 downto 0);
    vga_b     : out  STD_LOGIC_vector(7 downto 0);
    vga_blank_N : out  STD_LOGIC;
    vga_sync_N  : out  STD_LOGIC;
    vga_CLK     : out  STD_LOGIC;

    ov7670_pclk  : in  STD_LOGIC;
    ov7670_xclk  : out STD_LOGIC;
    ov7670_vsync : in  STD_LOGIC;
    ov7670_href  : in  STD_LOGIC;
    ov7670_data  : in  STD_LOGIC_vector(7 downto 0);
    ov7670_sioc  : out STD_LOGIC;
    ov7670_siod  : inout STD_LOGIC;
    ov7670_pwdn  : out STD_LOGIC;
    ov7670_reset : out STD_LOGIC;
	 
    HEX1 : out  std_logic_vector(6 downto 0);
    HEX2 : out  std_logic_vector(6 downto 0);
    HEX3 : out  std_logic_vector(6 downto 0);
    HEX4 : out  std_logic_vector(6 downto 0);
    HEX5 : out  std_logic_vector(6 downto 0);
    HEX6 : out  std_logic_vector(6 downto 0);
	 
	 ledR : out std_logic;
	 
	 led16 : out std_logic;
	 led15 : out std_logic;
	 led14 : out std_logic;
	 
	 --SDRAM
	 DRAM_ADDR                           : out       std_logic_vector(12 downto 0);  
    DRAM_BA                             : out       std_logic_vector(1 downto 0);
    DRAM_CAS_N                          : out       std_logic;
    DRAM_CKE                                : out       std_logic;
    DRAM_CS_N                           : out       std_logic;
    DRAM_DQ                             : inout std_logic_vector(31 downto 0);
    DRAM_DQM                                : out       std_logic_vector(3 downto 0);
    DRAM_RAS_N                          : out       std_logic;
    DRAM_WE_N                           : out       std_logic;
    DRAM_CLK                                : out       std_logic;
       
    -- SRAM
    SRAM_DQ                             : inout     std_logic_vector(15 downto 0);
    SRAM_ADDR                           : out       std_logic_vector(19 downto 0);
    SRAM_LB_N                           : out       std_logic;
    SRAM_UB_N                           : out       std_logic;
    SRAM_CE_N                           : out       std_logic;
    SRAM_OE_N                           : out       std_logic;
    SRAM_WE_N                           : out       std_logic;
       
    -- FLASH
    FL_ADDR                             : out       std_logic_vector(22 downto 0);
    FL_CE_N                             : out       std_logic;
    FL_OE_N                             : out       std_logic;
    FL_WE_N                             : out       std_logic;
    FL_RESET_N                          : out       std_logic;
    FL_DQ                                   : inout std_logic_vector(7 downto 0)
	 
	 -- here we placed all the variables that will be used by the C code
	 -- empty: 				001
	 -- friendly stone:	010
	 -- friendly king:	011
	 -- enemy stone:		100
	 -- enemy king:		101

  );
end digital_cam_impl1;


architecture my_structural of digital_cam_impl1 is


  COMPONENT VGA
  PORT(
    CLK25 : IN std_logic;    
    Hsync : OUT std_logic;
    Vsync : OUT std_logic;
    Nblank : OUT std_logic;      
    clkout : OUT std_logic;
    activeArea : OUT std_logic;
    Nsync : OUT std_logic
    );
  END COMPONENT;

  COMPONENT ov7670_controller
  PORT(
    clk : IN std_logic;
    resend : IN std_logic;    
    siod : INOUT std_logic;      
    config_finished : OUT std_logic;
    sioc : OUT std_logic;
    reset : OUT std_logic;
    pwdn : OUT std_logic;
    xclk : OUT std_logic
    );
  END COMPONENT;

  COMPONENT frame_buffer
  PORT(
    data : IN std_logic_vector(11 downto 0);
    rdaddress : IN std_logic_vector(16 downto 0);
    rdclock : IN std_logic;
    wraddress : IN std_logic_vector(16 downto 0);
    wrclock : IN std_logic;
    wren : IN std_logic;          
    q : OUT std_logic_vector(11 downto 0)
    );
  END COMPONENT;

  COMPONENT ov7670_capture
  PORT(
    pclk : IN std_logic;
    vsync : IN std_logic;
    href : IN std_logic;
    d : IN std_logic_vector(7 downto 0);          
    addr : OUT std_logic_vector(16 downto 0);
    dout : OUT std_logic_vector(11 downto 0);
    we : OUT std_logic
    );
  END COMPONENT;

  COMPONENT RGB
  PORT(
    Din : IN std_logic_vector(11 downto 0);
    Nblank : IN std_logic;          
    R : OUT std_logic_vector(7 downto 0);
    G : OUT std_logic_vector(7 downto 0);
    B : OUT std_logic_vector(7 downto 0)
    );
  END COMPONENT;

  -- DE2-115 board has an Altera Cyclone V E, which has ALTPLL's'
  COMPONENT my_altpll
  PORT (
    inclk0 : IN STD_LOGIC := '0';
    c0     : OUT STD_LOGIC ;
    c1     : OUT STD_LOGIC 
    );
  END COMPONENT;

  COMPONENT Address_Generator
  PORT(
    CLK25       : IN  std_logic;
    enable      : IN  std_logic;       
    vsync       : in  STD_LOGIC;
    address     : OUT std_logic_vector(16 downto 0)
    );
  END COMPONENT;
  
  component Colour_Recognition_register
  port(
	 activated	: in std_logic;
	 clk_i  		: in std_logic;
    dpixel 		: in std_logic_vector(11 downto 0);    
    address_second		: in std_logic_vector (16 downto 0);
    colour 		: out std_logic_vector(11 downto 0);
	 pixel		: out std_logic_vector(11 downto 0);
--	 led			: out std_logic
	 vak_1 		: out std_logic_vector(2 downto 0);
	 vak_2 		: out std_logic_vector(2 downto 0);
	 vak_3 		: out std_logic_vector(2 downto 0);
	 vak_4 		: out std_logic_vector(2 downto 0);
	 vak_5 		: out std_logic_vector(2 downto 0);
	 vak_6 		: out std_logic_vector(2 downto 0);
	 vak_7 		: out std_logic_vector(2 downto 0);
	 vak_8 		: out std_logic_vector(2 downto 0);
	 vak_9 		: out std_logic_vector(2 downto 0);
	 vak_10 		: out std_logic_vector(2 downto 0);
	 vak_11 		: out std_logic_vector(2 downto 0);
	 vak_12 		: out std_logic_vector(2 downto 0);
	 vak_13 		: out std_logic_vector(2 downto 0);
	 vak_14 		: out std_logic_vector(2 downto 0);
	 vak_15 		: out std_logic_vector(2 downto 0);
	 vak_16 		: out std_logic_vector(2 downto 0);
	 vak_17 		: out std_logic_vector(2 downto 0);
	 vak_18 		: out std_logic_vector(2 downto 0);
	 vak_19 		: out std_logic_vector(2 downto 0);
	 vak_20 		: out std_logic_vector(2 downto 0);
	 vak_21 		: out std_logic_vector(2 downto 0);
	 vak_22 		: out std_logic_vector(2 downto 0);
	 vak_23 		: out std_logic_vector(2 downto 0);
	 vak_24 		: out std_logic_vector(2 downto 0);
	 vak_25 		: out std_logic_vector(2 downto 0);
	 vak_26 		: out std_logic_vector(2 downto 0);
	 vak_27 		: out std_logic_vector(2 downto 0);
	 vak_28 		: out std_logic_vector(2 downto 0);
	 vak_29 		: out std_logic_vector(2 downto 0);
	 vak_30 		: out std_logic_vector(2 downto 0);
	 vak_31 		: out std_logic_vector(2 downto 0);
	 vak_32 		: out std_logic_vector(2 downto 0);
	 vak_33 		: out std_logic_vector(2 downto 0);
	 vak_34 		: out std_logic_vector(2 downto 0);
	 vak_35 		: out std_logic_vector(2 downto 0);
	 vak_36 		: out std_logic_vector(2 downto 0);
	 vak_37 		: out std_logic_vector(2 downto 0);
	 vak_38 		: out std_logic_vector(2 downto 0);
	 vak_39 		: out std_logic_vector(2 downto 0);
	 vak_40 		: out std_logic_vector(2 downto 0);
	 vak_41 		: out std_logic_vector(2 downto 0);
	 vak_42 		: out std_logic_vector(2 downto 0);
	 vak_43 		: out std_logic_vector(2 downto 0);
	 vak_44 		: out std_logic_vector(2 downto 0);
	 vak_45 		: out std_logic_vector(2 downto 0);
	 vak_46 		: out std_logic_vector(2 downto 0);
	 vak_47 		: out std_logic_vector(2 downto 0);
	 vak_48 		: out std_logic_vector(2 downto 0);
	 vak_49 		: out std_logic_vector(2 downto 0);
	 vak_50 		: out std_logic_vector(2 downto 0)
    );
  end component;
  
  component segment
  port(
    avg_colour : in std_logic_vector(11 downto 0);
    hex1 : out std_logic_vector(6 downto 0);
    hex2 : out std_logic_vector(6 downto 0);
    hex3 : out std_logic_vector(6 downto 0);
    hex4 : out std_logic_vector(6 downto 0);
    hex5 : out std_logic_vector(6 downto 0);
    hex6 : out std_logic_vector(6 downto 0)
    );
  end component;
  
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



  signal clk_50_camera : std_logic;
  signal clk_25_vga    : std_logic;
  signal wren       : std_logic;
  signal resend     : std_logic;
  signal nBlank     : std_logic;
  signal vSync      : std_logic;

  signal wraddress  : std_logic_vector(16 downto 0);
  signal wrdata     : std_logic_vector(11 downto 0);   
  signal rdaddress  : std_logic_vector(16 downto 0);
  signal rddata     : std_logic_vector(11 downto 0);
  signal red,green,blue : std_logic_vector(7 downto 0);
  signal activeArea : std_logic;
   
  signal pixel_addr_top : std_logic_vector(16 downto 0);
  
  signal once : std_logic := '0';
  
--  signal I : integer;
  
--  colour recognition. voor elk vakje word een blokje aangemaakt met de juiste kleur erin
  signal dpixel_main: std_logic_vector(11 downto 0);
  signal address_main : std_logic_vector (16 downto 0);
  
  type pixelArray is array (0 to 49) of std_logic_vector(11 downto 0);	-- (vaknummer)(kleur data)
  signal pixel_main : pixelArray;
  
  type colourArray is array (0 to 49) of std_logic_vector(11 downto 0);	-- (vaknummer)(kleur data)
  signal colour_main : colourArray;
  
  signal kleur_herkenning : std_logic := '0';
  
  signal group_pixels : std_logic := '0';
  signal btn_prev : std_logic := '0';
  
  signal vak01 : std_logic_vector(2 downto 0);
  
    signal vaka1 		 :std_logic_vector(2 downto 0);
	 signal vak2 		 :std_logic_vector(2 downto 0);
	 signal vak3 		 :std_logic_vector(2 downto 0);
	 signal vak4 		 :std_logic_vector(2 downto 0);
	 signal vak5 		 :std_logic_vector(2 downto 0);
	 signal vak6 		 :std_logic_vector(2 downto 0);
	 signal vak7 		 :std_logic_vector(2 downto 0);
	 signal vak8 		 :std_logic_vector(2 downto 0);
	 signal vak9 		 :std_logic_vector(2 downto 0);
	 signal vak10 		 :std_logic_vector(2 downto 0);
	 signal vak11 		 :std_logic_vector(2 downto 0);
	 signal vak12 		 :std_logic_vector(2 downto 0);
	 signal vak13 		 :std_logic_vector(2 downto 0);
	 signal vak14 		 :std_logic_vector(2 downto 0);
	 signal vak15 		 :std_logic_vector(2 downto 0);
	 signal vak16 		 :std_logic_vector(2 downto 0);
	 signal vak17 		 :std_logic_vector(2 downto 0);
	 signal vak18 		 :std_logic_vector(2 downto 0);
	 signal vak19 		 :std_logic_vector(2 downto 0);
	 signal vak20 		 :std_logic_vector(2 downto 0);
	 signal vak21 		 :std_logic_vector(2 downto 0);
	 signal vak22 		 :std_logic_vector(2 downto 0);
	 signal vak23 		 :std_logic_vector(2 downto 0);
	 signal vak24 		 :std_logic_vector(2 downto 0);
	 signal vak25 		 :std_logic_vector(2 downto 0);
	 signal vak26 		 :std_logic_vector(2 downto 0);
	 signal vak27 		 :std_logic_vector(2 downto 0);
	 signal vak28 		 :std_logic_vector(2 downto 0);
	 signal vak29 		 :std_logic_vector(2 downto 0);
	 signal vak30 		 :std_logic_vector(2 downto 0);
	 signal vak31 		 :std_logic_vector(2 downto 0);
	 signal vak32 		 :std_logic_vector(2 downto 0);
	 signal vak33 		 :std_logic_vector(2 downto 0);
	 signal vak34 		 :std_logic_vector(2 downto 0);
	 signal vak35 		 :std_logic_vector(2 downto 0);
	 signal vak36 		 :std_logic_vector(2 downto 0);
	 signal vak37 		 :std_logic_vector(2 downto 0);
	 signal vak38 		 :std_logic_vector(2 downto 0);
	 signal vak39 		 :std_logic_vector(2 downto 0);
	 signal vak40 		 :std_logic_vector(2 downto 0);
	 signal vak41 		 :std_logic_vector(2 downto 0);
	 signal vak42 		 :std_logic_vector(2 downto 0);
	 signal vak43 		 :std_logic_vector(2 downto 0);
	 signal vak44 		 :std_logic_vector(2 downto 0);
	 signal vak45 		 :std_logic_vector(2 downto 0);
	 signal vak46 		 :std_logic_vector(2 downto 0);
	 signal vak47 		 :std_logic_vector(2 downto 0);
	 signal vak48 	    :std_logic_vector(2 downto 0);
	 signal vak49 		 :std_logic_vector(2 downto 0);
	 signal vak50 		 :std_logic_vector(2 downto 0);


begin

  u0 : nios_system
        port map (
			system_pll_ref_clk_clk => clk_50,
         system_pll_ref_reset_reset => btn_resend ,
       
        -- SDRAM
        sdram_addr => DRAM_ADDR,
        sdram_ba => DRAM_BA,
        sdram_cas_n => DRAM_CAS_N,
        sdram_cke => DRAM_CKE,
        sdram_cs_n => DRAM_CS_N,
        sdram_dq => DRAM_DQ,
        sdram_dqm => DRAM_DQM,
        sdram_ras_n => DRAM_RAS_N,
        sdram_we_n => DRAM_WE_N,
        sdram_clk_clk => DRAM_CLK,
       
        -- SRAM 
        sram_DQ => SRAM_DQ,
        sram_ADDR => SRAM_ADDR,
        sram_LB_N => SRAM_LB_N,
        sram_UB_N => sram_UB_N,
        sram_CE_N => sram_CE_N,
        sram_OE_N => sram_OE_N,
        sram_WE_N => sram_WE_N,
       
        -- FLASH memory
        flash_ADDR => FL_ADDR,
        flash_CE_N => FL_CE_N,
        flash_OE_N => FL_OE_N,
        flash_WE_N => FL_WE_N,
        flash_RST_N => FL_RESET_N,
        flash_DQ => FL_DQ,
		  
		  cam_in_0_external_connection_export => vaka1 & vak2 & vak3 & vak4 & vak5, 
        cam_in_1_external_connection_export => vak6 & vak7 & vak8 & vak9 & vak10,
        cam_in_2_external_connection_export => vak11 & vak12 & vak13 & vak14 & vak15,
        cam_in_3_external_connection_export => vak16 & vak17 & vak18 & vak19 & vak20,
        cam_in_4_external_connection_export => vak21 & vak22 & vak23 & vak24 & vak25,
        cam_in_5_external_connection_export => vak26 & vak27 & vak28 & vak29 & vak30,
        cam_in_6_external_connection_export => vak31 & vak32 & vak33 & vak34 & vak35,
        cam_in_7_external_connection_export => vak36 & vak37 & vak38 & vak39 & vak40,
        cam_in_8_external_connection_export => vak41 & vak42 & vak43 & vak44 & vak45,
        cam_in_9_external_connection_export => vak46 & vak47 & vak48 & vak49 & vak50
		  

				); 


	led16 <= vak01(2);
	led15 <= vak01(1);
	led14 <= vak01(0);
	vaka1 <= vak01;

  vga_r <= red(7 downto 0);
  vga_g <= green(7 downto 0);
  vga_b <= blue(7 downto 0);
   

  Inst_vga_pll: my_altpll PORT MAP(
    inclk0 => clk_50,
    c0 => clk_50_camera,
    c1 => clk_25_vga
  );    
    
    
  -- take the inverted push button because KEY0 on DE2-115 board generates
  -- a signal 111000111; with 1 with not pressed and 0 when pressed/pushed;
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
  
  Inst_VGA: VGA PORT MAP(
    CLK25      => clk_25_vga,
    clkout     => vga_CLK,
    Hsync      => vga_hsync,
    Vsync      => vsync,
    Nblank     => nBlank,
    Nsync      => vga_sync_N,
    activeArea => activeArea
  );

  Inst_ov7670_controller: ov7670_controller PORT MAP(
    clk             => clk_50_camera,
    resend          => resend,
    config_finished => led_config_finished,
    sioc            => ov7670_sioc,
    siod            => ov7670_siod,
    reset           => ov7670_reset,
    pwdn            => ov7670_pwdn,
    xclk            => ov7670_xclk
  );
   
  Inst_ov7670_capture: ov7670_capture PORT MAP(
    pclk  => ov7670_pclk,
    vsync => ov7670_vsync,
    href  => ov7670_href,
    d     => ov7670_data,
    addr  => wraddress,
    dout  => wrdata,
    we    => wren
  );

  Inst_frame_buffer: frame_buffer PORT MAP(
    rdaddress => rdaddress,
    rdclock   => clk_25_vga,
    q         => rddata, 
    wrclock   => ov7670_pclk,
    wraddress => wraddress(16 downto 0),
    data      => wrdata,
    wren      => wren
  );
  
  Inst_RGB: RGB PORT MAP(
    Din => pixel_main(0),
    Nblank => activeArea,
    R => red,
    G => green,
    B => blue
  );

  Inst_Address_Generator: Address_Generator PORT MAP(
    CLK25 => clk_25_vga,
    enable => activeArea,
    vsync => vsync,
    address => rdaddress
  );
  
  Inst_Colour_Recognition_register: Colour_Recognition_register port map (
			activated => kleur_herkenning,
			clk_i => clk_50,
			dpixel => rddata,
			address_second => rdaddress,
			colour => colour_main(4),
			pixel => pixel_main(0),

			vak_1 => vak01,
			vak_2 => vak2,
			vak_3 => vak3,
			vak_4 => vak4,
			vak_5 => vak5,
			vak_6 => vak6,
			vak_7 => vak7,
			vak_8 => vak8,
			vak_9 => vak9,
			vak_10 => vak10,
			vak_11 => vak11,
			vak_12 => vak12,
			vak_13 => vak13,
			vak_14 => vak14,
			vak_15 => vak15,
			vak_16 => vak16,
			vak_17 => vak17,
			vak_18 => vak18,
			vak_19 => vak19,
			vak_20 => vak20,
			vak_21 => vak21,
			vak_22 => vak22,
			vak_23 => vak23,
			vak_24 => vak24,
			vak_25 => vak25,
			vak_26 => vak26,
			vak_27 => vak27,
			vak_28 => vak28,
			vak_29 => vak29,
			vak_30 => vak30,
			vak_31 => vak31,
			vak_32 => vak32,
			vak_33 => vak33,
			vak_34 => vak34,
			vak_35 => vak35,
			vak_36 => vak36,
			vak_37 => vak37,
			vak_38 => vak38,
			vak_39 => vak39,
			vak_40 => vak40,
			vak_41 => vak41,
			vak_42 => vak42,
			vak_43 => vak43,
			vak_44 => vak44,
			vak_45 => vak45,
			vak_46 => vak46,
			vak_47 => vak47,
			vak_48 => vak48,
			vak_49 => vak49,
			vak_50 => vak50
  );
  
  Inst_segment: segment port map (
		avg_colour => colour_main(4),
		hex1 => HEX1,
		hex2 => HEX2,
		hex3 => HEX3,
		hex4 => HEX4,
		hex5 => HEX5,
		hex6 => HEX6
  );
  
end my_structural;
