class GPSTrack
{
	private Widget widgetRoot;
	private TextWidget distanceTEXT;
	
	private bool isTrackOn = false;
	
	//Constructor
	void GPSTrack() 
	{		
		widgetRoot = GetGame().GetWorkspace().CreateWidgets("FalconItems/GUI/Layouts/GPSTrack.layout");
		distanceTEXT = TextWidget.Cast(widgetRoot.FindAnyWidget("distanceTEXT"));
		
		widgetRoot.Show(false);
	}
	
	//Deconstructor
	void ~GPSTrack() 
	{
        if ( widgetRoot )
        	widgetRoot.Unlink();
    }
	
	bool getIsTrackOn()
	{
		return isTrackOn;
	}
	
	void setIsTrackOn(bool value) 
	{
		isTrackOn = value;
	}
	
	void showTrack() 
	{
		if (!isTrackOn)
		{
			widgetRoot.Show(true);
			setIsTrackOn(true);
		}
	}
	
	void hideTrack() 
	{
		if (isTrackOn)
		{
			widgetRoot.Show(false);
			setIsTrackOn(false);
		}
	}
	
	void setPosition(vector targetPos)
	{
		distanceTEXT.SetPos(Math.Ceil(targetPos[0]), Math.Ceil(targetPos[1]));
	}
	
	void setDistance(vector targetPos)
	{
		distanceTEXT.SetText(vector.Distance(GetGame().GetPlayer().GetPosition(), targetPos).ToString());
	}
	
	bool checkVisibility(vector targetPos)
	{
		bool visible = false;
		
		vector screenPosRelative = GetGame().GetScreenPosRelative(targetPos);
			
        if (screenPosRelative[0] >= 1 || screenPosRelative[0] == 0 || screenPosRelative[1] >= 1 || screenPosRelative[1] == 0) 
		{
            hideTrack();
       	} 
	
		else if (screenPosRelative[2] < 0) 
		{
            hideTrack();
        }
	 
		else 
		{
	        showTrack();
			
			visible = true;
        }
		
		return visible;
	}
	
	void update(vector targetPos)
	{
		if (checkVisibility(targetPos))
		{
			vector screenPos = GetGame().GetScreenPos(targetPos);
	
			setPosition(screenPos);
			setDistance(targetPos);
		}
	}
}
	
	
