class ServerMarkersUtils
{
	const static string serverMarkersPath = "$profile:/FValues/ServerMarkers.json";;
	
	
	static array<ref ServerMarker> loadServerMarkers()
	{		
		if (FileExist(serverMarkersPath))
		{
			array<ref ServerMarker> data = new array<ref ServerMarker>();
			
			JsonFileLoader<array<ref ServerMarker>>.JsonLoadFile(serverMarkersPath, data);
			
			return data;
		}	
		
		return null;
	}
}