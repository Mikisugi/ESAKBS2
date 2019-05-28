library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;
--use ieee.numeric_std.all;


entity VGA is
	Port ( 
		CLK25 : in  std_logic;         -- Horloge d'entre de 25 MHz              
		clkout : out  std_logic;       -- Horloge de sortie vers le ADV7123 et l'ecran TFT
		Hsync,Vsync : out  std_logic;  -- les deux signaux de synchronisation pour l'ecran VGA
		Nblank : out  std_logic;       -- signal de commande du convertisseur N/A ADV7123
		activeArea : out  std_logic;
		Nsync : out  std_logic         -- signaux de synchronisation et commande de l'ecran TFT
	);        
end VGA;


architecture Behavioral of VGA is

	signal Hcnt:std_logic_vector(9 downto 0):="0000000000"; -- pour le comptage des colonnes
	signal Vcnt:std_logic_vector(9 downto 0):="1000001000"; -- pour le comptage des lignes
	signal video:std_logic;
	constant HM: integer :=799;  --la taille maximale considere 800 (horizontal)
	constant HD: integer :=640;  --la taille de l'ecran (horizontal)
	constant HF: integer :=16;   --front porch
	constant HB: integer :=48;   --back porch
	constant HR: integer :=96;   --sync time
	constant VM: integer :=524;  --la taille maximale considere 525 (vertical)  
	constant VD: integer :=480;  --la taille de l'ecran (vertical)
	constant VF: integer :=10;   --front porch
	constant VB: integer :=33;   --back porch
	constant VR: integer :=2;    --retrace
	
begin
-- initialisation d'un compteur de 0 a 799 (800 pixel par ligne):
-- a chaque front d'horloge en incremente le compteur de colonnes
-- c-a-d du 0 a 799.
	process(CLK25)
	begin
		if (CLK25'event and CLK25='1') then
			if (Hcnt = HM) then -- 799
				Hcnt <= "0000000000";
				if (Vcnt= VM) then -- 524
					Vcnt <= "0000000000";
					activeArea <= '1';
				else
					if vCnt < 240-1 then
						activeArea <= '1';
					end if;
					Vcnt <= Vcnt+1;
				end if;
			else      
				if hcnt = 320-1 then
					activeArea <= '0';
				end if;
				Hcnt <= Hcnt + 1;
			end if;
		end if;
	end process;
  
  
-- generation du signal de synchronisation horizontale Hsync:
	process(CLK25)
	begin
		if (CLK25'event and CLK25='1') then
			if (Hcnt >= (HD+HF) and Hcnt <= (HD+HF+HR-1)) then -- Hcnt >= 656 and Hcnt <= 751
				Hsync <= '0';
			else
				Hsync <= '1';
			end if;
		end if;
	end process;


-- generation du signal de synchronisation verticale Vsync:
	process(CLK25)
	begin
		if (CLK25'event and CLK25='1') then
			if (Vcnt >= (VD+VF) and Vcnt <= (VD+VF+VR-1)) then  ---Vcnt >= 490 and vcnt<= 491
				Vsync <= '0';
			else
				Vsync <= '1';
			end if;
		end if;
	end process;


-- Nblank et Nsync pour commander le covertisseur ADV7123:
	Nsync <= '1';
	video <= '1' when (Hcnt < HD) and (Vcnt < VD) else '0'; -- c'est pour utiliser la resolution complete 640 x 480
	Nblank <= video;
	clkout <= CLK25;
	
end Behavioral;
