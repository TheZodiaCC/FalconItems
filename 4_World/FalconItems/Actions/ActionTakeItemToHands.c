modded class ActionTakeItemToHands: ActionInteractBase
{
	override void OnExecuteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();

		if (target_object.IsInherited(Safe))
		{
			Safe safe = Safe.Cast(target_object);
			
			if (safe)
			{
				safe.setPasswordSet(false);
			}
		}
		else
		{
			super.OnExecuteServer(action_data);
		}
	}
}