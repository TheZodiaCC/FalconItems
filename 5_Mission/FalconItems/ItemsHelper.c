class ItemsHelper
{

	static bool checkPlayerForItem(PlayerBase player, string itemName)
	{
		ItemBase item = getItemFromInventory(player, itemName);
				
		if (item)
		{
			return true;
		}
		
		return false;
	}
	
	static ItemBase getItemFromInventory(PlayerBase player, string itemName)
	{
		ItemBase bodyPart;
		ItemBase item;
		array<string> bodyParts = new array<string>();
		array<string> emptyBodyParts = new array<string>();
		
		if (player)
		{
			item = ItemBase.Cast(player.GetItemInHands());
		
			if (item)
			{
				if (processItem(item, itemName))
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
					if (processItem(item, itemName))
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
							if (processItem(item, itemName))
							{
								return item;
							}
						}
					}
				}
			}
		}
		
		return null;
	}
	
	private static bool processItem(ItemBase item, string itemName)
	{

		if (item.ClassName() == itemName)
		{
			return true;
		}
		else 
		{
			return false;
		}
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