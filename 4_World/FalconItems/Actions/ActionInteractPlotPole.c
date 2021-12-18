class ActionInteractPlotPole extends ActionInteractBase
{
	void ActionInteractPlotPole()
	{
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
	}
	
	override void CreateConditionComponents()  
	{		
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}
	
	override string GetText()
	{
		return "Plot Pole";
	}
	
	override typename GetInputType()
	{
		return InteractActionInput;
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		TerritoryFlag totem = TerritoryFlag.Cast(target.GetObject());
		
		if (totem)
		{
			if ( totem.FindAttachmentBySlotName("Material_FPole_Flag"))
			{
				return true;
			}
		}
		
		return false;
	}
	
	override void OnExecuteServer(ActionData action_data)
	{
		TerritoryFlag totem = TerritoryFlag.Cast( action_data.m_Target.GetObject() );
		
		if (totem && totem.FindAttachmentBySlotName("Material_FPole_Flag"))
		{
			PlayerBase player = action_data.m_Player;
			
			GetRPCManager().SendRPC("FalconItems", "openPlotPoleC", new Param1<TerritoryFlag>(totem), true,  player.GetIdentity());
		}
	}
}