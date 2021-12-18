class InstaDoc extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionInjectInstaDocTarget);
		AddAction(ActionInjectInstaDocSelf);
	}
	
	static bool IsWearingSplint(PlayerBase player)
	{
		if ( player.GetItemOnSlot("Splint_Right") )
		{
			return true;
		}
		return false;		
	}
	
	override void OnApply(PlayerBase player)
	{
		player.SetHealth((player.GetHealth("", "") + player.GetMaxHealth("", "") / 100) * 40);
		player.SetHealth("GlobalHealth", "Shock", player.GetMaxHealth("GlobalHealth", "Shock"));
		player.GetBleedingManagerServer().RemoveAllSources();
		
		//Heal Broken Limbs
		if (player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS || player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS_SPLINT)
		{
			player.AddHealth("LeftLeg", "Health", (player.GetMaxHealth("LeftLeg", "Health")));
			player.AddHealth("RightLeg", "Health", (player.GetMaxHealth("RightLeg", "Health")));
			player.AddHealth("RightFoot", "Health", (player.GetMaxHealth("RightFoot", "Health")));
			player.AddHealth("LeftFoot", "Health",	(player.GetMaxHealth("LeftFoot", "Health")));
			
			player.GetModifiersManager().DeactivateModifier(eModifiers.MDF_BROKEN_LEGS);
			player.UpdateBrokenLegs(eBrokenLegs.NO_BROKEN_LEGS);

			player.m_NotifiersManager.DeactivateByType(eNotifiers.NTF_FRACTURE);
			
			EntityAI attachment;
			
			Class.CastTo(attachment, player.GetItemOnSlot("Splint_Right"));
			
			if (attachment && attachment.GetType() == "Splint_Applied")
			{
				attachment.Delete();
			}
		}
		
		//Heal Diseases
		player.RemoveAllAgents();
	}
}