class ActionCrackSafeCB extends ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.DEFAULT_CONSTRUCT);
	}
};

class ActionCrackSafe extends ActionContinuousBase
{
	void ActionCrackSafe()
	{
		m_CallbackClass = ActionCrackSafeCB;
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
		return "Crack Safe";
	}

	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{	
		Object targetObject = target.GetObject();
		
		if ( targetObject && targetObject.IsInherited(Safe))
		{
			Safe safe = Safe.Cast(targetObject);
			
			if (!safe.getIsOpened())
			{
				return true;
			}			
		}
		
		return false;
	}
		
	override void OnFinishProgressServer(ActionData action_data)
	{	
		Safe safe = Safe.Cast(action_data.m_Target.GetObject());
		
		SafeCracker cracker = SafeCracker.Cast(action_data.m_MainItem);
		
		safe.openServer();
		safe.setPasswordSet(false);
		
		cracker.SetHealth(0);
	}
}