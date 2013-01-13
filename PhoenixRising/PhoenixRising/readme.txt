#########	###    ###	   ####		##########	###    ###	##########	###    ###	
####  ####	###    ###	 ########	##########	####   ###	##########	####  ####	
####   ###	###    ###	###    ###	######		###### ###	    ##		 ########	
####  ####	##########	###    ###	######		##########	    ##		   ####		
########	##########	###    ###	###			### ######	    ##		 ########	
####		###    ###	 ########	##########	###   ####	##########	####  ####	
####		###    ###	   ####		##########	###    ###	##########	###    ###	

     #########	##########	   ####		##########	###    ###	   ####	
     ####  ####	##########	 ########	##########	####   ###	 ######## 
     ####   ###	    ##    	###       	    ##		###### ###	###
     ####  ####	    ##   	 ########	    ##		##########	###	 #####
     ########	    ##   	       ###	    ##		### ######	###    ###
     #### ####	##########	 ########	##########	###   ####	 ########
     ####  ####	##########	   ####		##########	###    ###	   ####
																	
**** CONTROLS ****

GAMEPLAY:
up		-	moves player ship up
down	-	moves player ship down
left	-	moves player ship left
right	-	moves player ship right
space	-	makes player ship shoot a bullet
escape	-	pauses the game

MENU:
up		-	moves option selector up
down	-	moves option selector down
space	-	selects option
escape	-	selects first option or last option on the menu


**** FEATURES ****

* custom level data
* 4 paths for enemies
* advanced player movement
* enemy health
* enemy shooting
* menu system (menu implementations needed)

operational level files:
-level1.dat
-level2.dat
-level3.dat

level data file commands:
  req'd:          command:			   parameters:									description:
----------      ------------ 	     ---------------						      ----------------
   YES			  player_sprite			[filename]									sets the player ship sprite to the file indicated with filename
   YES			  enemy_sprite			[filename]									sets the enemy ship sprite to the file indicated with filename
   YES			  background_sprite		[filename]									sets the background image to the file indicated with filename
   YES			  enemy_bullet_sprite	[filename]									sets the enemy bullet sprite to the file indicated with filename
   YES			  player_bullet_sprite	[filename]									sets the player bullet sprite to the file indicated with filename
   YES			  player				[x] [y]										sets where the player begins the level at on screen (x, y)
   NO			  enemy					[type] [x] [y] [w] [h] [speed] [hp]			creates a new enemy at X, Y, W, H with speed (.1 - 2) and health (hp)