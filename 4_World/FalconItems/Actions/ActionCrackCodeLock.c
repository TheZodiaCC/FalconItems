class ActionCrackCodeLockCB extends ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DEFAULT_CONSTRUCT);
	}
};

class ActionCrackCodeLock extends ActionContinuousBase
{
	void ActionCrackCodeLock()
	{
		m_CallbackClass = ActionCrackCodeLockCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.BASEBUILDING );
	}
		
	override string GetText()
	{
		return "Crack CodeLock";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		Object targetObject = target.GetObject();
		
		if ( targetObject && targetObject.IsInherited(CodeLock))
		{
			CodeLock codeLock = CodeLock.Cast(targetObject);
			
			if (codeLock.getIsLocked())
			{
				return true;
			}			
		}
		
		return false;
	}
		
	override void OnFinishProgressServer(ActionData action_data)
	{	
		CodeLock codeLock = CodeLock.Cast(action_data.m_Target.GetObject());
		
		CodeLockCracker cracker = CodeLockCracker.Cast(action_data.m_MainItem);
		
		codeLock.unlockServer();
		codeLock.destroyLock();
		cracker.SetHealth(0);
	}
}