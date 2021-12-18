class ActionOpenSafe: ActionInteractBase
{
	void ActionOpenSafe()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}

	override string GetText()
	{
		return "Unlock Safe";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		
		if (target_object)
		{
			Safe safe = Safe.Cast( target_object );
			
			if (safe)
			{
				if (!safe.getIsOpened())
				{
					return true;
				}
			}
		}
		
		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		
		Safe safe = Safe.Cast(target_object);
		
		if (safe)
		{
			if (!safe.getIsOpened())
			{				
				PlayerBase player = action_data.m_Player;
				
				GetRPCManager().SendRPC("FalconItems", "openSafePassC", new Param1<Safe>(safe), true,  player.GetIdentity());
			}
		}
	}
}