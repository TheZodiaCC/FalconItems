modded class ActionLowerFlag
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		TerritoryFlag totem = TerritoryFlag.Cast( action_data.m_Target.GetObject() );
		
		if (totem)
		{
			GetGame().CreateObject("TerritoryToken", action_data.m_Player.GetPosition(), false, false, false);
			super.OnFinishProgressServer(action_data);
		}
	}
}