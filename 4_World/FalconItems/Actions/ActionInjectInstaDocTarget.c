class ActionInjectInstaDocTarget extends ActionInjectTarget
{
	override void OnEndServer( ActionData action_data )
	{
		if (action_data.m_WasExecuted && action_data.m_MainItem)
		{
			action_data.m_MainItem.Delete();
		}
	}
	
	override void ApplyModifiers( ActionData action_data )
	{
		action_data.m_MainItem.OnApply(PlayerBase.Cast(action_data.m_Target.GetObject()));
	}
}