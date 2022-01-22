class CfgPatches
{
	class FalconItems
	{
		requiredAddons[]={"DZ_Data", "JM_CF_Scripts"};
	};

	class Safe
	{
		units[]={
			"Safe"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Containers"
		};
	}

	class GPS
	{
		units[]={
			"GPS"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Navigation"
		};
	}

	class InstaDoc
	{
		units[]={
			"InstaDoc"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Medical"
		};
	}
};

class CfgMods
{
	class FalconItems
	{
	    dir = "FalconItems"
	    picture = "";
	    action = "";
	    hideName = 1;
	    hidePicture = 1;
	    name = "FalconItems"
	    credits = "";
	    author = "zNitche";
	    authorID = "0";
	    version = "1.0";
	    extra = 0;
	    type = "mod";

	    dependencies[] = { "World", "Mission" };

		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = {"FalconItems/Defines", "FalconItems/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"FalconItems/Defines", "FalconItems/5_Mission"};
			};
		};
	};
};

class CfgAmmo
{
	class DefaultAmmo;
	class Explosive_Ammo: DefaultAmmo
	{
		indirectHit = 1;
		indirectHitRange = 3;
		indirectHitRangeMultiplier = 4.0;
		explosive = 1;
		typicalSpeed = 3;
		initSpeed = 3;
		simulation = "shotShell";
		simulationStep = 0.05;
		soundSetExplosion[] = {"Grenade_explosion_SoundSet","Grenade_Tail_SoundSet"};
		class DamageApplied
		{
			type = "FragGrenade";
			bleedThreshold = 0.4;
			class Health
			{
				damage = 2000;
			};
			class Blood
			{
				damage = 0;
			};
			class Shock
			{
				damage = 0;
			};
		};
		class NoiseExplosion
		{
			strength = 500;
			type = "shot"; //Can be "sound"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class GPS: Inventory_Base
	{
		scope = 2;
		displayName = "GPS";
		descriptionShort = "GPS lmao";
		model="FalconItems\Items\gps\gps.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class SafeCracker: Inventory_Base
	{
		scope = 2;
		displayName = "Safe Cracker";
		descriptionShort = "";
		model="FalconItems\Items\gps\gps.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class CodeLockCracker: Inventory_Base
	{
		scope = 2;
		displayName = "CodeLock Cracker";
		descriptionShort = "";
		model="FalconItems\Items\gps\gps.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class InstaDoc: Inventory_Base
	{
		scope = 2;
		displayName = "InstaDoc";
		descriptionShort = "";
		model = "\dz\gear\medical\Morphine.p3d";
		rotationFlags = 17;
		itemSize[] = {1,2};
		weight = 60;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 50;
					healthLevels[] = {{1.0,{"DZ\gear\medical\data\Morphine.rvmat"}},{0.7,{"DZ\gear\medical\data\Morphine.rvmat"}},{0.5,{"DZ\gear\medical\data\Morphine_damage.rvmat"}},{0.3,{"DZ\gear\medical\data\Morphine_damage.rvmat"}},{0.0,{"DZ\gear\medical\data\Morphine_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class Morphine_spear
				{
					soundSet = "Morphine_spear_SoundSet";
					id = 201;
				};
				class Morphine_out
				{
					soundSet = "Morphine_out_SoundSet";
					id = 202;
				};
			};
		};
	};

	class Explosive: Inventory_Base
	{
		scope=2;
		displayName="C4";
		descriptionShort="";
		model="\dz\gear\consumables\Paper.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class TerritoryToken: Inventory_Base
	{
		scope=2;
		displayName="Territory Token";
		descriptionShort="";
		model="\dz\gear\consumables\Paper.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class TerritoryUpgradeToken: Inventory_Base
	{
		scope=2;
		displayName="Territory Upgrade Token";
		descriptionShort="";
		model="\dz\gear\consumables\Paper.p3d";
		rotationFlags=90;
		itemSize[] = {2,2};
		weight = 400;
		fragility=0.000001;
	};

	class CodeLock: Inventory_Base
	{
		scope = 2;
		displayName = "CodeLock";
		descriptionShort = "";
		model = "\DZ\gear\camping\combination_lock3.p3d";
		inventorySlot[] = {"Att_CombinationLock"};
		rotationFlags = 34;
		itemSize[] = {3,3};
		weight = 350;
		class AnimationSources
		{
			class AnimSourceHidden
			{
				source = "user";
				animPeriod = 0.01;
				initPhase = 1;
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 1500;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage = 0;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage = 0;
					};
					class Blood
					{
						damage = 0;
					};
					class Shock
					{
						damage = 0;
					};
				};
			};
		};
	};

	class WoodenLog: Inventory_Base
	{
		scope = 2;
		displayName = "$STR_CfgVehicles_WoodenLog0";
		descriptionShort = "$STR_CfgVehicles_WoodenLog1";
		model = "\dz\gear\camping\wooden_log.p3d";
		weight = 20000;
		itemSize[] = {3,11};
		varQuantityDestroyOnMin = 1;
		itemBehaviour = 0;
		canBeSplit = 1;
		varQuantityInit = 1.0;
		varQuantityMin = 0.0;
		varQuantityMax = 50.0;
		varStackMax = 1.0;
		inventorySlot[] = {"WoodenLogsStand","Truck_01_WoodenLogs","Material_WoodenLogs","Material_L1_WoodenLogs","Material_L2_WoodenLogs","Material_L3_WoodenLogs","Material_FPole_WoodenLog","Material_FPole_WoodenLog2","Material_FPole_MagicStick"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 500;
					healthLevels[] = {{1.0,{"dz\gear\camping\data\wooden_log.rvmat"}},{0.7,{"dz\gear\camping\data\wooden_log.rvmat"}},{0.5,{"dz\gear\camping\data\wooden_log_damage.rvmat"}},{0.3,{"dz\gear\camping\data\wooden_log_damage.rvmat"}},{0.0,{"dz\gear\camping\data\wooden_log_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickup
				{
					soundSet = "woodenlog_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "woodenlog_drop_SoundSet";
					id = 898;
				};
			};
		};
	};

	class WoodenPlank: Inventory_Base
	{
		scope = 2;
		displayName = "$STR_CfgVehicles_WoodenPlank0";
		descriptionShort = "$STR_CfgVehicles_WoodenPlank1";
		model = "\dz\gear\consumables\single_plank.p3d";
		weight = 1500;
		itemSize[] = {2,8};
		canBeSplit = 1;
		varQuantityInit = 10.0;
		varQuantityMin = 0.0;
		varQuantityMax = 100.0;
		varQuantityDestroyOnMin = 1;
		varStackMax = 10.0;
		inventorySlot[] = {"WoodenPlanksStand","Truck_01_WoodenPlanks","Material_WoodenPlanks","Material_L1_WoodenPlanks","Material_L1W1_WoodenPlanks","Material_L1W2_WoodenPlanks","Material_L1W3_WoodenPlanks","Material_L2_WoodenPlanks","Material_L2W1_WoodenPlanks","Material_L2W2_WoodenPlanks","Material_L2W3_WoodenPlanks","Material_L3_WoodenPlanks","Material_L3W1_WoodenPlanks","Material_L3W2_WoodenPlanks","Material_L3W3_WoodenPlanks"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 100;
					healthLevels[] = {{1.0,{"dz\gear\consumables\data\pile_of_planks.rvmat"}},{0.7,{"dz\gear\consumables\data\pile_of_planks.rvmat"}},{0.5,{"dz\gear\consumables\data\pile_of_planks_damage.rvmat"}},{0.3,{"dz\gear\consumables\data\pile_of_planks_damage.rvmat"}},{0.0,{"dz\gear\consumables\data\pile_of_planks_destruct.rvmat"}}};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickup
				{
					soundSet = "woodenlog_pickup_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "woodenlog_drop_SoundSet";
					id = 898;
				};
			};
		};
	};

	class Container_Base;
	class Small_Safe: Container_Base
	{
		scope=2;
		displayName="Small Safe";
		descriptionShort="Big chonky safe.";
		model="FalconItems\Items\safe\safe.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {10,40};
		};
	};

	class WoodStand: Container_Base
	{
		scope=2;
		displayName="Wood Stand";
		descriptionShort="To be written soon...";
		attachments[]={"WoodenLogsStand","WoodenPlanksStand"};
		model="FalconItems\Items\safe\safe.p3d";
		rotationFlags=0;
		weight=20000;
		itemSize[]={10,10};
		fragility=0.00000001;
		canBeDigged = 0;
		heavyItem = 1;
		itemBehaviour = 0;
		placement = "ForceSlopeOnTerrain";
		physLayer = "item_large";
		class Cargo
		{
			itemsCargoSize[] = {0,0};
		};
		class GUIInventoryAttachmentsProps
		{
			class BaseBuildingAttachments
			{
				name = "$STR_cfgvehicles_fence_att_category_materials";
				description = "";
				icon = "set:dayz_inventory image:cat_common_cargo";
				attachmentSlots[] = {"WoodenLogsStand", "WoodenPlanksStand"};
			};
		};
	};
};

class CfgSlots
{
	class WoodenLogsStand
	{
		name = "WoodenLogsStand";
		displayName = "#STR_CfgWoodenLogs0";
		ghostIcon = "set:dayz_inventory image:woodenlog";
		stackMax = 20;
	};
	class WoodenPlanksStand
	{
		name = "WoodenPlanksStand";
		displayName = "#STR_CfgPlanks0";
		ghostIcon = "set:dayz_inventory image:planks";
		stackMax = 100;
	};
};

class CfgSoundShaders
{
	class baseCharacter_SoundShader;

	class c4_beep_Soundshader: baseCharacter_SoundShader
	{
		samples[]=
		{

			{
				"FalconItems\Sounds\c4_beep\c4_beep",
				0.9
			}
		};
		volume=1;
	};
};

class CfgSoundSets
{
	class baseCharacter_SoundSet;

	class c4_beep_SoundSet: baseCharacter_SoundSet
	{
		soundShaders[]=
		{
			"c4_beep_Soundshader"
		};
	};
};
