class ActionOpenCodeLock: ActionInteractBase
{
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
	}

	override string GetText()
	{
		return "Manage CodeLock";
	}

	override bool IsInstant()
	{
		return true;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (!target.GetObject())
			return false;
		
		CodeLock lock = CodeLock.Cast( target.GetObject() );
		
		if ( lock && lock.GetHierarchyParent() && Fence.Cast(lock.GetHierarchyParent()) )
		{
			return true;
		}
		
		return false;
	}
	
	override void Start( ActionData action_data )
	{
		super.Start( action_data );
		
		if (GetGame().IsServer())
		{
			CodeLock lock = CodeLock.Cast(action_data.m_Target.GetObject());
		
			if (lock)
			{
				Fence fence = Fence.Cast(lock.GetHierarchyParent());
				
				if (!lock.getIsLocked() && fence.IsOpened())
				{
					fence.CloseFence();
				}
				else
				{
					PlayerBase player = action_data.m_Player;
					
					GetRPCManager().SendRPC("FalconItems", "openCodeLockPassC", new Param1<CodeLock>(lock), true,  player.GetIdentity());
				}
			}
		}
	}
}