class ActionCloseCodeLock: ActionInteractBase
{
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.DEFAULT );
	}

	override string GetText()
	{
		return "Close CodeLock";
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
			if (!lock.getIsLocked())
			{
				return true;
			}
		}
		
		return false;
	}
	
	override void Start( ActionData action_data )
	{
		super.Start( action_data );
		
		CodeLock lock = CodeLock.Cast(action_data.m_Target.GetObject());
		
		if (lock)
		{
			if (!lock.getIsLocked())
			{
				lock.lockServer();
			}
		}
	}
}