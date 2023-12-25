#pragma once

	class Color
	{
	public:
		static inline glm::vec4 mult(const glm::vec4& c, float fac)
		{
			return glm::clamp(c * glm::vec4(fac, fac, fac, 1), 0.0f, 1.0f);
		}
		static inline glm::vec4 add(const glm::vec4& c, float fac)
		{
			return glm::clamp(c + glm::vec4(fac, fac, fac, 0), 0.0f, 1.0f);
		}



		static const glm::vec4 cloudyBlue;
		static const glm::vec4 darkPastelGreen;
		static const glm::vec4 dust;
		static const glm::vec4 electricLime;
		static const glm::vec4 freshGreen;
		static const glm::vec4 lightEggplant;
		static const glm::vec4 nastyGreen;
		static const glm::vec4 reallyLightBlue;
		static const glm::vec4 tea;
		static const glm::vec4 warmPurple;
		static const glm::vec4 yellowishTan;
		static const glm::vec4 cement;
		static const glm::vec4 darkGrassGreen;
		static const glm::vec4 dustyTeal;
		static const glm::vec4 greyTeal;
		static const glm::vec4 macaroniAndCheese;
		static const glm::vec4 pinkishTan;
		static const glm::vec4 spruce;
		static const glm::vec4 strongBlue;
		static const glm::vec4 toxicGreen;
		static const glm::vec4 windowsBlue;
		static const glm::vec4 blueBlue;
		static const glm::vec4 blueWithAHintOfPurple;
		static const glm::vec4 booger;
		static const glm::vec4 brightSeaGreen;
		static const glm::vec4 darkGreenBlue;
		static const glm::vec4 deepTurquoise;
		static const glm::vec4 greenTeal;
		static const glm::vec4 strongPink;
		static const glm::vec4 bland;
		static const glm::vec4 deepAqua;
		static const glm::vec4 lavenderPink;
		static const glm::vec4 lightMossGreen;
		static const glm::vec4 lightSeafoamGreen;
		static const glm::vec4 oliveYellow;
		static const glm::vec4 pigPink;
		static const glm::vec4 deepLilac;
		static const glm::vec4 desert;
		static const glm::vec4 dustyLavender;
		static const glm::vec4 purpleyGrey;
		static const glm::vec4 purply;
		static const glm::vec4 candyPink;
		static const glm::vec4 lightPastelGreen;
		static const glm::vec4 boringGreen;
		static const glm::vec4 kiwiGreen;
		static const glm::vec4 lightGreyGreen;
		static const glm::vec4 orangePink;
		static const glm::vec4 teaGreen;
		static const glm::vec4 veryLightBrown;
		static const glm::vec4 eggShell;
		static const glm::vec4 eggplantPurple;
		static const glm::vec4 powderPink;
		static const glm::vec4 reddishGrey;
		static const glm::vec4 babyShitBrown;
		static const glm::vec4 liliac;
		static const glm::vec4 stormyBlue;
		static const glm::vec4 uglyBrown;
		static const glm::vec4 custard;
		static const glm::vec4 darkishPink;
		static const glm::vec4 deepBrown;
		static const glm::vec4 greenishBeige;
		static const glm::vec4 manilla;
		static const glm::vec4 offBlue;
		static const glm::vec4 battleshipGrey;
		static const glm::vec4 brownyGreen;
		static const glm::vec4 bruise;
		static const glm::vec4 kelleyGreen;
		static const glm::vec4 sicklyYellow;
		static const glm::vec4 sunnyYellow;
		static const glm::vec4 azul;
		static const glm::vec4 darkGreen;
		static const glm::vec4 greenYellow;
		static const glm::vec4 lichen;
		static const glm::vec4 lightLightGreen;
		static const glm::vec4 paleGold;
		static const glm::vec4 sunYellow;
		static const glm::vec4 tanGreen;
		static const glm::vec4 burple;
		static const glm::vec4 butterscotch;
		static const glm::vec4 toupe;
		static const glm::vec4 darkCream;
		static const glm::vec4 indianRed;
		static const glm::vec4 lightLavendar;
		static const glm::vec4 poisonGreen;
		static const glm::vec4 babyPukeGreen;
		static const glm::vec4 brightYellowGreen;
		static const glm::vec4 charcoalGrey;
		static const glm::vec4 squash;
		static const glm::vec4 cinnamon;
		static const glm::vec4 lightPeaGreen;
		static const glm::vec4 radioactiveGreen;
		static const glm::vec4 rawSienna;
		static const glm::vec4 babyPurple;
		static const glm::vec4 cocoa;
		static const glm::vec4 lightRoyalBlue;
		static const glm::vec4 orangeish;
		static const glm::vec4 rustBrown;
		static const glm::vec4 sandBrown;
		static const glm::vec4 swamp;
		static const glm::vec4 tealishGreen;
		static const glm::vec4 burntSiena;
		static const glm::vec4 camo;
		static const glm::vec4 duskBlue;
		static const glm::vec4 fern;
		static const glm::vec4 oldRose;
		static const glm::vec4 paleLightGreen;
		static const glm::vec4 peachyPink;
		static const glm::vec4 rosyPink;
		static const glm::vec4 lightBluishGreen;
		static const glm::vec4 lightBrightGreen;
		static const glm::vec4 lightNeonGreen;
		static const glm::vec4 lightSeafoam;
		static const glm::vec4 tiffanyBlue;
		static const glm::vec4 washedOutGreen;
		static const glm::vec4 brownyOrange;
		static const glm::vec4 nIceBlue;
		static const glm::vec4 sapphire;
		static const glm::vec4 greyishTeal;
		static const glm::vec4 orangeyYellow;
		static const glm::vec4 parchment;
		static const glm::vec4 straw;
		static const glm::vec4 veryDarkBrown;
		static const glm::vec4 terracota;
		static const glm::vec4 uglyBlue;
		static const glm::vec4 clearBlue;
		static const glm::vec4 creme;
		static const glm::vec4 foamGreen;
		static const glm::vec4 greyGreen;
		static const glm::vec4 lightGold;
		static const glm::vec4 seafoamBlue;
		static const glm::vec4 topaz;
		static const glm::vec4 violetPink;
		static const glm::vec4 winterGreen;
		static const glm::vec4 yellowTan;
		static const glm::vec4 darkFuchsia;
		static const glm::vec4 indigoBlue;
		static const glm::vec4 lightYellowishGreen;
		static const glm::vec4 paleMagenta;
		static const glm::vec4 richPurple;
		static const glm::vec4 sunflowerYellow;
		static const glm::vec4 greenBlue;
		static const glm::vec4 leather;
		static const glm::vec4 racingGreen;
		static const glm::vec4 vividPurple;
		static const glm::vec4 darkRoyalBlue;
		static const glm::vec4 hazel;
		static const glm::vec4 mutedPink;
		static const glm::vec4 boogerGreen;
		static const glm::vec4 canary;
		static const glm::vec4 coolGrey;
		static const glm::vec4 darkTaupe;
		static const glm::vec4 darkishPurple;
		static const glm::vec4 trueGreen;
		static const glm::vec4 coralPink;
		static const glm::vec4 darkSage;
		static const glm::vec4 darkSlateBlue;
		static const glm::vec4 flatBlue;
		static const glm::vec4 mushroom;
		static const glm::vec4 richBlue;
		static const glm::vec4 dirtyPurple;
		static const glm::vec4 greenBlue_;
		static const glm::vec4 ickyGreen;
		static const glm::vec4 lightKhaki;
		static const glm::vec4 warmBlue;
		static const glm::vec4 darkHotPink;
		static const glm::vec4 deepSeaBlue;
		static const glm::vec4 carmine;
		static const glm::vec4 darkYellowGreen;
		static const glm::vec4 palePeach;
		static const glm::vec4 plumPurple;
		static const glm::vec4 goldenRod;
		static const glm::vec4 neonRed;
		static const glm::vec4 oldPink;
		static const glm::vec4 veryPaleBlue;
		static const glm::vec4 bloodOrange;
		static const glm::vec4 grapefruit;
		static const glm::vec4 sandYellow;
		static const glm::vec4 clayBrown;
		static const glm::vec4 darkBlueGrey;
		static const glm::vec4 flatGreen;
		static const glm::vec4 lightGreenBlue;
		static const glm::vec4 warmPink;
		static const glm::vec4 dodgerBlue;
		static const glm::vec4 grossGreen;
		static const glm::vec4 ice;
		static const glm::vec4 metallicBlue;
		static const glm::vec4 paleSalmon;
		static const glm::vec4 sapGreen;
		static const glm::vec4 algae;
		static const glm::vec4 blueyGrey;
		static const glm::vec4 greenyGrey;
		static const glm::vec4 highLighterGreen;
		static const glm::vec4 lightLightBlue;
		static const glm::vec4 lightMint;
		static const glm::vec4 rawUmber;
		static const glm::vec4 vividBlue;
		static const glm::vec4 deepLavender;
		static const glm::vec4 dullTeal;
		static const glm::vec4 lightGreenishBlue;
		static const glm::vec4 mudGreen;
		static const glm::vec4 pinky;
		static const glm::vec4 redWine;
		static const glm::vec4 shitGreen;
		static const glm::vec4 tanBrown;
		static const glm::vec4 darkBlue;
		static const glm::vec4 rosa;
		static const glm::vec4 lipstick;
		static const glm::vec4 paleMauve;
		static const glm::vec4 claret;
		static const glm::vec4 dandelion;
		static const glm::vec4 orangeRed;
		static const glm::vec4 poopGreen;
		static const glm::vec4 ruby;
		static const glm::vec4 dark;
		static const glm::vec4 greenishTurquoise;
		static const glm::vec4 pastelRed;
		static const glm::vec4 pissYellow;
		static const glm::vec4 brightCyan;
		static const glm::vec4 darkCoral;
		static const glm::vec4 algaeGreen;
		static const glm::vec4 darkishRed;
		static const glm::vec4 reddyBrown;
		static const glm::vec4 blushPink;
		static const glm::vec4 camouflageGreen;
		static const glm::vec4 lawnGreen;
		static const glm::vec4 putty;
		static const glm::vec4 vibrantBlue;
		static const glm::vec4 darkSand;
		static const glm::vec4 purpleBlue;
		static const glm::vec4 saffron;
		static const glm::vec4 twiLight;
		static const glm::vec4 warmBrown;
		static const glm::vec4 blueGrey;
		static const glm::vec4 bubbleGumPink;
		static const glm::vec4 duckEggBlue;
		static const glm::vec4 greenishCyan;
		static const glm::vec4 petrol;
		static const glm::vec4 royal;
		static const glm::vec4 butter;
		static const glm::vec4 dustyOrange;
		static const glm::vec4 offYellow;
		static const glm::vec4 paleOliveGreen;
		static const glm::vec4 orangish;
		static const glm::vec4 leaf;
		static const glm::vec4 lightBlueGrey;
		static const glm::vec4 driedBlood;
		static const glm::vec4 lightishPurple;
		static const glm::vec4 rustyRed;
		static const glm::vec4 lavenderBlue;
		static const glm::vec4 lightGrassGreen;
		static const glm::vec4 lightMintGreen;
		static const glm::vec4 sunflower;
		static const glm::vec4 velvet;
		static const glm::vec4 brickOrange;
		static const glm::vec4 lightishRed;
		static const glm::vec4 pureBlue;
		static const glm::vec4 twiLightBlue;
		static const glm::vec4 violetRed;
		static const glm::vec4 yellowyBrown;
		static const glm::vec4 carnation;
		static const glm::vec4 muddyYellow;
		static const glm::vec4 darkSeafoamGreen;
		static const glm::vec4 deepRose;
		static const glm::vec4 dustyRed;
		static const glm::vec4 greyBlue;
		static const glm::vec4 lemonLime;
		static const glm::vec4 purplePink;
		static const glm::vec4 brownYellow;
		static const glm::vec4 purpleBrown;
		static const glm::vec4 wisteria;
		static const glm::vec4 bananaYellow;
		static const glm::vec4 lipstickRed;
		static const glm::vec4 waterBlue;
		static const glm::vec4 brownGrey;
		static const glm::vec4 vibrantPurple;
		static const glm::vec4 babyGreen;
		static const glm::vec4 barfGreen;
		static const glm::vec4 eggshellBlue;
		static const glm::vec4 sandyYellow;
		static const glm::vec4 coolGreen;
		static const glm::vec4 pale;
		static const glm::vec4 blueGrey_;
		static const glm::vec4 hotMagenta;
		static const glm::vec4 greyBlue_;
		static const glm::vec4 purpley;
		static const glm::vec4 babyShitGreen;
		static const glm::vec4 brownishPink;
		static const glm::vec4 darkAquaMarine;
		static const glm::vec4 diarrhea;
		static const glm::vec4 lightMustard;
		static const glm::vec4 paleSkyBlue;
		static const glm::vec4 turtleGreen;
		static const glm::vec4 brightOlive;
		static const glm::vec4 darkGreyBlue;
		static const glm::vec4 greenyBrown;
		static const glm::vec4 lemonGreen;
		static const glm::vec4 lightPeriwinkle;
		static const glm::vec4 seaweedGreen;
		static const glm::vec4 sunshineYellow;
		static const glm::vec4 uglyPurple;
		static const glm::vec4 mediumPink;
		static const glm::vec4 pukeBrown;
		static const glm::vec4 veryLightPink;
		static const glm::vec4 viridian;
		static const glm::vec4 bile;
		static const glm::vec4 fadedYellow;
		static const glm::vec4 veryPaleGreen;
		static const glm::vec4 vibrantGreen;
		static const glm::vec4 brightLime;
		static const glm::vec4 sPearMint;
		static const glm::vec4 lightAquaMarine;
		static const glm::vec4 lightSage;
		static const glm::vec4 yellowGreen;
		static const glm::vec4 babyPoo;
		static const glm::vec4 darkSeafoam;
		static const glm::vec4 deepTeal;
		static const glm::vec4 heather;
		static const glm::vec4 rustOrange;
		static const glm::vec4 dirtyBlue;
		static const glm::vec4 fernGreen;
		static const glm::vec4 brightLilac;
		static const glm::vec4 weirdGreen;
		static const glm::vec4 peacockBlue;
		static const glm::vec4 avocadoGreen;
		static const glm::vec4 fadedOrange;
		static const glm::vec4 grapePurple;
		static const glm::vec4 hotGreen;
		static const glm::vec4 limeYellow;
		static const glm::vec4 mango;
		static const glm::vec4 shamrock;
		static const glm::vec4 bubblegum;
		static const glm::vec4 purplishBrown;
		static const glm::vec4 vomitYellow;
		static const glm::vec4 paleCyan;
		static const glm::vec4 keyLime;
		static const glm::vec4 tomatoRed;
		static const glm::vec4 lightGreen;
		static const glm::vec4 merlot;
		static const glm::vec4 nightBlue;
		static const glm::vec4 purpleishPink;
		static const glm::vec4 apple;
		static const glm::vec4 babyPoopGreen;
		static const glm::vec4 greenApple;
		static const glm::vec4 heliotrope;
		static const glm::vec4 yellowGreen_;
		static const glm::vec4 almostBlack;
		static const glm::vec4 coolBlue;
		static const glm::vec4 leafyGreen;
		static const glm::vec4 mustardBrown;
		static const glm::vec4 dusk;
		static const glm::vec4 dullBrown;
		static const glm::vec4 frogGreen;
		static const glm::vec4 vividGreen;
		static const glm::vec4 brightLightGreen;
		static const glm::vec4 fluroGreen;
		static const glm::vec4 kiwi;
		static const glm::vec4 seaweed;
		static const glm::vec4 navyGreen;
		static const glm::vec4 ultraMarineBlue;
		static const glm::vec4 iris;
		static const glm::vec4 pastelOrange;
		static const glm::vec4 yellowishOrange;
		static const glm::vec4 perrywinkle;
		static const glm::vec4 tealish;
		static const glm::vec4 darkPlum;
		static const glm::vec4 pear;
		static const glm::vec4 pinkishOrange;
		static const glm::vec4 midnightPurple;
		static const glm::vec4 lightUrple;
		static const glm::vec4 darkMint;
		static const glm::vec4 greenishTan;
		static const glm::vec4 lightBurgundy;
		static const glm::vec4 turquoiseBlue;
		static const glm::vec4 uglyPink;
		static const glm::vec4 sandy;
		static const glm::vec4 electricPink;
		static const glm::vec4 mutedPurple;
		static const glm::vec4 midGreen;
		static const glm::vec4 greyish;
		static const glm::vec4 neonYellow;
		static const glm::vec4 banana;
		static const glm::vec4 carnationPink;
		static const glm::vec4 tomato;
		static const glm::vec4 sea;
		static const glm::vec4 muddyBrown;
		static const glm::vec4 turquoiseGreen;
		static const glm::vec4 buff;
		static const glm::vec4 fawn;
		static const glm::vec4 mutedBlue;
		static const glm::vec4 paleRose;
		static const glm::vec4 darkMintGreen;
		static const glm::vec4 amethyst;
		static const glm::vec4 blueGreen;
		static const glm::vec4 chestnut;
		static const glm::vec4 sickGreen;
		static const glm::vec4 pea;
		static const glm::vec4 rustyOrange;
		static const glm::vec4 stone;
		static const glm::vec4 roseRed;
		static const glm::vec4 paleAqua;
		static const glm::vec4 deepOrange;
		static const glm::vec4 earth;
		static const glm::vec4 mossyGreen;
		static const glm::vec4 grassyGreen;
		static const glm::vec4 paleLimeGreen;
		static const glm::vec4 lightGreyBlue;
		static const glm::vec4 paleGrey;
		static const glm::vec4 asparagus;
		static const glm::vec4 blueBerry;
		static const glm::vec4 purpleRed;
		static const glm::vec4 paleLime;
		static const glm::vec4 greenishTeal;
		static const glm::vec4 caramel;
		static const glm::vec4 deepMagenta;
		static const glm::vec4 lightPeach;
		static const glm::vec4 milkChocolate;
		static const glm::vec4 ocher;
		static const glm::vec4 offGreen;
		static const glm::vec4 purplyPink;
		static const glm::vec4 lightBlue;
		static const glm::vec4 duSkyBlue;
		static const glm::vec4 golden;
		static const glm::vec4 lightBeige;
		static const glm::vec4 butterYellow;
		static const glm::vec4 duSkyPurple;
		static const glm::vec4 frenchBlue;
		static const glm::vec4 uglyYellow;
		static const glm::vec4 greenyYellow;
		static const glm::vec4 orangishRed;
		static const glm::vec4 shamrockGreen;
		static const glm::vec4 orangishBrown;
		static const glm::vec4 treeGreen;
		static const glm::vec4 deepViolet;
		static const glm::vec4 gunmetal;
		static const glm::vec4 bluePurple;
		static const glm::vec4 cherry;
		static const glm::vec4 sandyBrown;
		static const glm::vec4 warmGrey;
		static const glm::vec4 darkIndigo;
		static const glm::vec4 midnight;
		static const glm::vec4 blueyGreen;
		static const glm::vec4 greyPink;
		static const glm::vec4 softPurple;
		static const glm::vec4 blood;
		static const glm::vec4 brownRed;
		static const glm::vec4 mediumGrey;
		static const glm::vec4 berry;
		static const glm::vec4 poo;
		static const glm::vec4 purpleyPink;
		static const glm::vec4 lightSalmon;
		static const glm::vec4 snot;
		static const glm::vec4 easterPurple;
		static const glm::vec4 lightYellowGreen;
		static const glm::vec4 darkNavyBlue;
		static const glm::vec4 drab;
		static const glm::vec4 lightRose;
		static const glm::vec4 rouge;
		static const glm::vec4 purplishRed;
		static const glm::vec4 sLimeGreen;
		static const glm::vec4 babyPoop;
		static const glm::vec4 irishGreen;
		static const glm::vec4 pinkPurple;
		static const glm::vec4 darkNavy;
		static const glm::vec4 greenyBlue;
		static const glm::vec4 lightPlum;
		static const glm::vec4 pinkishGrey;
		static const glm::vec4 dirtyOrange;
		static const glm::vec4 rustRed;
		static const glm::vec4 paleLilac;
		static const glm::vec4 orangeyRed;
		static const glm::vec4 primaryBlue;
		static const glm::vec4 kermitGreen;
		static const glm::vec4 brownishPurple;
		static const glm::vec4 murkyGreen;
		static const glm::vec4 wheat;
		static const glm::vec4 veryDarkPurple;
		static const glm::vec4 bottleGreen;
		static const glm::vec4 waterMelon;
		static const glm::vec4 deepSkyBlue;
		static const glm::vec4 fireEngineRed;
		static const glm::vec4 yellowOchre;
		static const glm::vec4 pumpkinOrange;
		static const glm::vec4 paleOlive;
		static const glm::vec4 lightLilac;
		static const glm::vec4 lightishGreen;
		static const glm::vec4 carolinaBlue;
		static const glm::vec4 mulBerry;
		static const glm::vec4 shockingPink;
		static const glm::vec4 auburn;
		static const glm::vec4 brightLimeGreen;
		static const glm::vec4 celadon;
		static const glm::vec4 pinkishBrown;
		static const glm::vec4 pooBrown;
		static const glm::vec4 brightSkyBlue;
		static const glm::vec4 celery;
		static const glm::vec4 dirtBrown;
		static const glm::vec4 strawBerry;
		static const glm::vec4 darkLime;
		static const glm::vec4 copper;
		static const glm::vec4 mediumBrown;
		static const glm::vec4 mutedGreen;
		static const glm::vec4 robinsEgg;
		static const glm::vec4 brightAqua;
		static const glm::vec4 brightLavender;
		static const glm::vec4 ivory;
		static const glm::vec4 veryLightPurple;
		static const glm::vec4 lightNavy;
		static const glm::vec4 pinkRed;
		static const glm::vec4 oliveBrown;
		static const glm::vec4 poopBrown;
		static const glm::vec4 mustardGreen;
		static const glm::vec4 oceanGreen;
		static const glm::vec4 veryDarkBlue;
		static const glm::vec4 dustyGreen;
		static const glm::vec4 lightNavyBlue;
		static const glm::vec4 mintyGreen;
		static const glm::vec4 adobe;
		static const glm::vec4 barney;
		static const glm::vec4 jadeGreen;
		static const glm::vec4 brightLightBlue;
		static const glm::vec4 lightLime;
		static const glm::vec4 darkKhaki;
		static const glm::vec4 orangeYellow;
		static const glm::vec4 ocre;
		static const glm::vec4 maize;
		static const glm::vec4 fadedPink;
		static const glm::vec4 britishRacingGreen;
		static const glm::vec4 sandStone;
		static const glm::vec4 mudBrown;
		static const glm::vec4 lightSeaGreen;
		static const glm::vec4 robinEggBlue;
		static const glm::vec4 aquaMarine;
		static const glm::vec4 darkSeaGreen;
		static const glm::vec4 softPink;
		static const glm::vec4 orangeyBrown;
		static const glm::vec4 cherryRed;
		static const glm::vec4 burntYellow;
		static const glm::vec4 brownishGrey;
		static const glm::vec4 camel;
		static const glm::vec4 purplishGrey;
		static const glm::vec4 marine;
		static const glm::vec4 greyishPink;
		static const glm::vec4 paleTurquoise;
		static const glm::vec4 pastelYellow;
		static const glm::vec4 blueyPurple;
		static const glm::vec4 canaryYellow;
		static const glm::vec4 fadedRed;
		static const glm::vec4 sepia;
		static const glm::vec4 coffee;
		static const glm::vec4 brightMagenta;
		static const glm::vec4 mocha;
		static const glm::vec4 ecru;
		static const glm::vec4 purpleish;
		static const glm::vec4 cranBerry;
		static const glm::vec4 darkishGreen;
		static const glm::vec4 brownOrange;
		static const glm::vec4 duSkyRose;
		static const glm::vec4 melon;
		static const glm::vec4 sicklyGreen;
		static const glm::vec4 silver;
		static const glm::vec4 purplyBlue;
		static const glm::vec4 purpleishBlue;
		static const glm::vec4 hospitalGreen;
		static const glm::vec4 shitBrown;
		static const glm::vec4 midBlue;
		static const glm::vec4 amber;
		static const glm::vec4 easterGreen;
		static const glm::vec4 softBlue;
		static const glm::vec4 ceruleanBlue;
		static const glm::vec4 goldenBrown;
		static const glm::vec4 brightTurquoise;
		static const glm::vec4 redPink;
		static const glm::vec4 redPurple;
		static const glm::vec4 greyishBrown;
		static const glm::vec4 vermillion;
		static const glm::vec4 russet;
		static const glm::vec4 steelGrey;
		static const glm::vec4 lighterPurple;
		static const glm::vec4 brightViolet;
		static const glm::vec4 prussianBlue;
		static const glm::vec4 slateGreen;
		static const glm::vec4 dirtyPink;
		static const glm::vec4 darkBlueGreen;
		static const glm::vec4 pine;
		static const glm::vec4 yellowyGreen;
		static const glm::vec4 darkGold;
		static const glm::vec4 bluish;
		static const glm::vec4 darkishBlue;
		static const glm::vec4 dullRed;
		static const glm::vec4 pinkyRed;
		static const glm::vec4 bronze;
		static const glm::vec4 paleTeal;
		static const glm::vec4 militaryGreen;
		static const glm::vec4 barbiePink;
		static const glm::vec4 bubblegumPink;
		static const glm::vec4 peaSoupGreen;
		static const glm::vec4 darkMustard;
		static const glm::vec4 shit;
		static const glm::vec4 mediumPurple;
		static const glm::vec4 veryDarkGreen;
		static const glm::vec4 dirt;
		static const glm::vec4 duSkyPink;
		static const glm::vec4 redViolet;
		static const glm::vec4 lemonYellow;
		static const glm::vec4 pistachio;
		static const glm::vec4 dullYellow;
		static const glm::vec4 darkLimeGreen;
		static const glm::vec4 denimBlue;
		static const glm::vec4 tealBlue;
		static const glm::vec4 lightishBlue;
		static const glm::vec4 purpleyBlue;
		static const glm::vec4 lightIndigo;
		static const glm::vec4 swampGreen;
		static const glm::vec4 brownGreen;
		static const glm::vec4 darkMaroon;
		static const glm::vec4 hotPurple;
		static const glm::vec4 darkForestGreen;
		static const glm::vec4 fadedBlue;
		static const glm::vec4 drabGreen;
		static const glm::vec4 lightLimeGreen;
		static const glm::vec4 snotGreen;
		static const glm::vec4 yellowish;
		static const glm::vec4 lightBlueGreen;
		static const glm::vec4 bordeaux;
		static const glm::vec4 lightMauve;
		static const glm::vec4 ocean;
		static const glm::vec4 mariGold;
		static const glm::vec4 muddyGreen;
		static const glm::vec4 dullOrange;
		static const glm::vec4 steel;
		static const glm::vec4 electricPurple;
		static const glm::vec4 fluorescentGreen;
		static const glm::vec4 yellowishBrown;
		static const glm::vec4 blush;
		static const glm::vec4 softGreen;
		static const glm::vec4 brightOrange;
		static const glm::vec4 lemon;
		static const glm::vec4 purpleGrey;
		static const glm::vec4 acidGreen;
		static const glm::vec4 paleLavender;
		static const glm::vec4 violetBlue;
		static const glm::vec4 lightForestGreen;
		static const glm::vec4 burntRed;
		static const glm::vec4 khakiGreen;
		static const glm::vec4 cerise;
		static const glm::vec4 fadedPurple;
		static const glm::vec4 apricot;
		static const glm::vec4 darkOliveGreen;
		static const glm::vec4 greyBrown;
		static const glm::vec4 greenGrey;
		static const glm::vec4 trueBlue;
		static const glm::vec4 paleViolet;
		static const glm::vec4 periwinkleBlue;
		static const glm::vec4 lightSkyBlue;
		static const glm::vec4 blurple;
		static const glm::vec4 greenBrown;
		static const glm::vec4 blueGreen_;
		static const glm::vec4 brightTeal;
		static const glm::vec4 brownishYellow;
		static const glm::vec4 peaSoup;
		static const glm::vec4 forest;
		static const glm::vec4 barneyPurple;
		static const glm::vec4 ultraMarine;
		static const glm::vec4 purplish;
		static const glm::vec4 pukeYellow;
		static const glm::vec4 bluishGrey;
		static const glm::vec4 darkPeriwinkle;
		static const glm::vec4 darkLilac;
		static const glm::vec4 reddish;
		static const glm::vec4 lightMaroon;
		static const glm::vec4 dustyPurple;
		static const glm::vec4 terraCotta;
		static const glm::vec4 avocado;
		static const glm::vec4 marineBlue;
		static const glm::vec4 tealGreen;
		static const glm::vec4 slateGrey;
		static const glm::vec4 lighterGreen;
		static const glm::vec4 electricGreen;
		static const glm::vec4 dustyBlue;
		static const glm::vec4 goldenYellow;
		static const glm::vec4 brightYellow;
		static const glm::vec4 lightLavender;
		static const glm::vec4 umber;
		static const glm::vec4 poop;
		static const glm::vec4 darkPeach;
		static const glm::vec4 jungleGreen;
		static const glm::vec4 eggshell;
		static const glm::vec4 denim;
		static const glm::vec4 yellowBrown;
		static const glm::vec4 dullPurple;
		static const glm::vec4 chocolateBrown;
		static const glm::vec4 wineRed;
		static const glm::vec4 neonBlue;
		static const glm::vec4 dirtyGreen;
		static const glm::vec4 lightTan;
		static const glm::vec4 iceBlue;
		static const glm::vec4 cadetBlue;
		static const glm::vec4 darkMauve;
		static const glm::vec4 veryLightBlue;
		static const glm::vec4 greyPurple;
		static const glm::vec4 pastelPink;
		static const glm::vec4 veryLightGreen;
		static const glm::vec4 darkSkyBlue;
		static const glm::vec4 everGreen;
		static const glm::vec4 dullPink;
		static const glm::vec4 aubergine;
		static const glm::vec4 mahogany;
		static const glm::vec4 reddishOrange;
		static const glm::vec4 deepGreen;
		static const glm::vec4 vomitGreen;
		static const glm::vec4 purplePink_;
		static const glm::vec4 dustyPink;
		static const glm::vec4 fadedGreen;
		static const glm::vec4 camoGreen;
		static const glm::vec4 pinkyPurple;
		static const glm::vec4 pinkPurple_;
		static const glm::vec4 brownishRed;
		static const glm::vec4 darkRose;
		static const glm::vec4 mud;
		static const glm::vec4 brownish;
		static const glm::vec4 emeraldGreen;
		static const glm::vec4 paleBrown;
		static const glm::vec4 dullBlue;
		static const glm::vec4 burntUmber;
		static const glm::vec4 mediumGreen;
		static const glm::vec4 clay;
		static const glm::vec4 lightAqua;
		static const glm::vec4 lightOliveGreen;
		static const glm::vec4 brownishOrange;
		static const glm::vec4 darkAqua;
		static const glm::vec4 purplishPink;
		static const glm::vec4 darkSalmon;
		static const glm::vec4 greenishGrey;
		static const glm::vec4 jade;
		static const glm::vec4 uglyGreen;
		static const glm::vec4 darkBeige;
		static const glm::vec4 emerald;
		static const glm::vec4 paleRed;
		static const glm::vec4 lightMagenta;
		static const glm::vec4 sky;
		static const glm::vec4 lightCyan;
		static const glm::vec4 yellowOrange;
		static const glm::vec4 reddishPurple;
		static const glm::vec4 reddishPink;
		static const glm::vec4 orchid;
		static const glm::vec4 dirtyYellow;
		static const glm::vec4 orangeRed_;
		static const glm::vec4 deepRed;
		static const glm::vec4 orangeBrown;
		static const glm::vec4 cobaltBlue;
		static const glm::vec4 neonPink;
		static const glm::vec4 rosePink;
		static const glm::vec4 greyishPurple;
		static const glm::vec4 raspBerry;
		static const glm::vec4 aquaGreen;
		static const glm::vec4 salmonPink;
		static const glm::vec4 tangerine;
		static const glm::vec4 brownishGreen;
		static const glm::vec4 redBrown;
		static const glm::vec4 greenishBrown;
		static const glm::vec4 pumpkin;
		static const glm::vec4 pineGreen;
		static const glm::vec4 charcoal;
		static const glm::vec4 babyPink;
		static const glm::vec4 cornflower;
		static const glm::vec4 blueViolet;
		static const glm::vec4 chocolate;
		static const glm::vec4 greyishGreen;
		static const glm::vec4 scarlet;
		static const glm::vec4 greenYellow_;
		static const glm::vec4 darkOlive;
		static const glm::vec4 sienna;
		static const glm::vec4 pastelPurple;
		static const glm::vec4 terracotta;
		static const glm::vec4 aquaBlue;
		static const glm::vec4 sageGreen;
		static const glm::vec4 bloodRed;
		static const glm::vec4 deepPink;
		static const glm::vec4 grass;
		static const glm::vec4 moss;
		static const glm::vec4 pastelBlue;
		static const glm::vec4 bluishGreen;
		static const glm::vec4 greenBlue__;
		static const glm::vec4 darkTan;
		static const glm::vec4 greenishBlue;
		static const glm::vec4 paleOrange;
		static const glm::vec4 vomit;
		static const glm::vec4 forrestGreen;
		static const glm::vec4 darkLavender;
		static const glm::vec4 darkViolet;
		static const glm::vec4 purpleBlue_;
		static const glm::vec4 darkCyan;
		static const glm::vec4 oliveDrab;
		static const glm::vec4 pinkish;
		static const glm::vec4 cobalt;
		static const glm::vec4 neonPurple;
		static const glm::vec4 lightTurquoise;
		static const glm::vec4 appleGreen;
		static const glm::vec4 dullGreen;
		static const glm::vec4 wine;
		static const glm::vec4 powderBlue;
		static const glm::vec4 offWhite;
		static const glm::vec4 electricBlue;
		static const glm::vec4 darkTurquoise;
		static const glm::vec4 bluePurple_;
		static const glm::vec4 azure;
		static const glm::vec4 brightRed;
		static const glm::vec4 pinkishRed;
		static const glm::vec4 cornflowerBlue;
		static const glm::vec4 lightOlive;
		static const glm::vec4 grape;
		static const glm::vec4 greyishBlue;
		static const glm::vec4 purplishBlue;
		static const glm::vec4 yellowishGreen;
		static const glm::vec4 greenishYellow;
		static const glm::vec4 mediumBlue;
		static const glm::vec4 dustyRose;
		static const glm::vec4 lightViolet;
		static const glm::vec4 midnightBlue;
		static const glm::vec4 bluishPurple;
		static const glm::vec4 redOrange;
		static const glm::vec4 darkMagenta;
		static const glm::vec4 greenish;
		static const glm::vec4 oceanBlue;
		static const glm::vec4 coral;
		static const glm::vec4 cream;
		static const glm::vec4 reddishBrown;
		static const glm::vec4 burntSienna;
		static const glm::vec4 brick;
		static const glm::vec4 sage;
		static const glm::vec4 greyGreen_;
		static const glm::vec4 white;
		static const glm::vec4 robinsEggBlue;
		static const glm::vec4 mossGreen;
		static const glm::vec4 steelBlue;
		static const glm::vec4 eggplant;
		static const glm::vec4 lightYellow;
		static const glm::vec4 leafGreen;
		static const glm::vec4 lightGrey;
		static const glm::vec4 puke;
		static const glm::vec4 pinkishPurple;
		static const glm::vec4 seaBlue;
		static const glm::vec4 palePurple;
		static const glm::vec4 slateBlue;
		static const glm::vec4 blueGrey__;
		static const glm::vec4 hunterGreen;
		static const glm::vec4 fuchsia;
		static const glm::vec4 crimson;
		static const glm::vec4 paleYellow;
		static const glm::vec4 ochre;
		static const glm::vec4 mustardYellow;
		static const glm::vec4 lightRed;
		static const glm::vec4 cerulean;
		static const glm::vec4 palePink;
		static const glm::vec4 deepBlue;
		static const glm::vec4 rust;
		static const glm::vec4 lightTeal;
		static const glm::vec4 slate;
		static const glm::vec4 goldenrod;
		static const glm::vec4 darkYellow;
		static const glm::vec4 darkGrey;
		static const glm::vec4 armyGreen;
		static const glm::vec4 greyBlue__;
		static const glm::vec4 seafoam;
		static const glm::vec4 puce;
		static const glm::vec4 springGreen;
		static const glm::vec4 darkOrange;
		static const glm::vec4 sand;
		static const glm::vec4 pastelGreen;
		static const glm::vec4 mint;
		static const glm::vec4 lightOrange;
		static const glm::vec4 brightPink;
		static const glm::vec4 chartreuse;
		static const glm::vec4 deepPurple;
		static const glm::vec4 darkBrown;
		static const glm::vec4 taupe;
		static const glm::vec4 peaGreen;
		static const glm::vec4 pukeGreen;
		static const glm::vec4 kellyGreen;
		static const glm::vec4 seafoamGreen;
		static const glm::vec4 blueGreen__;
		static const glm::vec4 khaki;
		static const glm::vec4 burgundy;
		static const glm::vec4 darkTeal;
		static const glm::vec4 brickRed;
		static const glm::vec4 royalPurple;
		static const glm::vec4 plum;
		static const glm::vec4 mintGreen;
		static const glm::vec4 gold;
		static const glm::vec4 babyBlue;
		static const glm::vec4 yellowGreen__;
		static const glm::vec4 brightPurple;
		static const glm::vec4 darkRed;
		static const glm::vec4 paleBlue;
		static const glm::vec4 grassGreen;
		static const glm::vec4 navy;
		static const glm::vec4 aquaMarine_;
		static const glm::vec4 burntOrange;
		static const glm::vec4 neonGreen;
		static const glm::vec4 brightBlue;
		static const glm::vec4 rose;
		static const glm::vec4 lightPink;
		static const glm::vec4 mustard;
		static const glm::vec4 indigo;
		static const glm::vec4 lime;
		static const glm::vec4 seaGreen;
		static const glm::vec4 periwinkle;
		static const glm::vec4 darkPink;
		static const glm::vec4 oliveGreen;
		static const glm::vec4 peach;
		static const glm::vec4 paleGreen;
		static const glm::vec4 lightBrown;
		static const glm::vec4 hotPink;
		static const glm::vec4 black;
		static const glm::vec4 lilac;
		static const glm::vec4 navyBlue;
		static const glm::vec4 royalBlue;
		static const glm::vec4 beige;
		static const glm::vec4 salmon;
		static const glm::vec4 olive;
		static const glm::vec4 maroon;
		static const glm::vec4 brightGreen;
		static const glm::vec4 darkPurple;
		static const glm::vec4 mauve;
		static const glm::vec4 forestGreen;
		static const glm::vec4 aqua;
		static const glm::vec4 cyan;
		static const glm::vec4 tan;
		static const glm::vec4 darkBlue_;
		static const glm::vec4 lavender;
		static const glm::vec4 turquoise;
		static const glm::vec4 darkGreen_;
		static const glm::vec4 violet;
		static const glm::vec4 lightPurple;
		static const glm::vec4 limeGreen;
		static const glm::vec4 grey;
		static const glm::vec4 skyBlue;
		static const glm::vec4 yellow;
		static const glm::vec4 magenta;
		static const glm::vec4 lightGreen_;
		static const glm::vec4 orange;
		static const glm::vec4 teal;
		static const glm::vec4 lightBlue_;
		static const glm::vec4 red;
		static const glm::vec4 brown;
		static const glm::vec4 pink;
		static const glm::vec4 blue;
		static const glm::vec4 green;
		static const glm::vec4 purple;
		static const glm::vec4 sunsetOrange;
	};