class TerritoryBuildingHelpers
{
	const static int plotPoleRadius = TerritoryConsts.PLOT_POLE_RADIUS;
	const static int plotPoleRadiusForAnotherPlotPole = TerritoryConsts.PLOT_POLE_RADIUS_FROM_ANOTHER_PLOT_POLE;
	const static int maxObjectsCount = TerritoryConsts.MAX_OBJECTS_COUNT_PER_LEVEL;
	
	
	static TerritoryFlag getNearbyTotem(PlayerBase player, int radius)
	{
		array<Object> objects = new array<Object>();
		TerritoryFlag totem;
		
		GetGame().GetObjectsAtPosition(player.GetPosition(), radius, objects, null);
			
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i].IsInherited(TerritoryFlag))
			{
				totem = TerritoryFlag.Cast(objects[i]);		
				
				//Check if Totem is finished
				if (totem.FindAttachmentBySlotName("Material_FPole_Flag"))
				{
					return totem;
				}
			}
		}
		
		return null;
	}
	
	static int getTerritoryObjectsCount(TerritoryFlag totem)
	{
		array<Object> objects = new array<Object>();
		int objectsCount = 0;
		
		GetGame().GetObjectsAtPosition(totem.GetPosition(), plotPoleRadius, objects, null);
		
		for (int i = 0; i < objects.Count(); i++)
		{
			if (objects[i].IsInherited(BaseBuildingBase))
			{
				objectsCount++;
			}
		}
		
		return objectsCount;
	}
	
	static bool checkIfCanBuild(TerritoryFlag totem)
	{
		bool cond = false;
		
		int objectsCount = getTerritoryObjectsCount(totem);
		
		if (objectsCount + 1 <= maxObjectsCount * totem.getTerritoryLevel())
		{
			cond = true;
		}
		
		return cond;
	}
	
	static ItemBase getItemFromInventory(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		array<string> emptyBodyParts = new array<string>();
		
		item = ItemBase.Cast(player.GetItemInHands());
		
		if (item)
		{			
			if (item.ClassName() == itemName)
			{
				return item;
			}
			else if (item.ClassName() == (itemName + "_Base"))
			{
				return item;
			}
		}
		
		emptyBodyParts = getEmptyBodyParts();
		
		for (int k = 0; k < emptyBodyParts.Count(); k++)
		{
			item = ItemBase.Cast(player.GetItemOnSlot(emptyBodyParts[k]));
		
			if (item)
			{
				if (item.ClassName() == itemName)
				{
					return item;
				}
				else if (item.ClassName() == (itemName + "_Base"))
				{
					return item;
				}
			}
		}
		
		bodyParts = getBodyParts();
		
		for (int i = 0; i < bodyParts.Count(); i++)
		{
			bodyPart =  ItemBase.Cast(player.GetInventory().FindAttachmentByName(bodyParts[i]));
		
			if (bodyPart)
			{
				for (int j = 0; j < bodyPart.GetInventory().GetCargo().GetItemCount(); j++)
				{				
					item = ItemBase.Cast(bodyPart.GetInventory().GetCargo().GetItem(j));
					
					if (item)
					{
						if (item.ClassName() == itemName)
						{
							return item;
						}
						else if (item.ClassName() == (itemName + "_Base"))
						{
							return item;
						}
					}
				}
			}
		}
		
		return null;
	}
	
	private static array<string> getBodyParts()
	{
		array<string> bodyParts = new array<string>();
		
		bodyParts.Insert("Body");
		bodyParts.Insert("Back");
		bodyParts.Insert("Vest");
		bodyParts.Insert("Legs");
		
		return bodyParts;
	}
	
	private static array<string> getEmptyBodyParts()
	{
		array<string> bodyEmptyParts = new array<string>();
		
		bodyEmptyParts.Insert("Shoulder");
		bodyEmptyParts.Insert("Melee");
		bodyEmptyParts.Insert("Head");
		bodyEmptyParts.Insert("Headgear");
		bodyEmptyParts.Insert("Mask");
		bodyEmptyParts.Insert("Eyewear");
		bodyEmptyParts.Insert("Gloves");
		bodyEmptyParts.Insert("Feet");
		
		return bodyEmptyParts;
	}
}